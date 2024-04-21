An expansion for DSLinux

Install packages from the www/ folder by running...

```
tar -xvf package.tar -C / 
```

You can run coreutils-init.sh to copy files from coreutils to the /usr/bin/ folder, which enables some useful commands like `wc`. `base64`, and `bc`. However, the developers probably did not do this because some are buggy, such as `printf` which just seems to crash. Inside of the www/ folder you may find some redundant packages that are also in coreutils. Try one of these redundant ports if one of the coreutils ones are buggy.

NOTE: The version of WGET here is a later version but without SSL (meaning HTTPS websites don't work). I am still trying to figure out how to get SSL to work with it. The version of WGET in DSLinux by default has SSL support but it is outdated and so a lot of websites it won't download from. 
