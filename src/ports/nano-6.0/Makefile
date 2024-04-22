all:
	cp patch/string.h.p $(ROOTDIR)/uClibc/include/string.h
	cp patch/sysmacros.h.p $(ROOTDIR)/uClibc/include/sys/sysmacros.h
	cp patch/text.c.p code/src/text.c
	make -C code
	cp patch/string.h $(ROOTDIR)/uClibc/include/string.h
	cp patch/sysmacros.h $(ROOTDIR)/uClibc/include/sys/sysmacros.h
	cp patch/text.c code/src/text.c
