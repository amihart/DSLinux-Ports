# Makefile for kano-networks talker

SHELL		= /bin/sh
CXX		= ucfront-g++ arm-linux-elf-g++ 
CXXCPP		= ucfront-g++ arm-linux-elf-g++  -E
INSTALL		= /usr/bin/install -c
CP		= /bin/cp

PRJDIR		= ../..

DEFS            = $(subs -DHAVE_CONFIG_H,,-DHAVE_CONFIG_H)
CPPFLAGS        =  -I. -I$(PRJDIR)
#		  -I$(PRJDIR)/cmd.src -I$(PRJDIR)/sim.src
CFLAGS          = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -Wall
CXXFLAGS        = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -I /home/home/diskb/mnt/dslinux/lib/uClibc++/include -fno-builtin -nostdinc++ -DGCC_HASCLASSVISIBILITY -Wno-deprecated -Wall
M_OR_MM         = -MM

LIBS		=  -lnsl 

EXEEXT          = 

curses_ok	= 

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

OBJECTS		= main.o fileio.o frontend.o posix_signal.o


# Compiling entire program or any subproject
# ------------------------------------------
all: serio.src

ifeq ($(curses_ok),yes)
serio.src: checkconf serialview$(EXEEXT)
else
serio.src: checkconf
endif


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs
	$(INSTALL) -s serialview$(EXEEXT) $(bindir)


# Deleting all the installed files
# --------------------------------
uninstall:
	rm -f $(bindir)/serialview$(EXEEXT)


# Performing self-test
# --------------------
check:

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

Makefile.dep: *.cc *.h *.hh
	$(CXXCPP) $(CPPFLAGS) $(M_OR_MM) *.cc >Makefile.dep

include Makefile.dep
include clean.mk


# My rules
# --------
serialview$(EXEEXT): $(OBJECTS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS) $(LIBS)

.cc.o:
	$(CXX) $(CXXFLAGS)  $(CPPFLAGS) -c $< -o $@

# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
	  $(MAKE) -f conf.mk srcdir="$(srcdir)" PRJDIR="$(PRJDIR)" freshconf;\
	fi

# End of gui.src/serio.src/Makefile.in
