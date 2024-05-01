INCLUDES=" -I$(pwd)/include -I$(pwd) "
#COMPILE="gcc"
COMPILE="ucfront-gcc arm-linux-elf-gcc -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes"
$COMPILE -c proc/version.c -o proc/version.o $INCLUDES
$COMPILE -c lib/strutils.c -o lib/strutils.o $INCLUDES
$COMPILE -c lib/fileutils.c -o lib/fileutils.o $INCLUDES
$COMPILE -c proc/alloc.c -o proc/alloc.o
$COMPILE -c proc/sysinfo.c -o proc/sysinfo.o
$COMPILE -c free.c $INCLUDES
$COMPILE -o free free.o \
	proc/version.o \
	proc/sysinfo.o \
	proc/alloc.o \
	lib/fileutils.o \
	lib/strutils.o
exit

#gcc -c library/meminfo.c -o bin/meminfo.o $INCLUDES
#gcc -c local/fileutils.c -o bin/fileutils.o $INCLUDES
#gcc -c src/free.c -o bin/free.o $INCLUDES
#gcc bin/*.o -o bin/free
