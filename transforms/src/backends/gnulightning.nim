import ropes
import strformat
import strutils
import tables
import sequtils, sugar

#todo base as const0

from ../instruction import Instruction, ArgumentLayout
from backend import Backend

proc joinString(arguments: varargs[string, `$`]): string =
    arguments.join()


let structures = """
typedef union
{
#define ui uint32_t
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui rs2 : 5;
        ui funct7 : 7;
    } R;
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui rs2 : 5;
        ui funct2 : 2;
        ui rs3 : 5;
    } R4;
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui imm11_0 : 12;
    } I;
#if __WORDSIZE == 64
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui shamt : 6;
        ui imm6_0 : 6;
    } IS;
#endif
    struct
    {
        ui opcode : 7;
        ui imm4_0 : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui rs2 : 5;
        ui imm11_5 : 7;
    } S;
    struct
    {
        ui opcode : 7;
        ui imm11 : 1;
        ui imm3_0 : 4;
        ui funct3 : 3;
        ui rs1 : 5;
        ui rs2 : 5;
        ui imm9_4 : 6;
        ui imm10 : 1;
    } B;
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui imm19_0 : 20;
    } U;
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui imm18_11 : 8;
        ui imm10 : 1;
        ui imm9_0 : 10;
        ui imm19 : 1;
    } J;
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui func3 : 3;
        ui rs1 : 5;
        ui imm4_0 : 5;
        ui func7 : 7;
    } CheriSrcDst;
    struct
    {
        ui opcode : 7;
        ui rd : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui imm4_0 : 5;
        ui funct7 : 7;
    } CheriSCR;
    struct
    {
        ui opcode : 7;
        ui funct5 : 5;
        ui funct3 : 3;
        ui rs1 : 5;
        ui rs2 : 5;
        ui funct7 : 7;
    } CheriTwoSrc;
    struct
    {
        ui opcode : 7;
        ui mask4_0 : 5;
        ui func3 : 3;
        ui mask7_5 : 3;
        ui quarter : 2;
        ui funct5 : 5;
        ui funct7 : 7;
    } CheriClear;
    uint32_t w;
#undef ui
} instr_t;


"""

var encounteredShapes = newTable[string, string]()

proc getFunctionName(instruction: Instruction): string =
    var functionName = instruction.shapeName
    functionName.removePrefix("RVInst")
    functionName = joinString("_", functionName, "type")
    return functionName

proc getFunction(instruction: Instruction): string =
    var functionName = getFunctionName(instruction)

    let base = instruction.base.integer
    let hasImm = instruction.layout.any(arg => arg.argument.name.startsWith("imm"))
    let hasMask = instruction.layout.any(arg => arg.argument.name.startsWith("mask"))
   
    var unionField = instruction.shapeName
    unionField.removePrefix("RVInst")

    # echo instruction.layout
    var argumentSeq =  instruction.layout.filter(arg => not (arg.argument.name.startsWith("imm") or (arg.argument.name == "mask"))).map(proc(arg: ArgumentLayout): string = 
            joinString "jit_int32_t ", arg.argument.name
        )

    if hasMask:
        argumentSeq.add("jit_int32_t mask")
    
    if hasImm:
        argumentSeq.add("jit_int32_t imm")
   
    let arguments = argumentSeq.join(", ")

    let assignements =  join(instruction.layout.map(proc(arg: ArgumentLayout): string = 
        if(arg.argument.name.startsWith("imm") or arg.argument.name.startsWith("mask")):
            let prefix = if arg.argument.name == "mask":
                "mask"
            else:
                "imm"

            let fieldName = if arg.length > 1:
                joinString(prefix,  arg.index + arg.length - 1, "_", arg.index)
            else: 
                joinString prefix, arg.index
            joinString "i.", unionField, ".", fieldName, " = ", &"(( {prefix} >> {arg.index} ) && 0b{repeat('1', arg.length)})", ";"
        else:
            joinString "i.", unionField, ".", arg.argument.name, " = ", arg.argument.name, ";"
        ), "\n\t")
    return &"static void {functionName}(jit_state_t *_jit, jit_int32_t w, {arguments}) {{\n\tinstr_t i; i.w = w;\n\t{assignements}\n\tii(i.w);\n}}\n\n"

# TODO: fix the immediate value hack i did
proc getCCode(instruction: Instruction): string = 
    if not encounteredShapes.hasKey(instruction.shapeName):
        encounteredShapes[instruction.shapeName] = getFunction(instruction)

    let functionName = getFunctionName(instruction)
    var argumentSeq =  instruction.layout.filter(arg => not (arg.argument.name.startsWith("imm") or (arg.argument.name == "mask"))).map(proc(arg: ArgumentLayout): string = 
        arg.argument.name
    )

    let hasImm = instruction.layout.any(arg => arg.argument.name.startsWith("imm"))
    let hasMask = instruction.layout.any(arg => arg.argument.name.startsWith("mask"))

    if hasMask:
        argumentSeq.add("mask")
    
    if hasImm:
        argumentSeq.add("imm")
   
    var arguments = argumentSeq.join(", ")
    result = &"#define {instruction.name}({arguments}) "

    # we need to have the base inside of the func args
    argumentSeq.insert($instruction.base.integer, 0)
    arguments = argumentSeq.join(", ")

    result.add(&"{functionName}(_jit, {arguments})\n\n")

proc generate(instructions: seq[Instruction]): string =
    var resultRope = rope("#include<stdint.h>\n\n\n")
    var instRope = rope("")
    resultRope.add(structures)
    for index, instruction in instructions:
        if instruction.name.contains("FENCE"):
            continue
        # if instruction.shapeName == "RVInstCheriClear":
            # echo instruction
        instRope.add(instruction.getCCode())
    
    for shape, function in encounteredShapes:
        resultRope.add(function)

    resultRope.add(instRope)
    return $resultRope


proc getLightning*(): Backend = 
    return Backend(
        generate: generate
    )


