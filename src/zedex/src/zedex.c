#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <zeditty.h>
#include <unistd.h>
#include <sys/syscall.h>
#define HEADER_SIZE 6
extern uint64_t CALL_TABLE[];
uint16_t CALL_ARGV;
uint16_t CALL_ARGC;
void ports_out(z_Machine *mm, unsigned char port, unsigned char value)
{
	unsigned short argc;
	unsigned short addr;
	uint64_t argv[8];
	switch (port)
	{
		case 0:
			z_GetReg(mm, z_REG_HL, &argc);
			z_GetReg(mm, z_REG_DE, &addr);
			for (int i = 0; i < 8; i++)
			{
				if (i >= argc)
					argv[i] = 0;
				else
					z_ReadData(mm, addr + i * sizeof(uint64_t), (unsigned char*)(argv + i), sizeof(uint64_t));
			}
			//we have to offset certain arguments if they're related to memory addressing
			for (int i = 0; i < CALL_TABLE_SIZE; i += 2)
			{
				if (CALL_TABLE[i] == argv[0])
				{
					for (int j = 1; j < argc; j++)
					{
						if ( (CALL_TABLE[i + 1] >> (j - 1))&1 )
						{
							argv[j] += (uint64_t)((long)(mm->MEM));
						}
					}
					break;
				}
			}
			syscall
			(
				(long)argv[0],
				(long)argv[1],
				(long)argv[2],
				(long)argv[3],
				(long)argv[4],
				(long)argv[5],
				(long)argv[6]
			);
		break;
		case 0x01: putchar(value); break;
		case 0xFF: z_Stop(mm); break;
		default:
			fprintf(stderr, "Invalid port write (%i;%i).\n", port, value);
	}
}

unsigned char ports_in(z_Machine *mm, unsigned char port)
{
	switch (port)
	{
		case 0x01: return getchar();
		case 0x02: return CALL_ARGC;
		case 0x03: return CALL_ARGV >> 8;
		case 0x04: return CALL_ARGV;
		default:
			fprintf(stderr, "Invalid port read (%i).\n", port);
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [file]\n", argv[0]);
		exit(1);
	}

	//Setup our virtual machine
	z_Machine mm;
	z_InitMachine(&mm);
	mm.PortOutCallback = ports_out;
	mm.PortInCallback = ports_in;

	//Load our program
	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		fprintf(stderr, "File `%s` not found.\n", argv[1]);
		exit(1);
	}

	unsigned char header[HEADER_SIZE];
	for (int c, i = 0; (c = fgetc(f)) != EOF; i++)
	{
		if (i == 65536)
		{
			z_FreeMachine(&mm);
			fclose(f);
			fprintf(stderr, "Error: File too large.\n");
			exit(1);
		}
		unsigned char b = (unsigned char)c;
		z_WriteData(&mm, i, &b, 1);
		if (i < HEADER_SIZE)
		{
			header[i] = b;
		}
	}
	fclose(f);

	int version = 0;
	if (header[0] == 0xC3 && header[3] == 0x5A && header[4] == 0x58)
	{
		version = (int)header[5];
		if (version != 2)
		{
			fprintf(stderr, "Error: Unsupported CRT0 version.\n");
			z_FreeMachine(&mm);
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "Error: Bad magic number.\n");
		z_FreeMachine(&mm);
		exit(1);
	}

	//load argument data
	uint16_t argtab[256];
	uint8_t argtabL = 0;
	uint16_t argstart = HEADER_SIZE;
	uint16_t argend = argstart + 128;

	uint16_t pos = argend;
	for (int i = 1; i < (argc > 64 ? 64 : argc); i++)
	{
		int l = strlen(argv[i]) + 1;
		int estaddr = pos - (l + (argtabL + 1) * sizeof(uint16_t));
		if ( estaddr < argstart )
		{
			break;
		}

		pos -= l;
		z_WriteData(&mm, pos, (unsigned char*)argv[i], l);
		argtab[argtabL++] = pos;
	}
	pos -= argtabL * sizeof(uint16_t);
	CALL_ARGV = pos;
	CALL_ARGC = argtabL;
	for (int i = 0; i < argtabL; i++)
	{
		unsigned char u = argtab[i] >> 8;
		unsigned char l = argtab[i] & 0xFF;
		z_WriteData(&mm, pos++, &l, 1);
		z_WriteData(&mm, pos++, &u, 1);
	}

	//Run the program
	z_Run(&mm, 0x0000);
	
	//Fetch the return value
	uint16_t r;
	z_GetReg(&mm, z_REG_DE, &r);
	z_FreeMachine(&mm);
	
	return (int)((int16_t)r);
}
