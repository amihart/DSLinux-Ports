all:
	sh -c 'which sdcc || (echo Please install: sdcc && exit 1)'
	sh -c 'which srec_cat || (echo Please install: srecord && exit 1)'
	sh -c 'which valgrind || (echo Please install: valgrind && exit 1)'
	gcc interpret.c -o interpret -I../include -L../lib -lzeditty -std=gnu99
	sdasz80 -o crt0.rel crt0.s
	sdcc crt0.rel -mz80 --no-std-crt0 hello.c -o ~tmp.hex
	srec_cat ~tmp.hex -Intel -Output -Binary > hello.z80
	rm -f ~tmp*
	@echo "Running test..."
	valgrind ./interpret hello.z80
clean:
	rm -f interpret crt0.rel hello.z80
