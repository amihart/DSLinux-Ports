#include <stdio.h>
#include <zeditty.h>

void ports_out(z_Machine *mm, unsigned char port, unsigned char value)
{
	switch (port)
	{
		case 0x00: putchar(value); break;
		case 0xFF: z_Stop(mm); break;
		default:
			fprintf(stderr, "Invalid port write (%i;%i).\n", port, value);
	}
}

unsigned char ports_in(z_Machine *mm, unsigned char port)
{
	switch (port)
	{
		case 0x00: return getchar();
		default:
			fprintf(stderr, "Invalid port read (%i).\n", port);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
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
	for (int c, i = 0; (c = fgetc(f)) != EOF; i++)
	{
		unsigned char b = (unsigned char)c;
		z_WriteData(&mm, i, &b, 1);
	}
	fclose(f);
	//Run the program
	z_Run(&mm, 0x0000);
	z_FreeMachine(&mm);
	return 0;
}
