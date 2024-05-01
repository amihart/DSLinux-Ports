#!/bin/sh

paths='
	!binutils-2.13:@
		code/gas/as-new.gdb		usr/bin/as
		code/gprof/gprof.gdb		usr/bin/gprof
		code/binutils/cxxfilt.gdb	usr/bin/cxxfilt
		code/binutils/objdump.gdb	usr/bin/objdump
		code/binutils/strings.gdb	usr/bin/strings
		code/binutils/size.gdb		usr/bin/size
		code/binutils/objcopy.gdb	usr/bin/objcopy
		code/binutils/ar.gdb		usr/bin/ar
		code/binutils/ranlib.gdb	usr/bin/ranlib
		code/binutils/strip-new.gdb	usr/bin/strip
		code/binutils/addr2line.gdb	usr/bin/addr2line
		code/binutils/nm-new.gdb	usr/bin/nm
		code/ld/ld-new.gdb		usr/bin/ld
		o2bflt/o2bflt			usr/bin/o2bflt
		unistd.s			usr/include/unistd.s
	!texor:@
		texor			usr/bin/texor
	!ftp:@
		ftp/ftp			usr/bin/ftp
	!dropbear:@,scp
		dropbear		usr/bin/dropbear
		dropbearconvert		usr/bin/dropbearconvert
		dropbearkey		usr/bin/dropbearkey
		dbclient		usr/bin/dbclient
		dbclient		usr/bin/ssh
		scp			usr/bin/scp
	!lua-5.4.6:@
		src/lua			usr/bin/lua
		src/luac		usr/bin/luac
	!xxd:@
		xxd			usr/bin/xxd
	!realpath:@
		realpath		usr/bin/realpath
	!bflt-utils:@
		flthdr/flthdr		usr/bin/flthdr
		readbflt/readbflt	usr/bin/readbflt
	!fdisk:fdisk
		fdisk			usr/bin/fdisk
	!wcp:@
		wc			usr/bin/wc
	!netflash:@,sha256sum,hmacmd5
		netflash		usr/bin/netflash
		sha256sum		usr/bin/sha256sum
		hmacmd5			usr/bin/hmacmd5
	!units-1.86:@
		units			usr/bin/units
	!TinyBASIC:@
		TinyBASIC		usr/bin/tinybasic
	!fibonacci:@
		fibonacci.sh		usr/bin/fibonacci
		fibonacci.lua		usr/share/fibonacci.lua
	!wget/src:@
		wget			usr/bin/wget
	!bc-1.07:@
		bc/bc			usr/bin/bc
		dc/dc			usr/bin/dc
	!mawk:mawk
		mawk			usr/bin/awk
	!nano-6.0:@
		code/src/nano		usr/share/nano/binary
		profiles/lua.nanorc	usr/share/nano/lua.nanorc
		profiles/sh.nanorc	usr/share/nano/sh.nanorc
		profiles/pl.nanorc	usr/share/nano/pl.nanorc
		profiles/s.nanorc	usr/share/nano/s.nanorc
		profiles/c.nanorc	usr/share/nano/c.nanorc
		launcher		usr/bin/nano
	!make-3.81:@
		make			usr/bin/make
	!tar-1.30:@
		src/tar			usr/bin/tar
	!picoc-3.2.2:@
		picoc			usr/bin/picoc
	!free-3.3.13:@
		free			usr/bin/free
	!sdcc-2.4.0:@
		bin/as-gbz80		usr/bin/as-gbz80
		bin/as-hc08		usr/bin/as-hc08
		bin/aslink		usr/bin/aslink
		bin/asx8051		usr/bin/asx8051
		bin/as-z80		usr/bin/as-z80
		bin/link-gbz80		usr/bin/link-gbz80
		bin/link-hc08		usr/bin/link-hc08
		bin/link-z80		usr/bin/link-z80
		bin/makebin		usr/bin/makebin
		bin/sdcc		usr/bin/sdcc
		bin/sdcclib		usr/bin/sdcclib
		bin/sdcpp		usr/bin/sdcpp
	!zedex:@
		bin/zedex		usr/bin/zedex
	!
'
paths=$(echo "$paths" | xargs)

if [ "$CC" = "" ]
then
	echo 'Error: use the `make xsh` environment'
	exit
fi

pathdir1="`pwd`"
pathdir2=""
pathdir3=""
makecmds=""
if [ "$1" = "clean" ]
then
	rm -rf usr/ www/
else
	mkdir www/
fi

# make -C lib/
beginning=1
for i in $paths
do
	pathclen=`echo $i | sed 's/!//;s/:.*//'`
	if [ "$pathclen" = "$i" ]
	then
		pathdir3="$pathdir3 $i"
	else
		if [ "$beginning" = "0" ]
		then
			if [ "$1" != "clean" ]
			then
				echo "cleaning $pathdir2..."
			else
				echo "building $pathdir2..."
			fi
			cd "$pathdir2"
			make clean
			if [ "$?" != "0" ]
			then
				exit
			fi
			if [ "$1" != "clean" ]
			then
				for j in $makecmds
				do
					if [ "$j" = "@" ]
					then
						make
					else
						make $j
					fi
				done
				cd "$pathdir1"
				count=`echo $pathdir3 | awk '{ print NF }'`
				pkgdir=`echo $pathdir2 | sed 's/\/.*//'`.tar
				lstdir=""
				for j in `seq 1 2 $count`
				do
					k=$(expr $j + 1)
					fr=$(echo $pathdir3 | awk "{ print \$$j }")
					to=$(echo $pathdir3 | awk "{ print \$$k }")
					fr=$pathdir2/$fr
					echo $fr '=>' $to
					mkdir -p `dirname "$to"`
					cp "$fr" "$to"
					lstdir="$lstdir $to"
				done
				tar -cvf www/$pkgdir $lstdir
			else
				cd "$pathdir1"
			fi
		fi
		pathdir2="$pathclen"
		pathdir3=""
		makecmds="`echo $i | sed 's/.*://;s/\,/ /g' | xargs`"
		beginning=0
		sh .unpatch
	fi
done

rm -f www.tar
tar -cvf www.tar www/
exit
