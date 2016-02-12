#include <io.h>

void out(char c);

void prints(const char* s) {
	volatile char* p = (volatile char*)(0x5000);	
	/*while (*s) {
		c = *s ++;
		
		__asm__ __volatile__ ("movb %0, %%al\n\t"\
				      "movb $0x0e, %%ah\n\t"\
				      "movb $0x00, %%bh\n\t"\
				      "movb $0x07, %%bl\n\t"\
				      "int $0x10"
					:
					:"m"(c)
					:);
		outc(c);
	}*/
	while (*s) {
		putchar(*s++);	
	}

	
	
}

void putchar(char c) {
	if (c == '\n') {
		putchar('\r');
	}
	outc(c);
}

