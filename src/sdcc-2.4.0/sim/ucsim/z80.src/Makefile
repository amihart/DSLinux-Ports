#
# uCsim z80.src/Makefile
#
# (c) Drotos Daniel, Talker Bt. 1997
#

STARTYEAR	= 1997

SHELL		= /bin/sh
CXX		= ucfront-g++ arm-linux-elf-g++ 
CPP		= ucfront-gcc arm-linux-elf-gcc  -E
CXXCPP		= ucfront-g++ arm-linux-elf-g++  -E
RANLIB		= arm-linux-elf-ranlib
INSTALL		= /usr/bin/install -c

PRJDIR		= ..

DEFS            = $(subs -DHAVE_CONFIG_H,,-DHAVE_CONFIG_H)
CPPFLAGS        =  -I. -I$(PRJDIR) \
		  -I$(PRJDIR)/cmd.src -I$(PRJDIR)/sim.src -I$(PRJDIR)/gui.src
CFLAGS          = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -Wall
CXXFLAGS        = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -I /home/home/diskb/mnt/dslinux/lib/uClibc++/include -fno-builtin -nostdinc++ -DGCC_HASCLASSVISIBILITY -Wno-deprecated -Wall
M_OR_MM         = -MM
PICOPT		= 
SHAREDLIB	= no

EXEEXT          = 

LIBS		= -lnsl  -L$(PRJDIR) -lutil -lsim -lutil -lcmd -lguiucsim
DL		= 
dl_ok		= no

prefix          = /usr
exec_prefix     = ${prefix}
bindir          = ${exec_prefix}/bin
libdir          = ${exec_prefix}/lib
datadir         = ${prefix}/share
includedir      = ${prefix}/include
mandir          = ${prefix}/man
man1dir         = $(mandir)/man1
man2dir         = $(mandir)/man2
infodir         = ${prefix}/info
srcdir          = .

OBJECTS_SHARED	= glob.o \
		  inst.o \
		  inst_cb.o \
		  inst_dd.o \
		  inst_ed.o \
		  inst_fd.o \
		  inst_ddcb.o \
		  inst_fdcb.o \
		  simz80.o z80.o
OBJECTS_EXE	= sz80.o
OBJECTS		= $(OBJECTS_SHARED) $(OBJECTS_EXE)

Z80ASM		= 

enable_dlso	= no
dlso_ok		= no

#TEST_OBJ	= test_bit.hex test_dis.hex test_mov.hex test_jmp.hex \
#		  test_arith.hex

# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf otherlibs z80.src tests

tests: $(TEST_OBJ)


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs
	$(INSTALL) -s sz80$(EXEEXT) $(bindir)


# Deleting all the installed files
# --------------------------------
uninstall:
	rm -f $(bindir)/sz80$(EXEEXT)


# Performing self-test
# --------------------
check: test

test:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:
	test -d $(bindir) || $(INSTALL) -d $(bindir)


# Creating dependencies
# ---------------------
dep: Makefile.dep

Makefile.dep: *.cc *.h
	$(CXXCPP) $(CPPFLAGS) $(M_OR_MM) *.cc >Makefile.dep

include Makefile.dep
include clean.mk

# My rules
# --------
.SUFFIXES: .asm .hex

z80.src: sz80$(EXEEXT)  shared_lib

sz80$(EXEEXT): $(OBJECTS) $(PRJDIR)/*.a
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LIBS)

ifeq ($(dlso_ok),yes)
shared_lib: $(PRJDIR)/sz80.so
else
shared_lib:
	@$(PRJDIR)/mkecho $(PRJDIR) "No z80 shared lib made."
	@$(PRJDIR)/mkecho $(PRJDIR) "(SHAREDLIB="$(SHAREDLIB)",dl_ok="$(dl_ok)",enable_dlso="$(enable_dlso)")"
endif

$(PRJDIR)/sz80.so: $(OBJECTS_SHARED)
	$(CXX) -shared $(OBJECTS_SHARED) -o $(PRJDIR)/sz80.so

otherlibs:
	cd $(PRJDIR)/cmd.src && $(MAKE) all
	cd $(PRJDIR)/sim.src && $(MAKE) all

.cc.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

.asm.hex:
	$(Z80ASM) -l $< -o $@ -e $<.lst


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
	  $(MAKE) -f conf.mk srcdir="$(srcdir)" PRJDIR="$(PRJDIR)" freshconf;\
	fi

# End of z80.src/Makefile.in
