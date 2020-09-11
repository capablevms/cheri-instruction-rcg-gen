import json
import tables

type Argument* = object
    name*: string
    argType*: string
    direction*: bool # 0 - in, 1 - out

type ArgumentLayout* = object
    instructionIndex*: int
    index*: int
    length*: int
    argument*: Argument


type Encoding* {.bycopy, union.} = object
    integer*: uint32
    bytes*: array[4, byte]

type Instruction* = object
    name*: string
    shapeName*: string
    base*: Encoding
    mask*: Encoding
    operands*: ref Table[string, Argument]
    layout*: seq[ArgumentLayout]

proc toInstruction*(node: JsonNode): Instruction =
    result =  Instruction(
        shapeName: node["!superclasses"][3].getStr(),
        name: node["!name"].getStr())

    result.operands = newTable[string, Argument]()
    
    var base: uint32 = 0
    var mask: uint32 = 0
    var inArg = false
    var currentLayout: ArgumentLayout
    for index, bit in node["Inst"].getElems():
        case bit.kind:
            of JObject:
                var newArg = if inArg == false:
                    true
                elif currentLayout.argument.name != bit["var"].getStr:
                    result.layout.add(currentLayout)
                    true
                elif (currentLayout.index + currentLayout.length) != bit["index"].getInt:
                    result.layout.add(currentLayout)
                    true
                else:
                    false

                if newArg == true:
                    inArg = true
                    currentLayout.index = bit["index"].getInt
                    currentLayout.argument = Argument(name: bit["var"].getStr)
                    currentLayout.length = 1
                    currentLayout.instructionIndex = index
                else:
                    currentLayout.length += 1
            of JInt:
                if inArg == true:
                    inArg = false
                    result.layout.add(currentLayout)

                # echo index, " ", bit
                if bit.getInt() == 1:
                    base = base xor (1u32 shl index)
                mask = mask xor (1u32 shl index)
            else:
                echo "Unsupported kind: ", bit.kind, " ", result, " ", node
                break


    if inArg == true:
        result.layout.add(currentLayout)


    result.mask.integer = mask
    result.base.integer = base

proc isSupported*(instruction: Instruction): bool =
    return case instruction.shapeName:
    of "RVInstR", "RVInstR4", "RVInstI", "RVInstIS", "RVInstS", "RVInstB", "RVInstU", "RVInstJ", "RVInstCheriSrcDst", "RVInstCheriSCR", "RVInstCheriTwoSrc", "RVInstCheriClear":
        true
    else:
        false
        
