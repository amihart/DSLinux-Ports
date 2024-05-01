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
SLIB		= $(PRJDIR)/support/Util

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
infodir         = ${prefix}/info

STD_INC		= @sdcc_include_dir@
CPPFLAGS	=  -I. -I$(PRJDIR) -I$(PRJDIR)/support -I$(SLIB)
CFLAGS		= -pipe -ggdb -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall  -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__
M_OR_MM		= -MM
LDFLAGS		= -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes

EXEEXT          = 

LIBS            = 
LIBDIRS         =

SLIBOBJS		= NewAlloc.o

OBJECTS		= sdcdb.o symtab.o simi.o $(PRJDIR)/src/SDCCset.o \
		  break.o cmd.o $(PRJDIR)/src/SDCChasht.o \
		  $(PRJDIR)/support/Util/SDCCerr.o
SOURCES		= $(patsubst %.o,%.c,$(OBJECTS))

TARGET		= $(PRJDIR)/bin/sdcdb$(EXEEXT)


# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf $(TARGET)

# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs
	$(INSTALL) $(TARGET) $(bindir)/sdcdb$(EXEEXT)
	$(STRIP) $(bindir)/sdcdb$(EXEEXT)
	cp $(PRJDIR)/debugger/mcs51/sdcdb.el $(bindir)/sdcdb.el
	cp $(PRJDIR)/debugger/mcs51/sdcdbsrc.el $(bindir)/sdcdbsrc.el


# Deleting all the installed files
# --------------------------------
uninstall:
	rm -f $(bindir)/sdcdb$(EXEEXT)
	rm -f $(bindir)/sdcdb.el
	rm -f $(bindir)/sdcdbsrc.el

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

Makefile.dep: $(SOURCES) *.h $(PRJDIR)/*.h
	$(CPP) $(CPPFLAGS) $(M_OR_MM) $(SOURCES) >Makefile.dep

include Makefile.dep
include clean.mk

# My rules
# --------
$(TARGET): $(OBJECTS) $(SLIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(SLIBOBJS) $(LIBDIRS) $(LIBS)

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(SLIBOBJS):%.o:$(SLIB)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
          $(MAKE) -f conf.mk srcdir="$(srcdir)" PRJDIR="$(PRJDIR)" freshconf;\
        fi

# End of cpp/Makefile
