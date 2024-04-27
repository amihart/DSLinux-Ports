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

The version of `nano` that comes with DSLinux is `1.2.5`. The version here is much more up to date at `6.0.0`. The package also includes syntax highlighting profiles for Lua and shell scripts. 

![image](https://github.com/amihart/DSLinux-Ports/assets/6305912/eef2cd73-a2cb-4bd8-9877-1ef7505b4048)

This version opens a bit slowly on the NDS, so I also ported `texor` which is the simplest text editor I'm aware of that is actually decent, so if you want to do a quick edit and don't care about the fancy nano features, then you can use `texor`.

## fibonacci

The package `fibonacci.tar` is not actually a port but merely an example of how you can make a package for DSLinux with Lua. The package is distributed using a shell script in `/usr/bin/` which calls the Lua script in `/usr/share`. The package is distributed with the Lua source code, but if you compile with `luac` you can also distribute the package with a binary. For some reason, if you compile with `luac` on your PC and transfer it to your NDS, it gives an error when you try to run it. You have to compile it with `luac` on the NDS itself. Not entirely sure why, it might be an endianness issue, or something else. 

## picoc

Sadly, there will likely never be `gcc` ported to run on DSLinux itself. Apparently, it has to be patched to even handle memory correctly, and I am unsure how the original developers patched it to make their x86 version. The best alternative would be a C interpreter which could be compiled targeting DSLinux in the x86 version of `gcc`, and thus should handle memory correctly. This is what `picoc` is, a port of the last version (as it seems to be abandoned) of the `picoc` C interpreter. It is not a compiler but interprets C code as scripts. It is possible to make packages with it using the same method as shown with `fibonacci` above.

## ftp

An alternative to `ncftp` that ships with DSLinux.

## awk

Another useful command ported here is `awk` found in the `awk.tar` package, which is itself an entire scripting language, but typically used for processing output of other commands in shel scripts. This is actually built from the `mawk` source code but just renamed to `awk`. It is also possible to install `awk` by enabling it in the `busybox` configuration when compiling.

## wget

The version of `wget` here in the `wget.tar` package is a later version but without SSL support (meaning HTTPS websites don't work). The `wget` in DSLinux by default has SSL support but it is outdated and so it fails to form an SSL connection on many websites. The SSL code for the later version of `wget` seems to build but crash when actually used, so it is built without SSL support. You can choose either to stick with the older version of `wget` with finnicky SSL support, or the newer one without it, depending on your preference.
