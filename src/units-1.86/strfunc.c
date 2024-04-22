/*
 *  Copyright (C) 1996 Free Software Foundation, Inc
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *     
 */

#define NULL 0

#define size_t int

#ifdef NO_STRTOK

/* Find the first ocurrence in S of any character in ACCEPT.  */
char *
strpbrk(char *s, char *accept)
{
  while (*s != '\0')
    if (strchr(accept, *s) == NULL)
      ++s;
    else
      return (char *) s;

  return NULL;
}


static char *olds = NULL;

char *
strtok(char *s, char *delim)
{
  char *token;

  if (s == NULL)
    {
      if (olds == NULL)
	{
	  /*errno = EINVAL;  Wonder where errno is defined....*/
	  return NULL;
	}
      else
	s = olds;
    }

  /* Scan leading delimiters.  */
  s += strspn(s, delim);
  if (*s == '\0')
    {
      olds = NULL;
      return NULL;
    }

  /* Find the end of the token.  */
  token = s;
  s = strpbrk(token, delim);
  if (s == NULL)
    /* This token finishes the string.  */
    olds = NULL;
  else
    {
      /* Terminate the token and make OLDS point past it.  */
      *s = '\0';
      olds = s + 1;
    }
  return token;
}


#endif /* NO_STRTOK */

#ifdef NO_STRSPN

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
strspn(char *s, char *accept)
{
  register char *p;
  register char *a;
  register size_t count = 0;

  for (p = s; *p != '\0'; ++p)
    {
      for (a = accept; *a != '\0'; ++a)
	if (*p == *a)
	  break;
      if (*a == '\0')
	return count;
      else
	++count;
    }

  return count;
}

#endif NO_STRSPN
