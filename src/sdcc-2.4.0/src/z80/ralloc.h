/*-------------------------------------------------------------------------

  SDCCralloc.h - header file register allocation

                Written By -  Sandeep Dutta . sandeep.dutta@usa.net (1998)

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   
   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!  
-------------------------------------------------------------------------*/
#include "SDCCicode.h"
#include "SDCCBBlock.h"
#ifndef SDCCRALLOC_H
#define SDCCRALLOC_H 1

#define DEBUG_FAKE_EXTRA_REGS 	0

enum
  {
    C_IDX = 0,
    B_IDX,
    E_IDX,
    D_IDX,
    L_IDX,
    H_IDX,
#if DEBUG_FAKE_EXTRA_REGS
    M_IDX,
    N_IDX,
    O_IDX,
    P_IDX,
    Q_IDX,
    R_IDX,
    S_IDX,
    T_IDX,
#endif
    CND_IDX
  };

enum
  {
    REG_PTR = 1,
    REG_GPR = 2,
    REG_CND = 4,
    REG_PAIR = 8
  };

/* definition for the registers */
typedef struct regs
  {
    short type;			/* can have value 
				   REG_GPR, REG_PTR or REG_CND */
    short rIdx;			/* index into register table */
    char *name;			/* name */
    unsigned isFree:1;		/* is currently unassigned  */
  }
regs;

extern regs *regsZ80;

void assignRegisters (eBBlock **, int);
regs *regWithIdx (int);

void z80_assignRegisters (eBBlock ** ebbs, int count);
bitVect *z80_rUmaskForOp (operand * op);

#endif
