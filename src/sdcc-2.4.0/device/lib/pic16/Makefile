#
# Makefile - toplevel makefile that builds everything
#
# This file is part of the GNU PIC Library.
#
# January, 2004
# The GNU PIC Library is maintained by,
# 	Vangelis Rokas <vrokas@otenet.gr>
#
# $Id: Makefile,v 1.1 2004/01/12 22:10:38 vrokas Exp $
#
#


include ./Makefile.common


# The devices to build libraries for
DEVICES	=	18f242	\
		18f248	\
		18f252	\
		18f258	\
		18f442	\
		18f448	\
		18f452	\
		18f458


all: compile-library

compile-library: compile-sources build-library

build-library:
	@for temp in $(DEVICES) ; do		\
		$(AR) -c pic$$temp.lib pic$$temp/pic$$temp.o ; \
	done ;

compile-sources:
	@for temp in $(DEVICES); do				\
		$(MAKE) -C pic$$temp make-target;	\
	done

clean: all-clean
	$(RM) -f pic*.lib

clean-intermediate:
	@for temp in $(DEVICES) ; do \
		$(MAKE) -C pic$$temp clean-intermediate; \
	done

real-clean:
	@for temp in $(DEVICES) ; do \
		$(MAKE) -C pic$$temp real-clean; \
	done ;
	rm -f config.* ;

dep: all-dep

all-clean:
	for temp in $(DEVICES) ; do		\
		$(MAKE) -C pic$$temp clean;	\
	done

all-dep:
	for temp in $(DEVICES) ; do		\
		$(MAKE) -C pic$$temp dep;	\
	done
