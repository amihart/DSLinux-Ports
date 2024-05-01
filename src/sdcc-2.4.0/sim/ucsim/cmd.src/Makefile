#
# ucsim cmd.src/Makefile
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
		  -I$(PRJDIR)/sim.src -I$(PRJDIR)/gui.src
CFLAGS          = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -Wall
CXXFLAGS        = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__ -I /home/home/diskb/mnt/dslinux/lib/uClibc++/include -fno-builtin -nostdinc++ -DGCC_HASCLASSVISIBILITY -Wno-deprecated -Wall
M_OR_MM         = -MM

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

OBJECTS		= cmdset.o command.o newcmd.o cmdutil.o syntax.o \
		  get.o set.o timer.o bp.o info.o show.o cmdgui.o cmdconf.o \
		  cmduc.o cmdstat.o


# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf cmdlib

cmd.src: all


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs


# Deleting all the installed files
# --------------------------------
uninstall:


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


# Creating dependencies
# ---------------------
dep: Makefile.dep

Makefile.dep: *.cc *.h
	$(CXXCPP) $(CPPFLAGS) $(M_OR_MM) *.cc >Makefile.dep

include Makefile.dep
include clean.mk

#parser.cc: parser.y

#plex.cc: plex.l

# My rules
# --------

cmdlib: $(PRJDIR)/libcmd.a

$(PRJDIR)/libcmd.a: $(OBJECTS)
	ar -rcu $*.a $(OBJECTS)
	$(RANLIB) $*.a

.cc.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

.y.cc:
	rm -f $*.cc $*.h
	$(YACC) -d $<
	mv y.tab.c $*.cc
	mv y.tab.h $*.h

.l.cc:
	rm -f $*.cc
	$(LEX) -t $< >$*.cc


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
	  $(MAKE) -f conf.mk srcdir="$(srcdir)" PRJDIR="$(PRJDIR)" freshconf;\
	fi

# End of cmd.src/Makefile.in
