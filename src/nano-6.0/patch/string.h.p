/* Copyright (C) 1991-1993, 1995-2002, 2003 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 *	ISO C99 Standard: 7.21 String handling	<string.h>
 */

#ifndef	_STRING_H
#define	_STRING_H	1

#include <features.h>

__BEGIN_DECLS

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#include <stddef.h>


__BEGIN_NAMESPACE_STD
/* Copy N bytes of SRC to DEST.  */
extern void *memcpy (void *__restrict __dest,
		     __const void *__restrict __src, size_t __n) __THROW;
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern void *memmove (void *__dest, __const void *__src, size_t __n)
     __THROW;
__END_NAMESPACE_STD

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#if defined __USE_SVID || defined __USE_BSD || defined __USE_XOPEN
extern void *memccpy (void *__restrict __dest, __const void *__restrict __src,
		      int __c, size_t __n)
     __THROW;
#endif /* SVID.  */


__BEGIN_NAMESPACE_STD
/* Set N bytes of S to C.  */
extern void *memset (void *__s, int __c, size_t __n) __THROW;

/* Compare N bytes of S1 and S2.  */
extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
     __THROW __attribute_pure__;

/* Search N bytes of S for C.  */
extern void *memchr (__const void *__s, int __c, size_t __n)
      __THROW __attribute_pure__;
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
extern void *rawmemchr (__const void *__s, int __c) __THROW __attribute_pure__;

/* Search N bytes of S for the final occurrence of C.  */
extern void *memrchr (__const void *__s, int __c, size_t __n)
      __THROW __attribute_pure__;
#endif


__BEGIN_NAMESPACE_STD
/* Copy SRC to DEST.  */
extern char *strcpy (char *__restrict __dest, __const char *__restrict __src)
     __THROW;
/* Copy no more than N characters of SRC to DEST.  */
extern char *strncpy (char *__restrict __dest,
		      __const char *__restrict __src, size_t __n) __THROW;

/* Append SRC onto DEST.  */
extern char *strcat (char *__restrict __dest, __const char *__restrict __src)
     __THROW;
/* Append no more than N characters from SRC onto DEST.  */
extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
		      size_t __n) __THROW;

/* Compare S1 and S2.  */
extern int strcmp (__const char *__s1, __const char *__s2)
     __THROW __attribute_pure__;
/* Compare N characters of S1 and S2.  */
extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
     __THROW __attribute_pure__;

/* Compare the collated forms of S1 and S2.  */
extern int strcoll (__const char *__s1, __const char *__s2)
     __THROW __attribute_pure__;
/* Put a transformation of SRC into no more than N bytes of DEST.  */
extern size_t strxfrm (char *__restrict __dest,
		       __const char *__restrict __src, size_t __n) __THROW;
__END_NAMESPACE_STD

#ifdef __UCLIBC_HAS_XLOCALE__
#ifdef __USE_GNU
/* The following functions are equivalent to the both above but they
   take the locale they use for the collation as an extra argument.
   This is not standardsized but something like will come.  */
# include <xlocale.h>

/* Compare the collated forms of S1 and S2 using rules from L.  */
extern int strcoll_l (__const char *__s1, __const char *__s2, __locale_t __l)
     __THROW __attribute_pure__;
extern int __strcoll_l (__const char *__s1, __const char *__s2, __locale_t __l)
     __THROW __attribute_pure__;

/* Put a transformation of SRC into no more than N bytes of DEST.  */
extern size_t strxfrm_l (char *__dest, __const char *__src, size_t __n,
			 __locale_t __l) __THROW;
extern size_t __strxfrm_l (char *__dest, __const char *__src, size_t __n,
			 __locale_t __l) __THROW;

#endif
#endif

#if defined __USE_SVID || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
/* Duplicate S, returning an identical malloc'd string.  */
extern char *strdup (__const char *__s) __THROW __attribute_malloc__;
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#if defined __USE_GNU
extern char *strndup (__const char *__string, size_t __n)
     __THROW __attribute_malloc__;
#endif

#if defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      __const char *__old = (s);					      \
      size_t __len = strlen (__old) + 1;				      \
      char *__new = (char *) __builtin_alloca (__len);			      \
      (char *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      __const char *__old = (s);					      \
      size_t __len = strnlen (__old, (n));				      \
      char *__new = (char *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (char *) memcpy (__new, __old, __len);				      \
    }))
#endif

__BEGIN_NAMESPACE_STD
/* Find the first occurrence of C in S.  */
extern char *strchr (__const char *__s, int __c) __THROW __attribute_pure__;
/* Find the last occurrence of C in S.  */
extern char *strrchr (__const char *__s, int __c) __THROW __attribute_pure__;
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
extern char *strchrnul (__const char *__s, int __c) __THROW __attribute_pure__;
#endif

__BEGIN_NAMESPACE_STD
/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
extern size_t strcspn (__const char *__s, __const char *__reject)
     __THROW __attribute_pure__;
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
extern size_t strspn (__const char *__s, __const char *__accept)
     __THROW __attribute_pure__;
/* Find the first occurrence in S of any character in ACCEPT.  */
extern char *strpbrk (__const char *__s, __const char *__accept)
     __THROW __attribute_pure__;
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
extern char *strstr (__const char *__haystack, __const char *__needle)
     __THROW __attribute_pure__;


/* Divide S into tokens separated by characters in DELIM.  */
extern char *strtok (char *__restrict __s, __const char *__restrict __delim)
     __THROW;
__END_NAMESPACE_STD

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
extern char *__strtok_r (char *__restrict __s,
			 __const char *__restrict __delim,
			 char **__restrict __save_ptr) __THROW;
#if defined __USE_POSIX || defined __USE_MISC
extern char *strtok_r (char *__restrict __s, __const char *__restrict __delim,
		       char **__restrict __save_ptr) __THROW;
#endif

#ifdef __USE_GNU
/* Similar to `strstr' but this function ignores the case of both strings.  */
extern char *strcasestr (__const char *__haystack, __const char *__needle)
     __THROW __attribute_pure__;
#endif

#ifdef __USE_GNU
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
extern void *memmem (__const void *__haystack, size_t __haystacklen,
		     __const void *__needle, size_t __needlelen)
     __THROW __attribute_pure__;

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
extern void *__mempcpy (void *__restrict __dest,
			__const void *__restrict __src, size_t __n) __THROW;
extern void *mempcpy (void *__restrict __dest,
		      __const void *__restrict __src, size_t __n) __THROW;
#endif


__BEGIN_NAMESPACE_STD
/* Return the length of S.  */
extern size_t strlen (__const char *__s) __THROW __attribute_pure__;
__END_NAMESPACE_STD

#ifdef	__USE_GNU
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
extern size_t strnlen (__const char *__string, size_t __maxlen)
     __THROW __attribute_pure__;
#endif


__BEGIN_NAMESPACE_STD
/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
extern char *strerror (int __errnum) __THROW;
__END_NAMESPACE_STD
#if defined __USE_XOPEN2K || defined __USE_MISC
/* Reentrant version of `strerror'.  If a temporary buffer is required, at
   most BUFLEN bytes of BUF will be used.  */
/* extern char *strerror_r (int __errnum, char *__buf, size_t __buflen) __THROW; */

/* uClibc Note: glibc's strerror_r is different from that specified in SUSv3.
 * So we try to compensate based on feature macros. */
extern char *_glibc_strerror_r (int __errnum, char *__buf, size_t __buflen) __THROW;
extern int _susv3_strerror_r (int __errnum, char *__buf, size_t buflen) __THROW;

#if defined(__USE_XOPEN2K) && !defined(__USE_GNU)
# ifdef __REDIRECT
extern int __REDIRECT (strerror_r,
                       (int __errnum, char *__buf, size_t buflen) __THROW,
                       _susv3_strerror_r);
# else
#  define strerror_r _susv3_strerror_r
# endif
#else  /* defined(__USE_XOPEN2K) && !defined(__USE_GNU) */
# ifdef __REDIRECT
//extern char *__REDIRECT (strerror_r,
//                         (int __errnum, char *__buf, size_t buflen) __THROW,
//                         _glibc_strerror_r);
# else
#  define strerror_r _glibc_strerror_r
# endif
#endif /* defined(__USE_XOPEN2K) && !defined(__USE_GNU) */
#endif

/* We define this function always since `bzero' is sometimes needed when
   the namespace rules does not allow this.  */
extern void __bzero (void *__s, size_t __n) __THROW;

#ifdef __USE_BSD
/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
extern void bcopy (__const void *__src, void *__dest, size_t __n) __THROW;

/* Set N bytes of S to 0.  */
extern void bzero (void *__s, size_t __n) __THROW;

/* Compare N bytes of S1 and S2 (same as memcmp).  */
extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
     __THROW __attribute_pure__;

/* Find the first occurrence of C in S (same as strchr).  */
extern char *index (__const char *__s, int __c) __THROW __attribute_pure__;

/* Find the last occurrence of C in S (same as strrchr).  */
extern char *rindex (__const char *__s, int __c) __THROW __attribute_pure__;

/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
extern int ffs (int __i) __THROW __attribute__ ((__const__));

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_GNU
extern int ffsl (long int __l) __THROW __attribute__ ((__const__));
#  ifdef __GNUC__
__extension__ extern int ffsll (long long int __ll)
     __THROW __attribute__ ((__const__));
#  endif
# endif

/* Compare S1 and S2, ignoring case.  */
extern int strcasecmp (__const char *__s1, __const char *__s2)
     __THROW __attribute_pure__;

/* Compare no more than N chars of S1 and S2, ignoring case.  */
extern int strncasecmp (__const char *__s1, __const char *__s2, size_t __n)
     __THROW __attribute_pure__;
#endif /* Use BSD.  */

#ifdef __UCLIBC_HAS_XLOCALE__
#ifdef	__USE_GNU
/* Again versions of a few functions which use the given locale instead
   of the global one.  */
extern int strcasecmp_l (__const char *__s1, __const char *__s2,
			 __locale_t __loc) __THROW __attribute_pure__;
extern int __strcasecmp_l (__const char *__s1, __const char *__s2,
			 __locale_t __loc) __THROW __attribute_pure__;

extern int strncasecmp_l (__const char *__s1, __const char *__s2,
			  size_t __n, __locale_t __loc)
     __THROW __attribute_pure__;
extern int __strncasecmp_l (__const char *__s1, __const char *__s2,
			  size_t __n, __locale_t __loc)
     __THROW __attribute_pure__;
#endif
#endif

#ifdef	__USE_BSD
/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
extern char *strsep (char **__restrict __stringp,
		     __const char *__restrict __delim) __THROW;
#endif

#ifdef	__USE_GNU

/* Return a string describing the meaning of the signal number in SIG.  */
extern char *strsignal (int __sig) __THROW;

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
extern char *__stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __THROW;
extern char *stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __THROW;

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
extern char *__stpncpy (char *__restrict __dest,
			__const char *__restrict __src, size_t __n) __THROW;
extern char *stpncpy (char *__restrict __dest,
		      __const char *__restrict __src, size_t __n) __THROW;

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
extern char *basename (__const char *__filename) __THROW;
# endif
#endif


#ifdef	__USE_BSD
/* Two OpenBSD extension functions. */
extern size_t strlcat(char *__restrict dst, const char *__restrict src,
                      size_t n) __THROW;
extern size_t strlcpy(char *__restrict dst, const char *__restrict src,
                      size_t n) __THROW;
#endif

__END_DECLS

#endif /* string.h  */
