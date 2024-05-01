DOWNLOAD=$(cat .git/config | grep url | sed 's/.*=//;s/[Zz]edex/Zeditty/')
CFLAGS="$CFLAGS -IZeditty/include -std=gnu99 -Wall"
LDFLAGS="$LDFLAGS -LZeditty/lib -lzeditty"
DEPS="sdcc srec_cat bc xargs"
if [ "$CC" = "" ]
then
	CC=cc
fi

for i in $DEPS
do
	if ! which>/dev/null $i
	then
		d=$i
		if [ "$i" = "srec_cat" ]
		then
			d=srecord
		fi
		echo Please install \`$d\`.
		exit 1
	fi
done


if [ ! -d "Zeditty" ]
then
	git clone $DOWNLOAD
	if [ "$?" != "0" ]
	then
		echo "Could not fetch \`zeditty\` dependency."
		echo "Please make sure you cloned this project from the github."
		exit 1
	fi
fi

make -C Zeditty/
mkdir -p bin/
$CC -S src/call_table.c -o src/call_table.s
callsize=$(cat src/call_table.s | grep -i '\.size' | grep 'CALL_TABLE' | sed 's/.*,//' | xargs)
callsize=$(echo $callsize / 8 | bc)
if [ "$callsize" = "" ]
then
	echo "Failed to compute call table size."
	exit 1
fi

$CC $CFLAGS -c src/call_table.c -o src/call_table.o
$CC $CFLAGS -c src/zedex.c -o src/zedex.o -DCALL_TABLE_SIZE=$callsize
$CC $CFLAGS -o bin/zedex src/call_table.o src/zedex.o $LDFLAGS
rm -f .call_table_size

# can't build this on this version of linux, too old
# sdasz80 -o bin/crt0.rel src/crt0.s
