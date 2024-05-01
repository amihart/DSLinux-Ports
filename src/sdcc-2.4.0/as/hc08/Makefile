#
#
#

VERSION         = 2.4.0
VERSIONHI       = 2
VERSIONLO       = 4
VERSIONP        = 0

SHELL		= /bin/sh
CC		= ucfront-gcc arm-linux-elf-gcc 
CPP		= ucfront-gcc arm-linux-elf-gcc  -E
INSTALL		= /usr/bin/install -c
STRIP           = arm-linux-elf-strip

PRJDIR		= ../..

srcdir		= .
prefix		= /usr
exec_prefix     = ${prefix}
bindir          = ${exec_prefix}/bin
libdir          = ${exec_prefix}/lib
datadir         = ${prefix}/share
includedir      = ${prefix}/include
mandir          = ${prefix}/man
man1dir         = $(mandir)/man1
man2dir         = $(mandir)/man2
infodir         = @info@

EXEEXT          = 

CPPFLAGS	=  -I. -I$(PRJDIR)
CFLAGS		= -pipe -ggdb -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall  -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -Wall
M_OR_MM		= -MM
LDFLAGS		= -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes

ASOBJECTS	= asmain.o aslex.o assym.o assubr.o asnoice.o \
		  asexpr.o asdata.o aslist.o asout.o asstore.o \
		  m08ext.o m08pst.o m08mch.o m08adr.o strcmpi.o
ASSOURCES	= $(patsubst %.o,%.c,$(ASOBJECTS))

LKOBJECTS	= lkmain.o lkhead.o lkarea.o lkdata.o \
		  lkeval.o lklex.o lksym.o lkrloc.o \
		  lklibr.o lklist.o lkihx.o lks19.o \
		  lkstore.o lknoice.o lkmem.o lkaomf51.o strcmpi.o
LKSOURCES	= $(patsubst %.o,%.c,$(LKOBJECTS))

ASHC08		= $(PRJDIR)/bin/as-hc08$(EXEEXT)
ASLINK		= $(PRJDIR)/bin/link-hc08$(EXEEXT)

transform       = s,x,x,

# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf $(ASHC08) $(ASLINK)

$(ASHC08): $(ASOBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(ASOBJECTS) 

$(ASLINK): $(LKOBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(LKOBJECTS)

# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs
	$(INSTALL) $(ASHC08) `echo $(bindir)/as-hc08$(EXEEXT)|sed '$(transform)'`
	$(STRIP) `echo $(bindir)/as-hc08$(EXEEXT)|sed '$(transform)'`
	$(INSTALL) $(ASLINK) `echo $(bindir)/link-hc08$(EXEEXT)|sed '$(transform)'`
	$(STRIP) `echo $(bindir)/link-hc08$(EXEEXT)|sed '$(transform)'`

# Deleting all the installed files
# --------------------------------
uninstall:
	rm -f $(bindir)/as-hc08$(EXEEXT) $(bindir)/link-hc08$(EXEEXT)


# Performing self-test
# --------------------
check:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:
	$(INSTALL) -d $(bindir)


# Creating dependencies
# ---------------------
dep: Makefile.dep

Makefile.dep: $(ASSOURCES) $(LKSOURCES) *.h $(PRJDIR)/*.h
	$(CPP) $(CPPFLAGS) $(M_OR_MM) $(ASSOURCES) $(LKSOURCES) >Makefile.dep

include Makefile.dep
include clean.mk

# My rules
# --------
.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
          $(MAKE) -f conf.mk srcdir="$(srcdir)" PRJDIR="$(PRJDIR)" freshconf;\
        fi

# End of Makefile
