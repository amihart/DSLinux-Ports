	.globl _main
	.area _HEADER (ABS)
	.org 0
	call _main
	out (255), a
_putchar::
	ld a, l
	out (0), a
	ret
_getchar::
	in a, (0)
	ld e, a
	ret
