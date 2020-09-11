# cheri-instruction-rcg-gen
Generate Runtime Code Generation library from json descriptions extracted from llvm-tblgen using `--dump-json`


Build:

```bash
cd transforms
nimble build
```

Generating an assembler:

```bash
./transform --backend=lightning 
./transform --backend=c
```
