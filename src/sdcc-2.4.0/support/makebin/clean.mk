# Deleting all files created by building the program
# --------------------------------------------------
PRJDIR = ../..

clean:
	rm -rf obj
	rm -f *core *[%~] *.[oa] $(PRJDIR)/bin/makebin$(EXEEXT)
	rm -f *.[a-z]*~

# Deleting all files created by configuring or building the program
# -----------------------------------------------------------------
distclean: clean
	rm -f *.dep


# Like clean but some files may still exist
# -----------------------------------------
mostlyclean: clean


# Deleting everything that can reconstructed by this Makefile. It deletes
# everything deleted by distclean plus files created by bison, etc.
# -----------------------------------------------------------------------
realclean: distclean
