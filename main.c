#include <kernel.h>


char stk1[512];
char stk2[512];

void task1() {
	int i = 0;
	while (1) {
		putchar((char)i+'0');
		i ++;
		__asm__ __volatile__ ("hlt\n");
		
	}
}

void task2() {
	while (1) {
		prints("Hello from task2\n");
		__asm__ __volatile__ ("hlt\n");
		
	}
}

void main() {
	char s[10] = {0x30, 0x31, 0x00};
	prints("Hello\n");
	inst_irq(0x08, timer_irq);
	init();
	create_task(task1, &stk1[510]);
	create_task(task2, &stk2[510]);
	__asm__ __volatile__ ("sti\n");

	while (1) {
		prints("Hello from kernel task\n");
		__asm__ __volatile__ ("hlt\n");
		
	}
			

}




