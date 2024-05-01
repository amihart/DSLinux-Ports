	.globl _main
	.area _HEADER (ABS)
	.org 0
	jp _init
	.db 'Z', 'X', 2
	.ds 128
_init:
	in a, (2)
	ld l, a
	in a, (3)
	ld d, a
	in a, (4)
	ld e, a
	call _main
	out (255), a
_putchar::
	ld a, l
	out (1), a
	ret
_getchar::
	in a, (1)
	ld e, a
	ret

