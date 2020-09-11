type
  ui* = uint32

type RVInstR* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    rs2* {.bitsize: 5.}: ui
    funct7* {.bitsize: 7.}: ui

type RVInstR4* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    rs2* {.bitsize: 5.}: ui
    funct2* {.bitsize: 2.}: ui
    rs3* {.bitsize: 5.}: ui

type RVInstI* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    imm11_0* {.bitsize: 12.}: ui

type RVInstIS* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    shamt* {.bitsize: 6.}: ui
    imm6_0* {.bitsize: 6.}: ui

type RVInstS* = object
    opcode* {.bitsize: 7.}: ui
    imm4_0* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    rs2* {.bitsize: 5.}: ui
    imm11_5* {.bitsize: 7.}: ui

type RVInstB* = object
    opcode* {.bitsize: 7.}: ui
    imm11* {.bitsize: 1.}: ui
    imm4_1* {.bitsize: 4.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    rs2* {.bitsize: 5.}: ui
    imm10_5* {.bitsize: 6.}: ui
    imm12* {.bitsize: 1.}: ui

type RVInstU* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    imm12_31* {.bitsize: 20.}: ui

type RVInstJ* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    imm19_12* {.bitsize: 8.}: ui
    imm11* {.bitsize: 1.}: ui
    imm10_1* {.bitsize: 10.}: ui
    imm20* {.bitsize: 1.}: ui

type RVInstCheriSrcDst* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    func3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    imm5* {.bitsize: 5.}: ui
    func7* {.bitsize: 7.}: ui

type RVInstCheriSCR* = object
    opcode* {.bitsize: 7.}: ui
    rd* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    imm5* {.bitsize: 5.}: ui
    funct7* {.bitsize: 7.}: ui

type RVInstCheriTwoSrc* = object
    opcode* {.bitsize: 7.}: ui
    funct5* {.bitsize: 5.}: ui
    funct3* {.bitsize: 3.}: ui
    rs1* {.bitsize: 5.}: ui
    rs2* {.bitsize: 5.}: ui
    funct7* {.bitsize: 7.}: ui

type RVInstCheriClear* = object
    opcode* {.bitsize: 7.}: ui
    mask0* {.bitsize: 5.}: ui
    func3* {.bitsize: 3.}: ui
    maks1* {.bitsize: 3.}: ui
    quarter* {.bitsize: 2.}: ui
    funct5* {.bitsize: 5.}: ui
    funct7* {.bitsize: 7.}: ui

type RVInst* {.bycopy, union.} = object
    integer*: uint32
    bytes*: array[4, byte]
    R*: RVInstR
    R4*: RVInstR4
    I*: RVInstI
    IS*: RVInstIS
    S*: RVInstS
    B*: RVInstB
    U*: RVInstU
    J*: RVInstJ
    CheriSrcDst*: RVInstCheriSrcDst
    CheriSCR*: RVInstCheriSCR
    CheriTwoSrc*: RVInstCheriTwoSrc
    CheriClear*: RVInstCheriClear
