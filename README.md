An expansion for DSLinux

Run coreutils-init.sh to copy files from the coreutils folder into /usr/bin. This probably was not done by the developers automatically because some of these commands seem to be broken (such as printf), but many others seem to work fine (base64, sha commands, wc, yes, etc) and are very useful.

##Package Manager

The spkmg is a package manager which can be used to pull packages from a website hosting the www/ folder as an HTTP file server (such as with php -S).  You don't need the package manager to install any 
```
tar -cx
```



The spkmg is a package manager which can be used to pull packages from a website hosting the www folder as an HTTP file server (such as with php -S). You have to place spkgm in /usr/bin, run "spkgm init", then add the website URL to /etc/spkgm/sources.list. Then, you merely need to run "spkgm update" then "spkgm search somepackage" to look for a package, then "spkgm 




should be placed in /usr/bin as well and is a package manager. Run "spkmg init" to initialize it. You need to host the packages somewhere. The next section will discuss a way to host 

## File Transf

The easiest way to do it is with a Raspberry Pi which you can install RaspAP and do not connect it to your router. This will have the Pi host a local WiFi network that, if anything connects, it will have no internet access, so you can safely make this public (no password). You can



If you have an Android smartphone, you can install F-Droid and then with F-Droid install Termux, and with Termux you can host a PHP server on your phone.  On your smartphone, install F-Droid then inside of 

The web folder holds the packages. Host this on a device by changing the current directory to inside the web folder and using "php -S yourip:8080" to host it on your local network, then you can add yourip:8080 (replacing "yourip" with your actual local IP address, not your public IP address) to /etc/spkgm/sources.list. Once you  
