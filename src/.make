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
mkdir -p usr/bin/
mkdir -p usr/share/
mkdir -p www/
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
			echo "building $pathdir2..."
			cd "$pathdir2"
			make clean
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
		fi
		pathdir2="$pathclen"
		pathdir3=""
		makecmds="`echo $i | sed 's/.*://;s/\,/ /g' | xargs`"
		beginning=0
	fi
done
exit

#all:
#	mkdir -p usr/
#	mkdir -p usr/bin/
#	mkdir -p www/
#	cp ../awk/awk usr/bin/
#	cp ../wget2/src/wget usr/bin/
#	tar -cvf www/bc.tar usr/bin/bc usr/bin/dc
#	tar -cvf www/realpath.tar usr/bin/realpath
#	tar -cvf www/lua.tar usr/bin/lua usr/bin/luac
#	tar -cvf www/bflt-utils.tar usr/bin/flthdr usr/bin/readbflt
#	tar -cvf www/xxd.tar usr/bin/xxd
#	tar -cvf www/sha256sum.tar usr/bin/sha256sum
#	tar -cvf www/units.tar usr/bin/units
#	tar -cvf www/ftp.tar usr/bin/ftp
#	tar -cvf www/awk.tar usr/bin/awk
#	tar -cvf www/wc.tar usr/bin/wc
#	tar -cvf www/fibonacci.tar usr/bin/fibonacci usr/share/fibonacci.lua
#	tar -cvf www/tinybasic.tar usr/bin/tinybasic
#	tar -cvf www/fdisk.tar usr/bin/fdisk
#	tar -cvf www/dropbear.tar usr/bin/dropbear* usr/bin/dbclient usr/bin/ssh usr/bin/scp
#	tar -cvf www/wget.tar usr/bin/wget
#	tar -cvf www/texor.tar usr/bin/texor
#	ls www/*.tar | sed 's/.*[/]//;s/[.]tar//' > www/.list
#	tar -cvf expansion.tar usr/bin/*
#	tar -cvf www.tar www/.list www/*
#
#clean:
#	rm -r usr/ www/ expansion.tar www.tar
