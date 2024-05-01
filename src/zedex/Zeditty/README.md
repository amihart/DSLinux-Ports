# Zeditty
A Zilog Z80 interpreter library for C programs.

![img](https://github.com/amihart/CZ80LIB/raw/main/doc/doc.png)

## Usage

See the `/test` folder for an example. The `hello.c` file is a simple program that asks the user for their name and then outputs `Hello, [name]`! The `Makefile` in the `/test` folder will build this with the `Small Device C Compiler` and also compile a program called `interpret` using the `zeditty` library. If you run the `interpret` program, it will execute the `hello.z80` program.

If you open the `interpret.c` file, you can see how simple it is to begin interpreting Z80 code. You just have to load the file and run it, while also defining port callbacks. Interrupt callbacks are also supported. In order to get `sdcc` to compile a program properly, you have to define a `crt0.s` file. In this case, I built a simple file that calls the `_main` function and then writes to port 1. The `interpret.c` file interpets a write to port 1 as equivalent to `exit()`. It interpets a write to port 0 as `putchar()` and a read from port 0 as `getchar()`. These are also defined in the `crt0.s` file as well using the new SDCC calling convention (meaning, the `crt0.s` will need to be changed if you are using an old version of `sdcc`).
