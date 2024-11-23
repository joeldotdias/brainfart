# Brainfart

A compiler that generates x86_64 assembly (AT&T syntax) for brainfuck.

All emitted assembly files are in the `out` directory.

## Usage
- Run `make` to build the binary. Change the compiler if needed.
- Compile the source file

```
brainflip fibonacci.bf  # compiles into fibonacci.s
```
- Compile and link the generated assembly
```
gcc -c fibonacci.s && ld fibonacci.o -o fibonacci
```
- Run the binary
```
./fibonacci
```

## TODO
- [ ] Compile to RISC-V 64 bit assembly
- [ ] Implement a visualizer for the memory tape
