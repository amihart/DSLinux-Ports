all:
	#readline
	rm -rf $(ROOTDIR)/include/readline/
	make clean -C readline/
	make -C readline/
	cp readline/libhistory.a $(ROOTDIR)/lib/
	cp readline/libreadline.a $(ROOTDIR)/lib/
	mkdir -p $(ROOTDIR)/include/readline/
	cp -r readline/*.h $(ROOTDIR)/include/readline/

	#termcap
	make clean -C termcap/
	make -C termcap/
	cp termcap/libtermcap.a $(ROOTDIR)/lib/
