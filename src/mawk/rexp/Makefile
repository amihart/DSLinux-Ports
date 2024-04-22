
####################################
# This is a makefile for mawk,
# an implementation of AWK (1988).
####################################
#
#

#CC = cc
#CFLAGS = -O -lm -DMAWK -I..
CC = ucfront-gcc arm-linux-elf-gcc -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes
CFLAGS = -lm -DMAWK -I.. -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__

O=rexp.o rexp0.o rexp1.o rexp2.o rexp3.o 
DB=rexpdb.o

all : $(O)
	@cat </dev/null > .done

debug : $(O) $(DB)
	@cat </dev/null > .done

$(O) : rexp.h

clean :
	rm -f *.o .done
