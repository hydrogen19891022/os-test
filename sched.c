#include <kernel.h>

void sched() {
	p_pcb_now = p_pcb_now->p_next;
}
