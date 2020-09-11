import strutils
import ropes
import typetraits

from backend import Backend
from ../instruction import Instruction
import ../instruction_shapes

proc toHex*(arr: array[4, byte], last: string = "\n"): string =
    result = ""
    for b in 0 .. 3:
        result.add(arr[b].toHex())
        result.add(" ")

proc toBin*(arr: array[4, byte], last: string = "\n"): string =
    result = ""
    for b in countdown(3, 0):
        result.add(arr[b].int.toBin(8))
        if b != 0:
            result.add(" ")

proc joinString(arguments: varargs[string, `$`]): string =
    arguments.join()

proc printShape[shepType](test: uint32): string =
    var inst: RVInst = cast[RVInst](test);
    return joinString("base: ", inst.bytes.toHex, "(" ,inst.bytes.toBin, ") ", name(shepType), cast[shepType](inst), "\n")

proc printAssemblyInfo(instruction: Instruction): string =
    let base = instruction.base.integer
    return case instruction.shapeName:
    of "RVInstR":
        printShape[RVInstR](base)
    of "RVInstR4":
        printShape[RVInstR4](base)
    of "RVInstI":
        printShape[RVInstI](base)
    of "RVInstIS":
        printShape[RVInstIS](base)
    of "RVInstS":
        printShape[RVInstS](base)
    of "RVInstB":
        printShape[RVInstB](base)
    of "RVInstU":
        printShape[RVInstU](base)
    of "RVInstJ":
        printShape[RVInstJ](base)
    of "RVInstCheriSrcDst":
        printShape[RVInstCheriSrcDst](base)
    of "RVInstCheriSCR":
        printShape[RVInstCheriSCR](base)
    of "RVInstCheriTwoSrc":
        printShape[RVInstCheriTwoSrc](base)
    of "RVInstCheriClear":
        printShape[RVInstCheriClear](base)
    else: 
        ""
    
proc generate(instructions: seq[Instruction]): string =
    var resultRope = rope("")
    for index, instruction in instructions:
        resultRope.add(instruction.printAssemblyInfo())
    return $resultRope

proc getDebug*(): Backend = 
    return Backend(
        generate: generate
    )

