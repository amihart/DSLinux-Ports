#include <zeditty.h>
#ifdef z_VERBOSE
#include <stdio.h>
#endif

static void z_DefaultPortOutCallback(z_Machine* mm, unsigned char port, unsigned char value) {
#ifdef z_VERBOSE
	fprintf(stderr, "WARNING: An unhandled write of value %i to port %i occurred.\n", value, port);
#else
	(void)port;
	(void)value;
#endif
	(void)mm;
}
static unsigned char z_DefaultPortInCallback(z_Machine* mm, unsigned char port) {
#ifdef z_VERBOSE
	fprintf(stderr, "WARNING: An unhandled read from port %i occurred.\n", port);
#else
	(void)port;
#endif
	(void)mm;
	return 0;
}
static unsigned short z_DefaultInterruptCallback(z_Machine* mm, unsigned char mode) {
#ifdef z_VERBOSE
	fprintf(stderr, "WARNING: Interrupts are enabled but unhandled.\n");
#else
	(void)mode;
#endif
	(void)mm;
	return 0;
}
static int z_SignExt16(int val) {
	return (val >> 15) & 1 ? val | 0xFFFF0000 : val;
}
static int z_MemEqu(char *a, char *b, int lena, int lenb) {
	if (lena != lenb) {
		return 0;
	}
	int i;
	for (i = 0; i < lena; i++) {
		if (a[i] != b[i]) return 0;
	}
	return 1;
}
static z_InstructionInfo z_InstructionLookup(unsigned char opcode, unsigned char table) {
	unsigned int loc = 3 * (opcode + ((unsigned int)table) * 256);
	z_InstructionInfo ii;
	ii.OpCode = opcode;
	ii.Table = table;
	ii.SimplifiedLength = z_OPINFO[loc + 2];
	loc = (z_OPINFO[loc] << 8) | z_OPINFO[loc + 1];
	int i;
	for (i = 0; i < ii.SimplifiedLength; i++) {
		ii.Simplified[i] = z_OPINFO[loc + i];
	}
	return ii;
}
void z_InitMachine(z_Machine* mm) {
	mm->MEM = malloc(65536);
	int i;
	for (i = 0; i < 14; i++) {
		mm->REGS[i] = 0;
	}
	for (i = 0; i < 65536; i++) {
		mm->MEM[i] = 0;
	}
	mm->T0 = 0;
	mm->T1 = 0;
	mm->TABLE = 0;
	mm->INT_ENABLED = 0;
	mm->INT_MODE = 0;
	mm->PortOutCallback = z_DefaultPortOutCallback;
	mm->PortInCallback = z_DefaultPortInCallback;
	mm->InterruptCallback = z_DefaultInterruptCallback;
}
void z_FreeMachine(z_Machine* mm) {
	free(mm->MEM);
}
void z_Reset(z_Machine* mm) {
	int i;
	for (i = 0; i < 14; i++) {
		mm->REGS[i] = 0;
	}
	for (i = 0; i < 65536; i++) {
		mm->MEM[i] = 0;
	}
	mm->T0 = 0;
	mm->T1 = 0;
	mm->TABLE = 0;
	mm->INT_ENABLED = 0;
	mm->INT_MODE = 0;
	mm->PortOutCallback = z_DefaultPortOutCallback;
	mm->PortInCallback = z_DefaultPortInCallback;
	mm->InterruptCallback = z_DefaultInterruptCallback;
}
void z_Step(z_Machine *mm) {
	if (mm->STATUS == z_IDLE) return;
	unsigned char instrop = mm->MEM[mm->REGS[z_REG_PC]];
	unsigned char instrtbl = mm->TABLE;
	z_InstructionInfo ii = z_InstructionLookup(instrop, instrtbl);
	int arg8 = mm->MEM[(mm->REGS[z_REG_PC] + 1) & 0xFFFF];
	int arg16 = mm->MEM[(mm->REGS[z_REG_PC] + 1) & 0xFFFF] | (mm->MEM[(mm->REGS[z_REG_PC] + 2) & 0xFFFF] << 8);
	int arg8i = mm->MEM[(mm->REGS[z_REG_PC] - 1) & 0xFFFF];
	int i;
	mm->TABLE = 0;

	for (i = 0; i < ii.SimplifiedLength; i++) {

		int op0 = ii.Simplified[i] >> 4;
		int op1 = ii.Simplified[i] & 0xF;
		int tmp;
		switch (op0) {
			case 0:
				mm->T0 = op1;
			break;
			case 1:
				if (op1 < 8) mm->T0 = mm->REGS[op1];
				else mm->REGS[op1 - 8] = mm->T0 & 0xFFFF;
			break;
			case 2:
				if (op1 < 8) mm->T0 = mm->REGS[op1 + 8];
				else if (op1 == 12) mm->REGS[op1 + 8 - 8] = mm->T0 & 0xFF;
				else if (op1 == 13) mm->REGS[op1 + 8 - 8] = mm->T0 & 0x7F;
				else mm->REGS[op1 + 8 - 8] = mm->T0 & 0xFFFF;
			break;
			case 3:
				if (op1 == 0) {
					tmp = mm->T0;
					mm->T0 = mm->T1;
					mm->T1 = tmp;
				} else if (op1 == 1) {
					mm->ST0 = mm->T0;
					mm->ST1 = mm->T1;
				} else if (op1 == 2) {
					mm->T0 = mm->ST0;
					mm->T1 = mm->ST1;
				} else if (op1 == 3) {
					mm->T0 += mm->T1;
				} else if (op1 == 4) {
					mm->T0 -= mm->T1;
				} else if (op1 == 5) {
					mm->T0 &= mm->T1;
				} else if (op1 == 6) {
					mm->T0 |= mm->T1;
				} else if (op1 == 7) {
					mm->T0 ^= mm->T1;
				} else if (op1 == 8) {
					mm->T0 = ~(mm->T0);
				} else if (op1 == 9) {
					mm->T0 = (mm->T0 >> 7) & 1 ? mm->T0 | 0xFFFFFF00 : mm->T0;
				} else if (op1 == 10) {
					tmp = 1;
					tmp ^= (mm->T0 >> 7) & 1;
					tmp ^= (mm->T0 >> 6) & 1;
					tmp ^= (mm->T0 >> 5) & 1;
					tmp ^= (mm->T0 >> 4) & 1;
					tmp ^= (mm->T0 >> 3) & 1;
					tmp ^= (mm->T0 >> 2) & 1;
					tmp ^= (mm->T0 >> 1) & 1;
					tmp ^= (mm->T0) & 1;
					mm->T0 = tmp;
				} else if (op1 == 11) {
					mm->T0 &= 1;
				} else if (op1 == 12) {
					mm->T0 &= 3;
				} else if (op1 == 13) {
					mm->T0 &= 0xF;
				} else if (op1 == 14) {
					mm->T0 &= 0xFF;
				} else if (op1 == 15) {
					mm->T0 &= 0xFFFF;
				}
			break;
			case 4:
				if (op1 == 0) {
					mm->T0 = mm->MEM[mm->T1 & 0xFFFF];
				} else if (op1 == 1) {
					mm->T0 = mm->MEM[mm->T1 & 0xFFFF] | (mm->MEM[(mm->T1 + 1) & 0xFFFF] << 8);
				} else if (op1 == 2) {
					mm->MEM[(mm->T1) & 0xFFFF] = mm->T0 & 0xFF;
				} else if (op1 == 3) {
					mm->MEM[(mm->T1) & 0xFFFF] = mm->T0 & 0xFF;
					mm->MEM[(mm->T1 + 1) & 0xFFFF] = (mm->T0 & 0xFF00) >> 8;
				}
			break;
			case 5:
				if (op1 == 0) {
					mm->T0 = mm->T0 == mm->T1 ? 1 : 0;
				} else if (op1 == 1) {
					mm->T0 = mm->T0 != mm->T1 ? 1 : 0;
				} else if (op1 == 2) {
					mm->T0 = mm->T0 > mm->T1 ? 1 : 0;
				} else if (op1 == 3) {
					mm->T0 = mm->T0 < mm->T1 ? 1 : 0;
				}
			break;
			case 6:
				i += mm->T0 != 0 ? op1 : 0;
			break;
			case 7:
				i += mm->T0 != 0 ? op1 + 16 : 0;
			break;
			case 8:
				mm->T0 <<= op1;
			break;
			case 9:
				mm->T0 >>= op1;
			break;
			case 10:
				mm->T0 += op1;
			break;
			case 11:
				if (op1 == 0) {
					mm->T0 = arg8;
				} else if (op1 == 1) {
					mm->T0 = arg16;
				} else if (op1 == 2) {
					mm->T0 = arg8i & 0xFF;
				} else if (op1 == 3) {
					mm->PortOutCallback(mm, mm->T1, mm->T0);
				} else if (op1 == 4) {
					mm->T0 = mm->PortInCallback(mm, mm->T1);
				}
			break;
			case 12:
				mm->TABLE = op1;
			break;
			case 13:
				if (op1 == 0) {
					mm->T0 = 0;
				} else if (op1 == 1) {
					mm->T0 &= 0x00FF;
				} else if (op1 == 2) {
					mm->T0 &= 0xFF00;
				} else if (op1 == 3) {
					#ifdef z_VERBOSE
					fprintf(stderr, "An unimplemented instruction was used (OP: %X; TBL: %i).\n", instrop, instrtbl);
					#endif
				} else if (op1 == 4) {
					#ifdef z_VERBOSE
					fprintf(stderr, "An invalid instruction was used (OP: %X, TBL: %i).\n", instrop, instrtbl);
					#endif
				} else if (op1 == 5) {
					mm->STATUS = 0;
				}
			break;
			case 14:
				if (op1 < 3) {
					mm->INT_MODE = op1;
				} else if (op1 == 3) {
					mm->INT_ENABLED = 0;
				} else if (op1 == 4) {
					mm->INT_ENABLED = 1;
				}
			break;
			case 15:
				tmp = (~(1 << op1)) & 0xFFFF;
				mm->REGS[z_REG_AF] &= tmp;
				tmp = (mm->T0 & 1) << op1;
				mm->REGS[z_REG_AF] |= tmp;
			break;
		}
	}
	if (mm->INT_ENABLED && mm->INT_MODE > 0) {
		unsigned char fire, ival;
		unsigned short iret = mm->InterruptCallback(mm, mm->INT_MODE);
		fire = iret & 0xFF;
		ival = iret >> 8;
		if (fire) {
			mm->REGS[z_REG_SP] -= 2;
			mm->MEM[mm->REGS[z_REG_SP]] = mm->REGS[z_REG_PC] & 0xFF;
			mm->MEM[mm->REGS[z_REG_SP] + 1] = mm->REGS[z_REG_PC] >> 8;
			if (mm->INT_MODE == 1) {
				mm->REGS[z_REG_PC] = 0x0038;
			} else {
				unsigned short iaddr = (mm->REGS[z_REG_I] << 8) | ival;
				mm->REGS[z_REG_PC] = mm->MEM[iaddr] | (mm->MEM[iaddr + 1] << 8);
			}
		}
	}
}
void z_Cont(z_Machine *mm) {
	mm->STATUS = z_RUNNING;
}
void z_Stop(z_Machine *mm) {
	mm->STATUS = z_IDLE;
}
void z_Jump(z_Machine *mm, unsigned short addr) {
	mm->REGS[z_REG_PC] = addr;
}
void z_Trace(z_Machine *mm) {
	z_Cont(mm);
	while (mm->STATUS == z_RUNNING) {
		z_Step(mm);
	}
}
void z_Run(z_Machine *mm, unsigned short addr) {
	z_Jump(mm, addr);
	z_Trace(mm);
}
void z_SetReg(z_Machine* mm, unsigned char reg, unsigned short val) {
	switch (reg) {
		case z_REG_AF:
		case z_REG_BC:
		case z_REG_DE:
		case z_REG_HL:
		case z_REG_IX:
		case z_REG_IY:
		case z_REG_PC:
		case z_REG_SP:
		case z_REG_AFS:
		case z_REG_BCS:
		case z_REG_DES:
		case z_REG_HLS:
			mm->REGS[reg] = val;
		break;
		case z_REG_A:
		case z_REG_B:
		case z_REG_D:
		case z_REG_H:
		case z_REG_IXH:
		case z_REG_IYH:
		case z_REG_AS:
		case z_REG_BS:
		case z_REG_DS:
		case z_REG_HS:
			mm->REGS[reg - 100] = (mm->REGS[reg - 100] & 0xFF) | ((val & 0xFF) << 8);
		break;
		case z_REG_F:
		case z_REG_C:
		case z_REG_E:
		case z_REG_L:
		case z_REG_IXL:
		case z_REG_IYL:
		case z_REG_FS:
		case z_REG_CS:
		case z_REG_ES:
		case z_REG_LS:
			mm->REGS[reg - 200] = (mm->REGS[reg - 200] & 0xFF00) | (val & 0xFF);
		break;
		case z_REG_I:
			mm->REGS[reg] = val & 0xFF;
		break;
		case z_REG_R:
			mm->REGS[reg] = val & 0x7F;
		break;
	}
}
void z_GetReg(z_Machine* mm, unsigned char reg, unsigned short* val) {
	switch (reg) {
		case z_REG_AF:
		case z_REG_BC:
		case z_REG_DE:
		case z_REG_HL:
		case z_REG_IX:
		case z_REG_IY:
		case z_REG_PC:
		case z_REG_SP:
		case z_REG_AFS:
		case z_REG_BCS:
		case z_REG_DES:
		case z_REG_HLS:
		case z_REG_I:
		case z_REG_R:
			*val = mm->REGS[reg];
		break;
		case z_REG_A:
		case z_REG_B:
		case z_REG_D:
		case z_REG_H:
		case z_REG_IXH:
		case z_REG_IYH:
		case z_REG_AS:
		case z_REG_BS:
		case z_REG_DS:
		case z_REG_HS:
			*val = mm->REGS[reg - 100] >> 8;
		break;
		case z_REG_F:
		case z_REG_C:
		case z_REG_E:
		case z_REG_L:
		case z_REG_IXL:
		case z_REG_IYL:
		case z_REG_FS:
		case z_REG_CS:
		case z_REG_ES:
		case z_REG_LS:
			*val = mm->REGS[reg - 200] & 0xFF;
		break;
	}
}
unsigned short z_GetParameter(z_Machine* mm, unsigned short num) {
	unsigned short addr = (mm->REGS[z_REG_SP]) + (num * 2) + 2;
	unsigned short ret = mm->MEM[addr++];
	ret |= mm->MEM[addr] << 8;
	return ret;
}
void z_Return(z_Machine* mm, unsigned short num) {
	mm->REGS[z_REG_HL] = num;
}
void z_ReadData(z_Machine* mm, unsigned short addr, unsigned char* data, int strlen)
{
	for (int i = 0; i < strlen; i++)
	{
		data[i] = mm->MEM[ (i + addr) % 65536 ];
	}
}
void z_WriteData(z_Machine* mm, unsigned short addr, unsigned char* data, int strlen)
{
	for (int i = 0; i < strlen; i++)
	{
		mm->MEM[ (i + addr) % 65536 ] = data[i];
	}
}
