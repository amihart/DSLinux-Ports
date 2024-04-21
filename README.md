An expansion for DSLinux

Install packages from the www/ folder by running...

```
tar -xvf package.tar -C / 
```

You can run coreutils-init.sh to copy files from coreutils to the /usr/bin/ folder, which enables some useful commands like `wc`. `base64`, and `bc`. However, the developers probably did not do this because some are buggy, such as `printf` which just seems to crash. Inside of the www/ folder you may find some redundant packages that are also in coreutils. Try one of these redundant ports if one of the coreutils ones are buggy.

NOTE: The version of `wget` here is a later version but without SSL support (meaning HTTPS websites don't work), so it is probably not worth downloading. The version of `wget` in DSLinux by default has SSL support but it is outdated and so it fails to form an SSL connection on many websites. The SSL code for the later version of `wget` seems to build but crash when actually used, so unless this ever gets resolved then you can either choose an older version of `wget` with SSL support or a newer version without it.
