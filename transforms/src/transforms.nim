import json
# import sequtils, sugar
import tables
import parseopt

from instruction import Instruction, toInstruction, isSupported
from backends/backend import Backend, getBackend, listBackends


let jsonArray = parseFile("../defs/instr.json").getElems()
# let instructions = jsonArray["!instanceof"]["RVInst"].getElems().map(instruction => instruction.getStr())

# let i_value = -208
# let imm: uint16 = uint16(i_value + (2 shl 11))

var instructions: seq[Instruction] = newSeq[Instruction]()

# echo int64(imm).toBin(12)

# let bitInst = RVInstS(opcode: 0b0100011, imm4_0: imm, funct3: 0b100, rs1: 8, rs2: 13, imm11_5: imm shr 5)
# echo cast[ref array[4, byte]](bitInst.unsafeAddr).toHex
# echo bitInst


var unsupported = newTable[string, uint32]()

for index, instructionJson in jsonArray:
    let name = instructionJson["!name"].getStr()
    let shapeName = instructionJson["!superclasses"][3].getStr()
    var instruction = instructionJson.toInstruction()

    if not instruction.isSupported():
        unsupported[shapeName] = if unsupported.hasKey(shapeName):
            unsupported[shapeName] + 1
        else:
            1
    else:
        instructions.add(instruction)


for kind, key, val in getopt():
    case kind
    of cmdLongOption:
        case key
        of "help":
            echo "Supported backends:"
            for backend in listBackends():
                echo backend
            break

        of "unsupported":
            var count: uint32 = 0
            for key, value in unsupported:
                echo "Family: ", key
                count += value
            echo "Unsupporeted inst count: ", count

        of "backend":
            let backend = getBackend(val)
            echo backend.generate(instructions)
        of "out":
            echo "out: ", val

        of "count":
            echo "All instructions: ", jsonArray.len

        else: 
            echo "Unknown argument: ", key

    of cmdArgument:
        echo val 

    else:
        echo kind
        continue

    