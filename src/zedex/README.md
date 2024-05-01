# Zedex
Zilog Z80 Interpreter. The interpreter supports `putchar()`, `getchar()`, command line arguments, return values, and arbitrary Linux system calls.

## Compiling C Programs for Zedex

Programs are to be compiled in the Small Device C Compiler version >= 4.2. Older versions may be supported in the future.

To create a program for the interpreter, write a C program as you normally would, such as the example below.

```C
#include <stdio.h>

int main()
{
	printf("Hello, World!\n");
	return 0;
}
```

Then, compile it with the Small Device C Compiler targeting Z80 systems using the `crt0.rel` file in this repository.

```sh
sdcc ../bin/crt0.rel -mz80 --no-std-crt0 hello_world.c -o ~tmp.hex -I../include
````

Here, we compile to a `~tmp.hex` file because `sdcc` will produce many files we do not need, and this makes it easier to clean them up. The compiled code is in the `~tmp.hex` file but not in a format we can immediately use. The Small Device C Compiler comes with a `makebin` command for converting these files to binaries, but it is preferable to instead install the `srecord` package and use the `srec_cat` command.

```sh
srec_cat ~tmp.hex -Intel -Output -Binary > hello_world.z80
rm ~tmp*
```

Once a program is compiled, it can then be ran simply by passing it in as an argument to the interpeter.

```sh
$ zedex hello_world.z80
Hello, World!
```

Anything after the first command-line argument for `zedex` (the first command-line argument is the file name to run) will be passed in as command-line arguments to the interpreted program (which can be accessed using the `int main(int argc, char** argv)` function signature). The `zedex` command will also return with the return value set by the executed program.


## Linux System Calls

If the utility you are developing needs more features than standard input, standard output, command-line arguments, and return values, then it is possible to make a Linux system call in order to extend the program's functionality. For example, below is a `Hello, World!` program that uses the `__NR_write` system call.

```C
#include <unistd.h>
#include <sys/syscall.h>

void main()
{
	char str[] = "Hello, World!\n";
	syscall(__NR_write, 1, str, sizeof(str));
}
```

System calls require a valid `unistd.h` header file. The `conf/autogen.sh` script can assist you in creating one for your machine, but there is already a `unistd.h.x86_64` file in the repository that simply needs to be renamed to `unistd.h` and moved to the `includes/` folder. You sometimes might just be able to include the `/usr/include/asm-generic/unistd.h` file on your system, but sometimes I find this does not have the correct values. 
