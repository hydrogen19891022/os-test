#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <io.h>
#include <irq.h>


#define NULL (void*)0


struct pcb {
	void* stack;
	struct pcb *p_next;
	struct pcb *p_prev;
	
};

struct pcb* p_pcb_now;

void sched();
void init();
void create_task(void (*f)(), void* stack_bottom);

#endif
