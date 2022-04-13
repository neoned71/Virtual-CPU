# Virtual-CPU
A stackful virtual CPU written in **`C++`**. All operations are done using **stack**.
CPU registers are there but only for the most basic purposes, like `instruction pointer`, `stack pointer` and `base pointer`.

### Compilation
 To compile the machine on a linux platform, run: `g++ simulator.cpp machine.cpp instructions.hpp -o machine`
