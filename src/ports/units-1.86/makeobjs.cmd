/*
 *  Make a program object for the OS/2 version of units
 *  Peter Weilbacher (os2@Weilbacher.org), 25Jan2003
 *
 *  Copyright (C) 1996, 1997, 1999 Free Software Foundation, Inc
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
 
call RxFuncAdd SysLoadFuncs, REXXUtil, SysLoadFuncs
call SysLoadFuncs

workdir = Directory()
classname='WPProgram'

title = 'units'
location = '<WP_DESKTOP>'
setup = 'OBJECTID=<UNITS>;'||,
	'EXENAME=CMD.EXE;'||,
	'PARAMETERS=/c mode co50,5 & units.exe [from-unit] [to-unit] & pause;'||,
	'STARTUPDIR='workdir
if SysCreateObject(classname, title, location, setup, 'U') then 
   say 'Object created.'
else
   say 'Could NOT create the object!!'

title = 'units Shell'
location = '<WP_DESKTOP>'
setup = 'OBJECTID=<UNITSSHELL>;'||,
	'EXENAME=CMD.EXE;'||,
	'PARAMETERS=/c mode co80,25 & units.exe;'||,
	'STARTUPDIR='workdir
if SysCreateObject(classname, title, location, setup, 'U') then 
   say 'Object created.'
else
   say 'Could NOT create the object!!'
