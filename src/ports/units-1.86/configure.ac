dnl        Copyright (C) 2006 Free Software Foundation, Inc
dnl Process this file with autoconf to produce a configure script.

AC_INIT(GNU units,1.85b,adrian@cam.cornell.edu)
AC_PREREQ(2.59)
AC_ARG_PROGRAM

AC_SUBST(DEFIS)
AC_SUBST(STRFUNC)
AC_SUBST(UDAT)

dnl Hack to set correct CFLAGS for cl compiler while still
dnl allowing user to override the CFLAGS setting

saveCFLAGS=$CFLAGS

AC_PROG_CC(cl gcc cc egcs)

if test "$CC" = cl -a -z "$saveCFLAGS" ; then
    AC_MSG_NOTICE([setting special CFLAGS value for cl])
    CFLAGS="-G6 -O2 -Za -W3 -nologo"
fi

AC_C_CONST
AC_PROG_INSTALL

dnl Checks for libraries.

AC_CHECK_FUNC(sin,[],LIBS=-lm)
AC_CHECK_LIB(ncurses,tparm,TERMLIB=-lncurses,
  AC_CHECK_LIB(termcap,tgetent,TERMLIB=-ltermcap))
saved_LIBS="$LIBS"
LIBS="$LIBS $TERMLIB"
AC_CHECK_LIB(readline,readline,
  [AC_CHECK_HEADER(readline/readline.h, 
  LIBS="$saved_LIBS -lreadline $TERMLIB";DEFIS="$DEFIS -DREADLINE")],
  LIBS="$saved_LIBS")

dnl Checks for header files.
AC_CHECK_HEADER(string.h,[],[DEFIS="$DEFIS -DSTRINGS_H"])
AC_CHECK_HEADER(stdlib.h,[],[DEFIS="$DEFIS -DNO_STDLIB_H"])

dnl Checks for library functions.
AC_CHECK_FUNC(strchr,[],DEFIS="$DEFIS -DNO_STRCHR")
AC_CHECK_FUNC(strspn,[],DEFIS="$DEFIS -DNO_STRSPN";STRFUNC="strfunc.$OBJEXT")
AC_CHECK_FUNC(strtok,[],DEFIS="$DEFIS -DNO_STRTOK";STRFUNC="strfunc.$OBJEXT")

dnl Check for path search option
AC_ARG_ENABLE([path-search],
    AC_HELP_STRING([--enable-path-search],
       [search path for units database (default is NO)]),
    [UDAT=""],[UDAT="$datadir/"])

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
