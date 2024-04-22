#!/bin/sh
paths='
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
		fibonacci		usr/bin/fibonacci
		fibonacci.lc		usr/share/fibonacci
	!wget/src:@
		wget			usr/bin/wget
	!bc-1.07:@
		bc/bc			usr/bin/bc
		dc/dc			usr/bin/dc
	!mawk:mawk
		mawk			usr/bin/awk
	!nano-6.0:@
		code/src/nano		usr/bin/nano
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
	mkdir -p usr/bin/
	mkdir -p usr/share/
	mkdir -p www/
fi
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
	fi
done
exit
