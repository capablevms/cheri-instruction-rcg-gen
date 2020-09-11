import tables 
import sequtils 
import strformat

from ../instruction import Instruction

type Backend* = ref object
    generate*: proc(instructions: seq[Instruction]): string


from debug import getDebug
from gnulightning import getLightning
from c import getC

let backends = {
    "debug": getDebug(),
    "lightning": getLightning(),
    "c": getC()
}.toTable()

proc getBackend*(name: string): Backend =
    if backends.hasKey(name):
        return backends[name]
    else: 
        raise newException(ValueError, &"Couldn't find a backend with the name: {name}")

proc listBackends*(): seq[string] =
    return toSeq(backends.keys)