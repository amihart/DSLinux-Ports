# Makefile for units, a program for units conversion
#
# Copyright (C) 1996, 1997, 1999, 2005, 2006 Free Software Foundation, Inc
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#    
#
# This program was written by Adrian Mariano (adrian@cam.cornell.edu)
#

SHELL = /bin/sh
exec_prefix = ${prefix}
prefix = /usr
srcdir = .

CC = ucfront-gcc arm-linux-elf-gcc 

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
MAKEINFO = makeinfo
TEXI2DVI = texi2dvi
LDFLAGS = -Wl,-elf2flt -D__PIC__ -fpic -msingle-pic-base -mswp-byte-writes
LIBS= -lm


bindir = ${exec_prefix}/bin
infodir = ${prefix}/info
mandir = ${prefix}/man

transform=s,x,x,

datadir = ${prefix}/share
DEFS = -DUNITSFILE=\"${prefix}/share/units.dat\"  -DPACKAGE_NAME=\"GNU\ units\" -DPACKAGE_TARNAME=\"units\" -DPACKAGE_VERSION=\"1.85b\" -DPACKAGE_STRING=\"GNU\ units\ 1.85b\" -DPACKAGE_BUGREPORT=\"adrian@cam.cornell.edu\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 
CFLAGS = -O2 -g -fomit-frame-pointer -fno-common -fno-builtin -Wall  -mswp-byte-writes -DCONFIG_NDS_ROM8BIT -mcpu=arm946e-s -mfpu=fpe3 -DEMBED -D__PIC__ -fpic -msingle-pic-base -Dlinux -D__linux__ -Dunix -D__uClinux__
OBJECTS = units.o parse.tab.o getopt.o getopt1.o 

.SUFFIXES:
.SUFFIXES: .c .o
 
.c.o:
	$(CC) $(DEFS) $(CFLAGS) -I$(srcdir) -c $<
 
# %.o: %.c
#     $(CC) $(DEFS) $(CFLAGS) -I$(srcdir) -c %.c


DISTFILES = README ChangeLog units.info units.doc getopt1.c units.dvi \
   Makefile.in units.c getopt.c getopt.h units.dat units.man units.texinfo \
   configure.ac configure strfunc.c COPYING Makefile.dos install-sh \
   mkinstalldirs NEWS texi2man INSTALL \
   parse.tab.c parse.y units.h Makefile.OS2 makeobjs.cmd README.OS2


all: units units.1 units.info

units.o: units.c

parse.tab.c: parse.y
	bison parse.y

parse.tab.o: parse.tab.c

units: $(OBJECTS)
	$(CC) $(LDFLAGS) -o units $(OBJECTS) $(LIBS)

install: units units.dat install-doc
	$(srcdir)/mkinstalldirs $(DESTDIR)$(bindir) $(DESTDIR)$(datadir)
	$(INSTALL_PROGRAM) units $(DESTDIR)$(bindir)/`echo units|sed '$(transform)'`
	$(INSTALL_DATA) $(srcdir)/units.dat $(DESTDIR)$(datadir)/units.dat

install-strip: units units.dat install-doc
	$(INSTALL_PROGRAM) -s units $(DESTDIR)$(bindir)/`echo units|sed '$(transform)'`
	$(INSTALL_DATA) $(srcdir)/units.dat $(DESTDIR)$(datadir)/units.dat

install-doc: install-man install-info

install-man: units.1
	$(srcdir)/mkinstalldirs $(DESTDIR)$(mandir)/man1
	$(INSTALL_DATA) units.1 $(DESTDIR)$(mandir)/man1/`echo units|sed '$(transform)'`.1

units.man: units.texinfo texi2man
	./texi2man units.texinfo > units.man

units.1: units.man
	sed s!@DATAFILE@!${prefix}/share/units.dat! $(srcdir)/units.man > units.1

install-info: $(DESTDIR)$(infodir)/units.info

$(DESTDIR)$(infodir)/units.info: units.info
	$(POST_INSTALL)
	$(srcdir)/mkinstalldirs $(DESTDIR)$(infodir)
# There may be a newer info file in . than in srcdir.
	-if test -f units.info; then d=.; \
	    else d=$(srcdir); fi; \
	$(INSTALL_DATA) $$d/units.info $@; \
# Run install-info only if it exists.
# Use `if' instead of just prepending `-' to the
# line so we notice real errors from install-info.
# We use `$(SHELL) -c' because some shells do not
# fail gracefully when there is an unknown command.
	if test -f $(DESTDIR)$(infodir)/dir; then \
	  if $(SHELL) -c 'install-info --version' \
	       >/dev/null 2>&1; then \
	    install-info --dir-file=$(DESTDIR)$(infodir)/dir \
	               $(DESTDIR)$(infodir)/units.info; \
	  else true; fi \
	else true; fi

Makefile: Makefile.in config.status
	./config.status

uninstall: 
	-rm -f $(DESTDIR)$(bindir)/`echo units|sed '$(transform)'` \
	       $(DESTDIR)$(mandir)/man1/`echo units|sed '$(transform)'`.1 \
	       $(DESTDIR)$(infodir)/units.info $(DESTDIR)$(datadir)/units.dat
	@if test -f $(DESTDIR)$(infodir)/dir; then \
	  echo You may need to remove units.info from $(DESTDIR)$(infodir)/dir; \
	else true; fi

clean mostlyclean: 
	-rm -f *.o units units.fn units.ky units.pg units.tp \
	     units.vr units.log units.dvi units.1 units.cp distname .chk \
	     units.toc units.aux units.cps units.op 

distclean: clean
	-rm -f config.* Makefile TAGS

maintainer-clean: clean
	-rm -f units.doc units.info units.dvi units-*.tar.gz parse.tab.c

sig:
	echo units-`sed -n -e '/#.*VERSION/s/.*"\(.*\)"/\1/gp' \
	    $(srcdir)/units.c`.tar.gz > distname
	echo 'version: 1.1' > `cat distname`.directive
	echo 'directory: units' >> `cat distname`.directive
	echo 'filename: '`cat distname` >> `cat distname`.directive
	gpg --clearsign `cat distname`.directive
	gpg -b `cat distname`
	-rm -f `cat distname`.directive distname



dist: $(DISTFILES)
	echo units-`sed -n -e '/#.*VERSION/s/.*"\(.*\)"/\1/gp' \
	    $(srcdir)/units.c` > distname
	-rm -r `cat distname` `cat distname`.tar `cat distname`.tar.gz
	mkdir `cat distname`
	dst=`cat distname`; for f in $(DISTFILES); do \
	   ln $(srcdir)/$$f $$dst/$$f || { echo copying $$f; \
	          cp -p $(srcdir)/$$f $$dst/$$f ; } \
	done
	chmod 777 `cat distname`
	tar cf `cat distname`.tar `cat distname`
	gzip `cat distname`.tar
	-rm -rf `cat distname` distname

dvi: units.dvi

units.dvi: units.texinfo
	$(TEXI2DVI) $(srcdir)/units.texinfo

info: units.info

units.info: units.texinfo
	$(MAKEINFO) $(srcdir)/units.texinfo

units.doc: units.1
	nroff -man $(srcdir)/units.1 | col -b > units.doc

doc: units.dvi units.info units.doc

check: all
	@echo Checking units
	@./units -f $(srcdir)/units.dat \
	      '(((square(kiloinch)+2.84m2) /0.5) meters^2)^(1|4)' m \
	    | sed -n -e 's/	\* //p' > .chk
	@if [ "`cat .chk`" = 6 ]; then echo Units seems to work; \
	   else echo Something is wrong: units failed the check: ;cat .chk; fi
	@rm -f .chk

configure: configure.ac
	autoconf

TAGS: units.c
	etags $(srcdir)/units.c $(srcdir)/parse.y


smalldist: units.c units.h parse.y parse.tab.c
	echo units-`sed -n -e '/#.*VERSION/s/.*"\(.*\)"/\1/gp' \
	    $(srcdir)/units.c` > distname
	-rm -r `cat distname` `cat distname`.tar `cat distname`.tar.gz
	tar cf `cat distname`.tar units.c units.h  parse.y  parse.tab.c\
	   getopt1.c getopt.c getopt.h
	gzip `cat distname`.tar

#
# Not very portable code to compile into library (written for Linux)
#

libunits.a: $(OBJECTS)
	ar -r libunits.a $^

libunits.so: $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -o $@ $^

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:

