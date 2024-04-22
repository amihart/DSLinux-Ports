all:
	mkdir -p usr/
	mkdir -p usr/bin/
	mkdir -p www/
	cp ../bc-1.07/bc/bc usr/bin/
	cp ../bc-1.07/dc/dc usr/bin/
	cp ../realpath/realpath usr/bin/
	#cp ../lua-4.0.0/bin/lua usr/bin/
	#cp ../lua-4.0.0/bin/luac usr/bin/
	cp ../lua-5.4.6/src/lua usr/bin/
	cp ../lua-5.4.6/src/luac usr/bin/
	cp ../ftp/ftp/ftp usr/bin/
	cp ../netflash/sha256sum usr/bin/
	cp ../units-1.86/units usr/bin/
	cp ../bflt-utils/flthdr/flthdr usr/bin/
	cp ../bflt-utils/readbflt/readbflt usr/bin/
	cp ../xxd/xxd usr/bin/
	cp ../awk/awk usr/bin/
	cp ../wcp/wc usr/bin/
	cp ../TinyBASIC/TinyBASIC usr/bin/tinybasic
	cp -r ../fibonacci/usr/* usr/
	cp ../fdisk/fdisk usr/bin/
	cp ../dropbear2/dropbear usr/bin/
	cp ../dropbear2/dropbearconvert usr/bin/
	cp ../dropbear2/dropbearkey usr/bin/
	cp ../dropbear2/dbclient usr/bin/
	cp ../dropbear2/dbclient usr/bin/ssh
	cp ../dropbear2/scp usr/bin/
	cp ../wget2/src/wget usr/bin/
	cp ../texor/texor usr/bin/
	tar -cvf www/bc.tar usr/bin/bc usr/bin/dc
	tar -cvf www/realpath.tar usr/bin/realpath
	tar -cvf www/lua.tar usr/bin/lua usr/bin/luac
	tar -cvf www/bflt-utils.tar usr/bin/flthdr usr/bin/readbflt
	tar -cvf www/xxd.tar usr/bin/xxd
	tar -cvf www/sha256sum.tar usr/bin/sha256sum
	tar -cvf www/units.tar usr/bin/units
	tar -cvf www/ftp.tar usr/bin/ftp
	tar -cvf www/awk.tar usr/bin/awk
	tar -cvf www/wc.tar usr/bin/wc
	tar -cvf www/fibonacci.tar usr/bin/fibonacci usr/share/fibonacci.lua
	tar -cvf www/tinybasic.tar usr/bin/tinybasic
	tar -cvf www/fdisk.tar usr/bin/fdisk
	tar -cvf www/dropbear.tar usr/bin/dropbear* usr/bin/dbclient usr/bin/ssh usr/bin/scp
	tar -cvf www/wget.tar usr/bin/wget
	tar -cvf www/texor.tar usr/bin/texor
	ls www/*.tar | sed 's/.*[/]//;s/[.]tar//' > www/.list
	tar -cvf expansion.tar usr/bin/*
	tar -cvf www.tar www/.list www/*

clean:
	rm -r usr/ www/ expansion.tar www.tar
