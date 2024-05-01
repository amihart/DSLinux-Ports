#include <unistd.h>
#include <sys/syscall.h>

void main()
{
	char str[] = "Hello, World!\n";
	syscall(__NR_write, 1, str, sizeof(str));
}
