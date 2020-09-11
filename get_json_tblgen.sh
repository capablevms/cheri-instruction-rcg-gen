#!/bin/bash
CHERI_LLVM_SRC=~/cheri/llvm-project/llvm/lib/Target/RISCV
# Find the current dir of this script: https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd $CHERI_LLVM_SRC
llvm-tblgen RISCV.td -I ../../../include --dump-json > $DIR/defs/riscv.json
