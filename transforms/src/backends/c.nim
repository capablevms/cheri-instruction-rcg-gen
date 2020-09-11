import ropes
import strformat
import strutils
import tables
import sequtils, sugar

#todo base as const

from ../instruction import Instruction, ArgumentLayout
from backend import Backend

proc joinString(arguments: varargs[string, `$`]): string =
    arguments.join()


proc toHex*(arr: array[4, byte], last: string = "\n"): string =
    result = ""
    for b in 0 .. 3:
        result.add(arr[b].toHex())
        result.add(" ")

let structures = """ """

# TODO: fix the immediate value hack i did
proc getCCode(instruction: Instruction): string = 
    let functionName = instruction.name.toLowerAscii()
    let base = instruction.base.integer
    let hasImm = instruction.layout.any(arg => arg.argument.name.startsWith("imm"))
    let hasMask = instruction.layout.any(arg => arg.argument.name.startsWith("mask"))
   
    var unionField = instruction.shapeName
    unionField.removePrefix("RVInst")

    # echo instruction.layout
    var argumentSeq =  instruction.layout.filter(arg => not (arg.argument.name.startsWith("imm") or (arg.argument.name == "mask"))).map(proc(arg: ArgumentLayout): string = 
            joinString "uint32_t ", arg.argument.name
        )

    if hasMask:
        argumentSeq.add("uint32_t mask")
    
    if hasImm:
        argumentSeq.add("uint32_t imm")
   
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
            joinString "i |= ", &"((( {prefix} >> {arg.index} ) && 0b{repeat('1', arg.length)}) << {arg.instructionIndex})", ";"
        else:
            joinString "i |= ", &"((( {arg.argument.name} >> {arg.index} ) && 0b{repeat('1', arg.length)}) << {arg.instructionIndex})", ";"
        ), "\n\t")
    return &"uint32_t {functionName}({arguments}) {{\n\tuint32_t i; i = {base}; // {instruction.base.bytes.toHex()} \n\t{assignements}\n\treturn i;\n}}\n\n"

proc generate(instructions: seq[Instruction]): string =
    var resultRope = rope("#include<stdint.h>\n\n\n")
    resultRope.add(structures)
    for index, instruction in instructions:
        if instruction.name.contains("FENCE"):
            continue
        # if instruction.shapeName == "RVInstCheriClear":
            # echo instruction
        resultRope.add(instruction.getCCode())
            
    return $resultRope


proc getC*(): Backend = 
    return Backend(
        generate: generate
    )


