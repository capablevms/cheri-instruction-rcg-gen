#include<stdint.h>


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


static void _Stype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rs1, jit_int32_t rs2, jit_int32_t imm) {
	instr_t i; i.w = w;
	i.S.imm4_0 = (( imm >> 0 ) && 0b11111);
	i.S.rs1 = rs1;
	i.S.rs2 = rs2;
	i.S.imm11_5 = (( imm >> 5 ) && 0b1111111);
	ii(i.w);
}

static void _CheriSCRtype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rd, jit_int32_t rs1, jit_int32_t imm) {
	instr_t i; i.w = w;
	i.CheriSCR.rd = rd;
	i.CheriSCR.rs1 = rs1;
	i.CheriSCR.imm4_0 = (( imm >> 0 ) && 0b11111);
	ii(i.w);
}

static void _CheriTwoSrctype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rs1, jit_int32_t rs2) {
	instr_t i; i.w = w;
	i.CheriTwoSrc.rs1 = rs1;
	i.CheriTwoSrc.rs2 = rs2;
	ii(i.w);
}

static void _Itype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rd, jit_int32_t rs1, jit_int32_t imm) {
	instr_t i; i.w = w;
	i.I.rd = rd;
	i.I.rs1 = rs1;
	i.I.imm11_0 = (( imm >> 0 ) && 0b111111111111);
	ii(i.w);
}

static void _CheriSrcDsttype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rd, jit_int32_t rs1) {
	instr_t i; i.w = w;
	i.CheriSrcDst.rd = rd;
	i.CheriSrcDst.rs1 = rs1;
	ii(i.w);
}

static void _CheriCleartype(jit_state_t *_jit, jit_int32_t w, jit_int32_t quarter, jit_int32_t mask) {
	instr_t i; i.w = w;
	i.CheriClear.mask4_0 = (( mask >> 0 ) && 0b11111);
	i.CheriClear.mask7_5 = (( mask >> 5 ) && 0b111);
	i.CheriClear.quarter = quarter;
	ii(i.w);
}

static void _Jtype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rd, jit_int32_t imm) {
	instr_t i; i.w = w;
	i.J.rd = rd;
	i.J.imm18_11 = (( imm >> 11 ) && 0b11111111);
	i.J.imm10 = (( imm >> 10 ) && 0b1);
	i.J.imm9_0 = (( imm >> 0 ) && 0b1111111111);
	i.J.imm19 = (( imm >> 19 ) && 0b1);
	ii(i.w);
}

static void _Btype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rs1, jit_int32_t rs2, jit_int32_t imm) {
	instr_t i; i.w = w;
	i.B.imm10 = (( imm >> 10 ) && 0b1);
	i.B.imm3_0 = (( imm >> 0 ) && 0b1111);
	i.B.rs1 = rs1;
	i.B.rs2 = rs2;
	i.B.imm9_4 = (( imm >> 4 ) && 0b111111);
	i.B.imm11 = (( imm >> 11 ) && 0b1);
	ii(i.w);
}

static void _Utype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rd, jit_int32_t imm) {
	instr_t i; i.w = w;
	i.U.rd = rd;
	i.U.imm19_0 = (( imm >> 0 ) && 0b11111111111111111111);
	ii(i.w);
}

static void _Rtype(jit_state_t *_jit, jit_int32_t w, jit_int32_t rd, jit_int32_t rs1, jit_int32_t rs2) {
	instr_t i; i.w = w;
	i.R.rd = rd;
	i.R.rs1 = rs1;
	i.R.rs2 = rs2;
	ii(i.w);
}

#define ADD(rd, rs1, rs2) _Rtype(_jit, 51, rd, rs1, rs2)

#define ADDI(rd, rs1, imm) _Itype(_jit, 19, rd, rs1, imm)

#define ADDIW(rd, rs1, imm) _Itype(_jit, 27, rd, rs1, imm)

#define ADDW(rd, rs1, rs2) _Rtype(_jit, 59, rd, rs1, rs2)

#define AND(rd, rs1, rs2) _Rtype(_jit, 28723, rd, rs1, rs2)

#define ANDI(rd, rs1, imm) _Itype(_jit, 28691, rd, rs1, imm)

#define AUIPC(rd, imm) _Utype(_jit, 23, rd, imm)

#define AUIPCC(rd, imm) _Utype(_jit, 23, rd, imm)

#define BEQ(rs1, rs2, imm) _Btype(_jit, 99, rs1, rs2, imm)

#define BGE(rs1, rs2, imm) _Btype(_jit, 20579, rs1, rs2, imm)

#define BGEU(rs1, rs2, imm) _Btype(_jit, 28771, rs1, rs2, imm)

#define BLT(rs1, rs2, imm) _Btype(_jit, 16483, rs1, rs2, imm)

#define BLTU(rs1, rs2, imm) _Btype(_jit, 24675, rs1, rs2, imm)

#define BNE(rs1, rs2, imm) _Btype(_jit, 4195, rs1, rs2, imm)

#define CAndPerm(rd, rs1, rs2) _Rtype(_jit, 436207707, rd, rs1, rs2)

#define CBuildCap(rd, rs1, rs2) _Rtype(_jit, 973078619, rd, rs1, rs2)

#define CCSeal(rd, rs1, rs2) _Rtype(_jit, 1040187483, rd, rs1, rs2)

#define CCall(rs1, rs2) _CheriTwoSrctype(_jit, 4227858651, rs1, rs2)

#define CClearTag(rd, rs1) _CheriSrcDsttype(_jit, 4272947291, rd, rs1)

#define CCopyType(rd, rs1, rs2) _Rtype(_jit, 1006633051, rd, rs1, rs2)

#define CFLD(rd, rs1, imm) _Itype(_jit, 12295, rd, rs1, imm)

#define CFLW(rd, rs1, imm) _Itype(_jit, 8199, rd, rs1, imm)

#define CFSD(rs1, rs2, imm) _Stype(_jit, 12327, rs1, rs2, imm)

#define CFSW(rs1, rs2, imm) _Stype(_jit, 8231, rs1, rs2, imm)

#define CFromPtr(rd, rs1, rs2) _Rtype(_jit, 637534299, rd, rs1, rs2)

#define CGetAddr(rd, rs1) _CheriSrcDsttype(_jit, 4277141595, rd, rs1)

#define CGetBase(rd, rs1) _CheriSrcDsttype(_jit, 4263510107, rd, rs1)

#define CGetFlags(rd, rs1) _CheriSrcDsttype(_jit, 4268752987, rd, rs1)

#define CGetLen(rd, rs1) _CheriSrcDsttype(_jit, 4264558683, rd, rs1)

#define CGetOffset(rd, rs1) _CheriSrcDsttype(_jit, 4267704411, rd, rs1)

#define CGetPerm(rd, rs1) _CheriSrcDsttype(_jit, 4261412955, rd, rs1)

#define CGetSealed(rd, rs1) _CheriSrcDsttype(_jit, 4266655835, rd, rs1)

#define CGetTag(rd, rs1) _CheriSrcDsttype(_jit, 4265607259, rd, rs1)

#define CGetType(rd, rs1) _CheriSrcDsttype(_jit, 4262461531, rd, rs1)

#define CIncOffset(rd, rs1, rs2) _Rtype(_jit, 570425435, rd, rs1, rs2)

#define CIncOffsetImm(rd, rs1, imm) _Itype(_jit, 4187, rd, rs1, imm)

#define CJALR(rd, rs1) _CheriSrcDsttype(_jit, 4273995867, rd, rs1)

#define CLB(rd, rs1, imm) _Itype(_jit, 3, rd, rs1, imm)

#define CLBU(rd, rs1, imm) _Itype(_jit, 16387, rd, rs1, imm)

#define CLC_128(rd, rs1, imm) _Itype(_jit, 8207, rd, rs1, imm)

#define CLC_64(rd, rs1, imm) _Itype(_jit, 12291, rd, rs1, imm)

#define CLD(rd, rs1, imm) _Itype(_jit, 12291, rd, rs1, imm)

#define CLH(rd, rs1, imm) _Itype(_jit, 4099, rd, rs1, imm)

#define CLHU(rd, rs1, imm) _Itype(_jit, 20483, rd, rs1, imm)

#define CLW(rd, rs1, imm) _Itype(_jit, 8195, rd, rs1, imm)

#define CLWU(rd, rs1, imm) _Itype(_jit, 24579, rd, rs1, imm)

#define CMove(rd, rs1) _CheriSrcDsttype(_jit, 4271898715, rd, rs1)

#define CRAM(rd, rs1) _CheriSrcDsttype(_jit, 4270850139, rd, rs1)

#define CRRL(rd, rs1) _CheriSrcDsttype(_jit, 4269801563, rd, rs1)

#define CSB(rs1, rs2, imm) _Stype(_jit, 35, rs1, rs2, imm)

#define CSC_128(rs1, rs2, imm) _Stype(_jit, 16419, rs1, rs2, imm)

#define CSC_64(rs1, rs2, imm) _Stype(_jit, 12323, rs1, rs2, imm)

#define CSD(rs1, rs2, imm) _Stype(_jit, 12323, rs1, rs2, imm)

#define CSEQX(rd, rs1, rs2) _Rtype(_jit, 1107296347, rd, rs1, rs2)

#define CSH(rs1, rs2, imm) _Stype(_jit, 4131, rs1, rs2, imm)

#define CSRRC(rd, rs1, imm) _Itype(_jit, 12403, rd, rs1, imm)

#define CSRRCI(rd, rs1, imm) _Itype(_jit, 28787, rd, rs1, imm)

#define CSRRS(rd, rs1, imm) _Itype(_jit, 8307, rd, rs1, imm)

#define CSRRSI(rd, rs1, imm) _Itype(_jit, 24691, rd, rs1, imm)

#define CSRRW(rd, rs1, imm) _Itype(_jit, 4211, rd, rs1, imm)

#define CSRRWI(rd, rs1, imm) _Itype(_jit, 20595, rd, rs1, imm)

#define CSW(rs1, rs2, imm) _Stype(_jit, 8227, rs1, rs2, imm)

#define CSeal(rd, rs1, rs2) _Rtype(_jit, 369098843, rd, rs1, rs2)

#define CSealEntry(rd, rs1) _CheriSrcDsttype(_jit, 4279238747, rd, rs1)

#define CSetAddr(rd, rs1, rs2) _Rtype(_jit, 536871003, rd, rs1, rs2)

#define CSetBounds(rd, rs1, rs2) _Rtype(_jit, 268435547, rd, rs1, rs2)

#define CSetBoundsExact(rd, rs1, rs2) _Rtype(_jit, 301989979, rd, rs1, rs2)

#define CSetBoundsImm(rd, rs1, imm) _Itype(_jit, 8283, rd, rs1, imm)

#define CSetFlags(rd, rs1, rs2) _Rtype(_jit, 469762139, rd, rs1, rs2)

#define CSetOffset(rd, rs1, rs2) _Rtype(_jit, 503316571, rd, rs1, rs2)

#define CSpecialRW(rd, rs1, imm) _CheriSCRtype(_jit, 33554523, rd, rs1, imm)

#define CSub(rd, rs1, rs2) _Rtype(_jit, 671088731, rd, rs1, rs2)

#define CTestSubset(rd, rs1, rs2) _Rtype(_jit, 1073741915, rd, rs1, rs2)

#define CToPtr(rd, rs1, rs2) _Rtype(_jit, 603979867, rd, rs1, rs2)

#define CUnseal(rd, rs1, rs2) _Rtype(_jit, 402653275, rd, rs1, rs2)

#define Clear(quarter, mask) _CheriCleartype(_jit, 4275044443, quarter, mask)

#define DIV(rd, rs1, rs2) _Rtype(_jit, 33570867, rd, rs1, rs2)

#define DIVU(rd, rs1, rs2) _Rtype(_jit, 33574963, rd, rs1, rs2)

#define DIVUW(rd, rs1, rs2) _Rtype(_jit, 33574971, rd, rs1, rs2)

#define DIVW(rd, rs1, rs2) _Rtype(_jit, 33570875, rd, rs1, rs2)

#define DRET() _Rtype(_jit, 2065694835)

#define EBREAK() _Itype(_jit, 1048691)

#define ECALL() _Itype(_jit, 115)

#define FPClear(quarter, mask) _CheriCleartype(_jit, 4278190171, quarter, mask)

#define JAL(rd, imm) _Jtype(_jit, 111, rd, imm)

#define JALR(rd, rs1, imm) _Itype(_jit, 103, rd, rs1, imm)

#define LB(rd, rs1, imm) _Itype(_jit, 3, rd, rs1, imm)

#define LBU(rd, rs1, imm) _Itype(_jit, 16387, rd, rs1, imm)

#define LBU_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4206887003, rd, rs1)

#define LBU_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4198498395, rd, rs1)

#define LB_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4202692699, rd, rs1)

#define LB_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4194304091, rd, rs1)

#define LC_128(rd, rs1, imm) _Itype(_jit, 8207, rd, rs1, imm)

#define LC_64(rd, rs1, imm) _Itype(_jit, 12291, rd, rs1, imm)

#define LC_CAP_128(rd, rs1) _CheriSrcDsttype(_jit, 4226809947, rd, rs1)

#define LC_CAP_64(rd, rs1) _CheriSrcDsttype(_jit, 4205838427, rd, rs1)

#define LC_DDC_128(rd, rs1) _CheriSrcDsttype(_jit, 4218421339, rd, rs1)

#define LC_DDC_64(rd, rs1) _CheriSrcDsttype(_jit, 4197449819, rd, rs1)

#define LD(rd, rs1, imm) _Itype(_jit, 12291, rd, rs1, imm)

#define LD_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4205838427, rd, rs1)

#define LD_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4197449819, rd, rs1)

#define LH(rd, rs1, imm) _Itype(_jit, 4099, rd, rs1, imm)

#define LHU(rd, rs1, imm) _Itype(_jit, 20483, rd, rs1, imm)

#define LHU_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4207935579, rd, rs1)

#define LHU_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4199546971, rd, rs1)

#define LH_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4203741275, rd, rs1)

#define LH_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4195352667, rd, rs1)

#define LR_B_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4219469915, rd, rs1)

#define LR_B_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4211081307, rd, rs1)

#define LR_C_CAP_128(rd, rs1) _CheriSrcDsttype(_jit, 4223664219, rd, rs1)

#define LR_C_CAP_64(rd, rs1) _CheriSrcDsttype(_jit, 4222615643, rd, rs1)

#define LR_C_DDC_128(rd, rs1) _CheriSrcDsttype(_jit, 4215275611, rd, rs1)

#define LR_C_DDC_64(rd, rs1) _CheriSrcDsttype(_jit, 4214227035, rd, rs1)

#define LR_D_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4222615643, rd, rs1)

#define LR_D_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4214227035, rd, rs1)

#define LR_H_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4220518491, rd, rs1)

#define LR_H_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4212129883, rd, rs1)

#define LR_W_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4221567067, rd, rs1)

#define LR_W_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4213178459, rd, rs1)

#define LUI(rd, imm) _Utype(_jit, 55, rd, imm)

#define LW(rd, rs1, imm) _Itype(_jit, 8195, rd, rs1, imm)

#define LWU(rd, rs1, imm) _Itype(_jit, 24579, rd, rs1, imm)

#define LWU_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4208984155, rd, rs1)

#define LWU_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4200595547, rd, rs1)

#define LW_CAP(rd, rs1) _CheriSrcDsttype(_jit, 4204789851, rd, rs1)

#define LW_DDC(rd, rs1) _CheriSrcDsttype(_jit, 4196401243, rd, rs1)

#define MRET() _Rtype(_jit, 807403635)

#define MUL(rd, rs1, rs2) _Rtype(_jit, 33554483, rd, rs1, rs2)

#define MULH(rd, rs1, rs2) _Rtype(_jit, 33558579, rd, rs1, rs2)

#define MULHSU(rd, rs1, rs2) _Rtype(_jit, 33562675, rd, rs1, rs2)

#define MULHU(rd, rs1, rs2) _Rtype(_jit, 33566771, rd, rs1, rs2)

#define MULW(rd, rs1, rs2) _Rtype(_jit, 33554491, rd, rs1, rs2)

#define OR(rd, rs1, rs2) _Rtype(_jit, 24627, rd, rs1, rs2)

#define ORI(rd, rs1, imm) _Itype(_jit, 24595, rd, rs1, imm)

#define REM(rd, rs1, rs2) _Rtype(_jit, 33579059, rd, rs1, rs2)

#define REMU(rd, rs1, rs2) _Rtype(_jit, 33583155, rd, rs1, rs2)

#define REMUW(rd, rs1, rs2) _Rtype(_jit, 33583163, rd, rs1, rs2)

#define REMW(rd, rs1, rs2) _Rtype(_jit, 33579067, rd, rs1, rs2)

#define SB(rs1, rs2, imm) _Stype(_jit, 35, rs1, rs2, imm)

#define SB_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160750683, rs1, rs2)

#define SB_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160749659, rs1, rs2)

#define SC_128(rs1, rs2, imm) _Stype(_jit, 16419, rs1, rs2, imm)

#define SC_64(rs1, rs2, imm) _Stype(_jit, 12323, rs1, rs2, imm)

#define SC_B_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160752731, rs1, rs2)

#define SC_B_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160751707, rs1, rs2)

#define SC_CAP_128(rs1, rs2) _CheriTwoSrctype(_jit, 4160751195, rs1, rs2)

#define SC_CAP_64(rs1, rs2) _CheriTwoSrctype(_jit, 4160751067, rs1, rs2)

#define SC_C_CAP_128(rs1, rs2) _CheriTwoSrctype(_jit, 4160753243, rs1, rs2)

#define SC_C_CAP_64(rs1, rs2) _CheriTwoSrctype(_jit, 4160753115, rs1, rs2)

#define SC_C_DDC_128(rs1, rs2) _CheriTwoSrctype(_jit, 4160752219, rs1, rs2)

#define SC_C_DDC_64(rs1, rs2) _CheriTwoSrctype(_jit, 4160752091, rs1, rs2)

#define SC_DDC_128(rs1, rs2) _CheriTwoSrctype(_jit, 4160750171, rs1, rs2)

#define SC_DDC_64(rs1, rs2) _CheriTwoSrctype(_jit, 4160750043, rs1, rs2)

#define SC_D_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160753115, rs1, rs2)

#define SC_D_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160752091, rs1, rs2)

#define SC_H_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160752859, rs1, rs2)

#define SC_H_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160751835, rs1, rs2)

#define SC_W_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160752987, rs1, rs2)

#define SC_W_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160751963, rs1, rs2)

#define SD(rs1, rs2, imm) _Stype(_jit, 12323, rs1, rs2, imm)

#define SD_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160751067, rs1, rs2)

#define SD_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160750043, rs1, rs2)

#define SH(rs1, rs2, imm) _Stype(_jit, 4131, rs1, rs2, imm)

#define SH_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160750811, rs1, rs2)

#define SH_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160749787, rs1, rs2)

#define SLL(rd, rs1, rs2) _Rtype(_jit, 4147, rd, rs1, rs2)

#define SLLW(rd, rs1, rs2) _Rtype(_jit, 4155, rd, rs1, rs2)

#define SLT(rd, rs1, rs2) _Rtype(_jit, 8243, rd, rs1, rs2)

#define SLTI(rd, rs1, imm) _Itype(_jit, 8211, rd, rs1, imm)

#define SLTIU(rd, rs1, imm) _Itype(_jit, 12307, rd, rs1, imm)

#define SLTU(rd, rs1, rs2) _Rtype(_jit, 12339, rd, rs1, rs2)

#define SRA(rd, rs1, rs2) _Rtype(_jit, 1073762355, rd, rs1, rs2)

#define SRAW(rd, rs1, rs2) _Rtype(_jit, 1073762363, rd, rs1, rs2)

#define SRET() _Rtype(_jit, 270532723)

#define SRL(rd, rs1, rs2) _Rtype(_jit, 20531, rd, rs1, rs2)

#define SRLW(rd, rs1, rs2) _Rtype(_jit, 20539, rd, rs1, rs2)

#define SUB(rd, rs1, rs2) _Rtype(_jit, 1073741875, rd, rs1, rs2)

#define SUBW(rd, rs1, rs2) _Rtype(_jit, 1073741883, rd, rs1, rs2)

#define SW(rs1, rs2, imm) _Stype(_jit, 8227, rs1, rs2, imm)

#define SW_CAP(rs1, rs2) _CheriTwoSrctype(_jit, 4160750939, rs1, rs2)

#define SW_DDC(rs1, rs2) _CheriTwoSrctype(_jit, 4160749915, rs1, rs2)

#define UNIMP() _Itype(_jit, 3221229683)

#define URET() _Rtype(_jit, 2097267)

#define WFI() _Rtype(_jit, 273678451)

#define XOR(rd, rs1, rs2) _Rtype(_jit, 16435, rd, rs1, rs2)

#define XORI(rd, rs1, imm) _Itype(_jit, 16403, rd, rs1, imm)


