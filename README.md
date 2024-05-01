An expansion for DSLinux

Install packages from the www/ folder by running...

```
tar -xvf package.tar -C / 
```

You can run coreutils-init.sh to copy files from coreutils to the /usr/bin/ folder, which enables some useful commands like `wc`. `base64`, and `bc`. However, the developers probably did not do this because some are buggy, such as `printf` which just seems to crash. Inside of the www/ folder you may find some redundant packages that are also in coreutils. Try one of these redundant ports if one of the coreutils ones are buggy.

## Lua

The `lua.tar` package contains both the Lua5 interpreter and compiler compiled with POSIX support. DSLinux by default has no methodology, outside of shell scripts, to write software on the console itself. This allows for writing Lua code and compiling it and running it on the NDS itself, and it runs quite fast.

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
_str: .equ str, 0
  .ascii "Hello, World!\n"
  .equ strlen, . - _str
```

System calls are made using the `swi` instruction and their addresses are included in the `unistd.s` file. One thing that is a bit different here is the `ldr r1, [sl, #0]` line. Because the NDS lacks an MMU, it can't use virtual memory addreses. When you a label like `_str`, at compile time this compiles down to some memory address. Usually, at runtime, this memory address is treated as "virtual" because the MMU will remap it to some physical memory address based on the operating system's needs. Since the NDS can't do this, we can't actually directly reference any memory addreses like `_str` since their addresses will differ between at compile time and at run time.

There are two solutions to this. The first is to just never use absolute memory addresses. You can make everything relative, such as, by pushing data to the stack, then referencing the data at the stack pointer. However, the operating system actually does provide a way to use the `.data` segment, and that's with something called a _global offset table for position independent code_, or _gotpic_ for short. If your program uses a global offset table, then at runtime, the operating system will provide a table which you can access in your code that lists where all your data was actually loaded into memory. It then stores this offset table at a memory address pointed to by the `sl` register, which is just `r10`.

My `o2bflt` will setup the offset table for you. It sets it up so that the order your labels appear in the `.data` segment is equivalent to their index into the global offset table (if you add a `.rodata` or `.bss`, the will just be concatenated onto the end of `.data.` in that order). In this case, `_str` is our very first label, so its index into the table is `0`, and I also go ahead and define constant for its index using `.equ str, 0`.  If we added another label, the index to that would be `4` because memory addresses are 32-bits, so each entry into the offset table is 4 bytes.

This is why we have the `ldr r1, [sl, #str]` instruction. It is saying to look for a pointer located at `sl` with an offset of `#str`, and then use that pointer to look up a memory address, and store that into `r1`. In this case, `r1` will get wherever the value `_str` was loaded into at runtime. If we had another label, we could load the second label's runtime memory address into `r1` by defining a constant such as `.equ str2, 4` and referencing it using `ldr r1, [sl, #str2]`. Note that it does not matter how long a single labeled chunk of data is in the `.data` segment. All that matters is the ordering of the labels. If you create a string called `_str` then one called `_str2` and the former is 8 bytes long and the latter 100, they could still only be index `0` and `4` respectively.

## ftp

An alternative to `ncftp` that ships with DSLinux.

## awk

Another useful command ported here is `awk` found in the `awk.tar` package, which is itself an entire scripting language, but typically used for processing output of other commands in shel scripts. This is actually built from the `mawk` source code but just renamed to `awk`. It is also possible to install `awk` by enabling it in the `busybox` configuration when compiling.

## wget

The version of `wget` here in the `wget.tar` package is a later version but without SSL support (meaning HTTPS websites don't work). The `wget` in DSLinux by default has SSL support but it is outdated and so it fails to form an SSL connection on many websites. The SSL code for the later version of `wget` seems to build but crash when actually used, so it is built without SSL support. You can choose either to stick with the older version of `wget` with finnicky SSL support, or the newer one without it, depending on your preference.

## zedex

The `zedex` interpreter is a custom interpreter I've written that allows you run programs on Linux systems compiled with the Small Device C Compiler. This is slower than writing native applications, but might be more convenient if you just want to put something together quickly, as it allows you to run code in DSLinux that has been compiled using a modern compiler (it requires at least SDCC v4.2 to work). You can follow the README at [my other repository](https://github.com/amihart/Zedex/) to learn how to compile code that can be ran with `zedex`. Inside of the `conf/` folder in that repository is a `unistd.h.arm` file that I generated for DSLinux, so you do not need to generate it yourself, but you can if you wish.

