#ifndef __IO_H__
#define __IO_H__


void outc(char c);
void prints(const char* s);
void putchar(char c);



static inline __attribute__((always_inline))
void outb(unsigned char val, unsigned short port) {
	__asm__ __volatile__("outb %b0, %w1"
				:
				:"a"(val), "Nd"(port)
				:
				);
}

static inline __attribute__((always_inline))
void outw(unsigned short val, unsigned short port) {
	__asm__ __volatile__("outw %w0, %w1"
				:
				:"a"(val), "Nd"(port)
				:			
				);
}

static inline __attribute__((always_inline))
unsigned char inb(unsigned short port) {
	unsigned char val;
	__asm__ __volatile__("inb %w0, %b1"
				:"=a"(val)
				:"Nd"(port)
				:				
				);
	return val;
}

#endif
