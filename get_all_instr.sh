# Can obtain everything throuth llvm-tblgen
# Get all isntructions but remove the pseudo ones

jq '.[] | select(.|type == "object") | select(.isPseudo == 0)' defs/riscv.json | jq -s

