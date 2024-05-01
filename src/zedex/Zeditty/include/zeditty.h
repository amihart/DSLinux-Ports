#ifndef __z_H__
#define __z_H__
#include <stdlib.h>
typedef struct z_Machine z_Machine;
struct z_Machine { //!show struct
	int T0, T1, ST0, ST1, INT_ENABLED, INT_MODE, TABLE, STATUS;
	int REGS[14];
	////!show struct The program memory is located here.
	unsigned char* MEM; //!show struct
	////!show struct This callback is executed whenever
	////!show struct the interpreter encounters an OUT
	////!show struct instruction.
	void (*PortOutCallback)(z_Machine*, unsigned char, unsigned char); //!show struct
	////!show struct This callback is executed whenever
	////!show struct the interpreter encounters an IN
	////!show struct instruction.
	unsigned char (*PortInCallback)(z_Machine*, unsigned char); //!show struct
	////!show struct This callback is executed
	////!show struct repeatedly when interrupts are
	////!show struct enabled. The lower byte is 1 or 0
	////!show struct indicating whether or not the
	////!show struct interrupt should be fired. The
	////!show struct upper byte is used for Mode 2
	////!show struct interrupts as the value combined
	////!show struct combined with the I register.
	unsigned short (*InterruptCallback)(z_Machine*, unsigned char); //!show struct
}; //!show struct
//Instruction info
typedef struct {
	unsigned char OpCode, Table;
	unsigned char SimplifiedLength;
	unsigned char Simplified[256];
} z_InstructionInfo;
//Defines
#define z_IDLE 0
#define z_RUNNING 1
#define z_REG_AF 0
#define z_REG_BC 1
#define z_REG_DE 2
#define z_REG_HL 3
#define z_REG_IX 4
#define z_REG_IY 5
#define z_REG_PC 6
#define z_REG_SP 7
#define z_REG_AFS 8
#define z_REG_BCS 9
#define z_REG_DES 10
#define z_REG_HLS 11
#define z_REG_I 12
#define z_REG_R 13
#define z_REG_A 100
#define z_REG_F 200
#define z_REG_B 101
#define z_REG_C 201
#define z_REG_D 102
#define z_REG_E 202
#define z_REG_H 103
#define z_REG_L 203
#define z_REG_AS 108
#define z_REG_FS 208
#define z_REG_BS 109
#define z_REG_CS 209
#define z_REG_DS 110
#define z_REG_ES 210
#define z_REG_HS 111
#define z_REG_LS 211
#define z_REG_IXH 105
#define z_REG_IXL 205
#define z_REG_IYH 106
#define z_REG_IYL 206
//Creates a new z_Machine with the
//default values set.
void z_InitMachine(z_Machine* mm); //!show func
//Frees memory associated with a z_Machine
void z_FreeMachine(z_Machine* mm); //!show func
//Resets a z_Machine to its default values.
void z_Reset(z_Machine* mm); //!show func
//If the status of the machine is z_RUNNING and
//not z_IDLE, then this will execute a single
//instruction at the current memory address. If it
//encounters the HALT instruction, then the status
//will be changed to z_IDLE.
void z_Step(z_Machine* mm); //!show func
//Sets the status of the machine to z_RUNNING.
void z_Cont(z_Machine* mm); //!show func
//Sets the status of the machine to z_IDLE.
void z_Stop(z_Machine* mm); //!show func
//Jumps to a memory address (sets PC).
void z_Jump(z_Machine* mm, unsigned short addr); //!show func
//Begins executing instructions at the current
//program counter until the HALT instruction is
//reached. This is a blocking operation.
void z_Trace(z_Machine* mm); //!show func
//Jumps to a memory address and begins executing
//instructions until the HALT instruction is reached.
//This is a blocking operation.
void z_Run(z_Machine* mm, unsigned short addr); //!show func
//Set the value of a register.
//Use this rather than trying to access registers directly.
void z_SetReg(z_Machine* mm, unsigned char reg, unsigned short val); //!show func
//Gets the value of a register.
void z_GetReg(z_Machine* mm, unsigned char reg, unsigned short* val); //!show func
//Read data from memory
void z_ReadData(z_Machine* mm, unsigned short addr, unsigned char* data, int strlen); //!show func
//Write data to memory
void z_WriteData(z_Machine* mm, unsigned short addr, unsigned char* data, int strlen); //!show func
//used internally
extern const unsigned char z_OPINFO[45785];
#endif

