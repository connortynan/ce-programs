# ti84plusce-programs
Various programs for the TI84 Plus CE calculator, written in TI-BASIC and C.

Files are stored as a src directory for viewable source code, and a bin directory containing compiled `.8xp` files 

TI-BASIC programs are difficult to share in a plaintext, so i just put them in `.tibasic` files (equivalent to a `.txt` file, I just wanted to be quirky) You could put the `.8xp` files in TI Connect CE to view the code, but I made them less readable to reduce file size on the calculator.

**NOTE: C Programs are made using [CE C/C++ Toolchain](https://github.com/CE-Programming/toolchain), and probably require [Libload](https://github.com/CE-Programming/libload) to run.**

## [char-star-int](char-star-int) (TI-BASIC)
A solution to this coding problem, all in TI-BASIC:
```
// Give the output of this code
// (assuming a little endian machine)

#include <stdio.h>

int main(int argc, char* argv[]) {
  unsigned long long x = {CAREFULLY CRAFTED MAGIC NUMBER};
  printf("%s\n", (char*) &x);
}
```
Basically just divides a big number by 256 a bunch and finds characters in a look up table, but works with arbitrarily large inputs, avoiding the automatic rounding at values >10^10, preserving exact integer values no matter how big the numbers are.

## [str-int-functions](str-int-functions) (TI-BASIC)
Performs arithmetic on arbitrarily large integers, using strings to store digits to avoid the calculator rounding values >10^10.
This allows for large numbers to be calculated while maintaining the exact integer value for applications involving modulo (or some other reason for unrounded large integer values)

To use: Input positive integer values in both inputs, string conversion happens automatically

- ***STRIADD (StrIntAdd)***
  - Adds two positive integers, maintaining exact unrounded values
- ***STRIDIV (StrIntDiv)***
  - Divides a positive integer by a positive integer, giving the exact quotient and remainder
  - **NOTE: Divisor is not stored as a string, so divisor values greater than 10^10 will result in a rounded answer!**
- ***STRIMULT (StrIntMult)***
  - Multiplies two positive integers, maintaining unrounded values
- ***STRISUB (StrIntSub)***
  - Subtracts two positive integers, maintaining unrounded values
  - **NOTE: result cannot be negative, if the second input is larger than the first, the answer will be incorrect!**


## [ti-canvas](ti-canvas) (C)
Currently a WIP/library project, uses graphx to draw images with RGB dithering.

Build Instructions: Follow the section [Building Programs](https://ce-programming.github.io/toolchain/static/getting-started.html#building-programs) on the toolchain wiki.
- Launch the compiler terminal
  - Windows: Open `cedev.bat` in your `CEdev` folder
  - Linux/MacOS Launch a terminal session
- Navigate to `..../ce-programs/ti-canvas`
- Run `make`
- Profit. (compiles to `bin/CANVAS.8xp`)