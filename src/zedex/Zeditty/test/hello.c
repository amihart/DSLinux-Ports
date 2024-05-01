#include <stdio.h>

void main()
{
	char name[128];
	char c;
	int p = 0;
	printf("What is your name?\n");
	while ( (c = getchar()) != '\n' )
	{
		name[p++] = c;
		if (p == sizeof(name) - 1)
		{
			break;
		}
	}
	name[p] = 0;
	printf("Hello, %s!\n", name);
}
