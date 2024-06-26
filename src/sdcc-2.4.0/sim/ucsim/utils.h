/*
 * Simulator of microcontrollers (utils.h)
 *
 * Copyright (C) 1999,99 Drotos Daniel, Talker Bt.
 * 
 * To contact author send email to drdani@mazsola.iit.uni-miskolc.hu
 *
 */

/* This file is part of microcontroller simulator: ucsim.

UCSIM is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

UCSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with UCSIM; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA. */
/*@1@*/

#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>


extern int get_sub_opt(char **option,
		       const char * const *tokens,
		       char **valuep);
extern char *get_id_string(struct id_element *ids, int id);
extern char *get_id_string(struct id_element *ids, int id, char *def);
extern int get_string_id(struct id_element *ids, char *str);
extern int get_string_id(struct id_element *ids, char *str, int def);
extern char *format_string(char *format, ...);
extern void print_char_octal(char c, FILE *f);
extern char *object_name(class cl_base *o);


#endif

/* End of utils.h */
