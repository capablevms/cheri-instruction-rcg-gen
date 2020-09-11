# cheri-instruction-rcg-gen
Generate Runtime Code Generation library from json descriptions extracted from llvm-tblgen using `--dump-json`


Build:

```sh
cd transforms
nimble build
```

It is possible to generate 2 different assemblers.
On generic one, and one taht can be used with gnulightning.
Generating an assembler:

```sh
./transform --backend=lightning 
./transform --backend=c
```
