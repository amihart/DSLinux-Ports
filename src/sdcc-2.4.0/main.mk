#
#
#

# Version
VERSION         = 2.4.0
VERSIONHI       = 2
VERSIONLO       = 4
VERSIONP        = 0

# Programs
SHELL		= /bin/sh
CC		= ucfront-gcc arm-linux-elf-gcc 
CPP		= ucfront-gcc arm-linux-elf-gcc  -E
RANLIB		= arm-linux-elf-ranlib
INSTALL		= /usr/bin/install -c
AUTOCONF        = autoconf

# Directories
PRJDIR		= .

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

# Flags
DEFS            = $(subs -DHAVE_CONFIG_H,,-DHAVE_CONFIG_H)
CPPFLAGS        =  -I$(PRJDIR)
CFLAGS          = -pipe -ggdb -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall  -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__
M_OR_MM         = -MM


# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs


# Deleting all the installed files
# --------------------------------
uninstall:


# Performing self-test
# --------------------
check:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:


# Creating dependencies
# ---------------------
dep: #main.dep

#main.dep: *.c *.h
#	$(CPP) $(CPPFLAGS) $(M_OR_MM) *.c >main.dep

#include main.dep
include clean.mk

# My rules
# --------
.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.y.c:
	rm -f $*.cc $*.h
	$(YACC) -d $<
	mv y.tab.c $*.cc
	mv y.tab.h $*.h

.l.c:
	rm -f $*.cc
	$(LEX) -t $< >$*.cc


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
	  $(MAKE) -f $(srcdir)/conf.mk srcdir="$(srcdir)" freshconf;\
	fi

# End of main_in.mk/main.mk

