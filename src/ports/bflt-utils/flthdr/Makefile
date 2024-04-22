#CC=gcc
CFLAGS= -Wall -g -O2 -I/usr/include/libiberty -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__
LDFLAGS= -lz -lc -liberty -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes
#LDFLAGS= -lz -lc -lbfd -liberty -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes
TARGET=flthdr

$(TARGET): compress.o stubs.o flthdr.o
	$(CC) $(CFLAGS) -o $(TARGET) *.o $(LDFLAGS)

compress.o:
	$(CC) $(CFLAGS) compress.c -c

stubs.o:
	$(CC) $(CFLAGS) stubs.c -c

flthdr.o:
	$(CC) $(CFLAGS) flthdr.c -c

clean:
	rm -f *.o $(TARGET)
