#include <stdint.h>
#include "sysarg.h"

#define syscall(...) VARGS(__SYSCALL__, __VA_ARGS__)
void __SYSCALL__(uint16_t argc, uint64_t *argv)
{
	__asm
		out (0), a
	__endasm;
	(void)argc;
	(void)argv;
}
