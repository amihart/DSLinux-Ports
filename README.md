An expansion for DSLinux

Install packages from the www/ folder by running...

```
tar -xvf package.tar -C / 
```

You can run coreutils-init.sh to copy files from coreutils to the /usr/bin/ folder, which enables some useful commands like `wc`. `base64`, and `bc`. Inside of the www/ folder you may find some redundant packages that are also in coreutils. Try one of these redundant ports if you want a later version.

## Lua

The `lua.tar` package contains both the Lua5 interpreter and compiler compiled with POSIX support. 

## Dropbear

Probably the most useful thing in this repository is an updated version of `ssh` and `scp` which is found in the `dropbear.tar` package. This allows you to SSH into a modern device without having to downgrade your security in the `/etc/ssh/sshd_config` settings.

## NFS

The `kernel.nds` is a kernel built with support for mounting drives over the network with NFSv2 or NFSv3. The kernel also fixes the `Unknown error` issue as it is compiles with error messages.

## nano

The version of `nano` that comes with DSLinux is `1.2.5`. The version here is much more up to date at `6.0.0`. The package also includes syntax highlighting profiles for Lua, SH, C, Perl, and assembly. 

![image](https://github.com/amihart/DSLinux-Ports/assets/6305912/eef2cd73-a2cb-4bd8-9877-1ef7505b4048)

This version opens a bit slowly on the NDS, so I also ported `texor` which is the simplest text editor I'm aware of that is actually decent, so if you want to do a quick edit and don't care about the fancy nano features, then you can use `texor`.

## fibonacci

The package `fibonacci.tar` is not actually a port but merely an example of how you can make a package for DSLinux with Lua. The package is distributed using a shell script in `/usr/bin/` which calls the Lua script in `/usr/share`. The package is distributed with the Lua source code, but if you compile with `luac` you can also distribute the package with a binary. For some reason, if you compile with `luac` on your PC and transfer it to your NDS, it gives an error when you try to run it. You have to compile it with `luac` on the NDS itself. Not entirely sure why, it might be an endianness issue, or something else. 

## picoc

Sadly, there will likely never be `gcc` ported to run on DSLinux itself. Apparently, it has to be patched to even handle memory correctly, and I am unsure how the original developers patched it to make their x86 version. The best alternative would be a C interpreter which could be compiled targeting DSLinux in the x86 version of `gcc`, and thus should handle memory correctly. This is what `picoc` is, a port of the last version (as it seems to be abandoned) of the `picoc` C interpreter. It is not a compiler but interprets C code as scripts. It is possible to make packages with it using the same method as shown with `fibonacci` above.

## gas

The `binutils-2.13` package has a working version of the GNU assembler. This is the only way currently (that I am aware of) to create binaries on the NDS itself. Although, the assembler is actually incapable of outputting binaries in the format DSLinux recognizes (bFLT gotpic v4). I created my own `o2bflt` command that comes with the `binutils-2.13` package that lets you create them. It doesn't support every feature of ELF object files but it does enough so that you can write assembly code by hand and build it to something that can be executed all on the NDS itself. Below is an example of a "Hello, World!" program.

```as
.include "/usr/include/unistd.s"
.global _start
.section .text
_start:
  mov r0, #STDOUT_FILENO
  ldr r1, [sl, #str]
  mov r2, #strlen
  swi __NR_write
  mov r0, #0
  swi __NR_exit
.section .data
data str
  .ascii "Hello, World!\n"
  .equ strlen, . - _str
```

```sh
$ as hello.s -o hello.o
$ o2bflt hello.o
$ ./hello
Hello, World!
```

System calls are made using the `swi` instruction and their addresses are included in the `unistd.s` file. One thing that is a bit different here is the `ldr r1, [sl, #str]` line. Because the NDS lacks an MMU, it can't use virtual memory addresses. When you use a label like `_str`, at compile time this compiles down to some memory address. Usually, at runtime, this memory address is treated as "virtual" because the MMU will remap it to some physical memory address based on the operating system's needs at runtime. Since the NDS can't do this, we can't actually directly reference any memory addreses like `_str` since their addresses will differ between at compile time and at run time.

There are two solutions to this. The first is to just never use absolute memory addresses. You can make everything relative, such as, by pushing data to the stack, then referencing the data at the stack pointer. However, the operating system actually does provide a way to use the `.data` segment, and that's with something called a _global offset table for position independent code_, or _gotpic_ for short. If your program uses a global offset table, then at runtime, the operating system will provide a table which you can access in your code that lists where all your data was actually loaded into memory. It then stores this offset table at a memory address pointed to by the `sl` register, which is just `r10`.

My `o2bflt` will setup the offset table for you as well as a `data` macro which both creates the label for you as well as a constant with its index into the global offset table. That's what the line `data str` is doing, it is using the macro which creates a label `_str` as well as a constant `str` where `str` is the index in the global offset table for `_str`. At runtime, you cannot call `_str` directly because you do not know where it might be loaded into memory, but you know the global offset table is stored in `sl` and the index wll be `str`, so you can use that to call `ldr r1, [sl, #str]` which goes to the global offset table at `sl` with an offset of `str` and loads the pointer from there into `r1`. 

Please report any bugs in `o2bflt` to this repository.

## ftp

An alternative to `ncftp` that ships with DSLinux.

## awk

Another useful command ported here is `awk` found in the `awk.tar` package, which is itself an entire scripting language, but typically used for processing output of other commands in shel scripts. This is actually built from the `mawk` source code but just renamed to `awk`. It is also possible to install `awk` by enabling it in the `busybox` configuration when compiling.

## wget

The version of `wget` here in the `wget.tar` package is a later version but without SSL support (meaning HTTPS websites don't work). The `wget` in DSLinux by default has SSL support but it is outdated and so it fails to form an SSL connection on many websites. The SSL code for the later version of `wget` seems to build but crash when actually used, so it is built without SSL support. You can choose either to stick with the older version of `wget` with finnicky SSL support, or the newer one without it, depending on your preference.

## zedex

The `zedex` interpreter is a custom interpreter I've written that allows you run programs on Linux systems compiled with the Small Device C Compiler. This is slower than writing native applications, but might be more convenient if you just want to put something together quickly, as it allows you to run code in DSLinux that has been compiled using a modern compiler (it requires at least SDCC v4.2 to work). You can follow the README at [my other repository](https://github.com/amihart/Zedex/) to learn how to compile code that can be ran with `zedex`. Inside of the `conf/` folder in that repository is a `unistd.h.arm` file that I generated for DSLinux, so you do not need to generate it yourself, but you can if you wish.

## bug with paths

Some software seems to have a bug where it only opens things on the home directory. It helps to treat your home directory as the "working" directory for stuff you're actually working on at the moment, and moving it to other folders when you're done working with it. 
