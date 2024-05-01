#
#
#

VERSION         = 2.4.0
VERSIONHI       = 2
VERSIONLO       = 4
VERSIONP        = 0

SHELL		= /bin/sh
CPP		= ucfront-gcc arm-linux-elf-gcc  -E
INSTALL		= /usr/bin/install -c
CP              = cp

PRJDIR		= ..

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

include_dir_suffix = sdcc/include

sdcc_includedir    = $(datadir)/$(include_dir_suffix)

CPPFLAGS        =  -I$(PRJDIR)


# Compiling entire program or any subproject
# ------------------------------------------
all:

# Compiling and installing everything and running test
# ----------------------------------------------------
install: all installdirs
	$(CP) -r asm *.h $(sdcc_includedir)
	if [ "`grep pic16 ../../ports.build`" = pic16 ]; then \
		$(CP) pic16/*.h $(sdcc_includedir)/pic16 ; \
	fi
	rm -rf `find $(sdcc_includedir) -type d -name 'CVS'`


# Deleting all the installed files
# --------------------------------
uninstall:
	rm -rf $(sdcc_includedir)


# Performing self-test
# --------------------
check:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:
	[ -d $(sdcc_includedir) ] || mkdir -p $(sdcc_includedir)
	[ -d $(sdcc_includedir)/pic16 ] || mkdir -p $(sdcc_includedir)/pic16


# Creating dependencies
# ---------------------
dep: #Makefile.dep

#Makefile.dep:
#	$(CPP) $(CPPFLAGS) $(M_OR_MM) *.c >main.dep

#include Makefile.dep
include clean.mk

# My rules
# --------


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(PRJDIR)/devel ]; then\
	  $(MAKE) -f $(srcdir)/conf.mk srcdir="$(srcdir)" PRJDIR="$(PRJDIR)" \
	  freshconf;\
	fi

# End of main_in.mk/main.mk

