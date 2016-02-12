#include <kernel.h>

#define PCB_CNT 10

static struct pcb pcbs[PCB_CNT];
static struct pcb* p_free_pcb = NULL;
static struct pcb* p_used_pcb = NULL;


static void init_pcbs();
static struct pcb* get_pcb(struct pcb** p_pcb_pool);
static void insert_pcb(struct pcb** p_pcb_pool, struct pcb* p_insert);

void init() {
	struct pcb* p_kernel_pcb;


	init_pcbs();
	p_kernel_pcb = get_pcb(&p_free_pcb);
	if (NULL == p_kernel_pcb)
		return;
	insert_pcb(&p_used_pcb, p_kernel_pcb);
	
	p_kernel_pcb->stack = NULL;
	p_pcb_now = p_kernel_pcb;
}

void create_task(void (*f)(), void* stack_bottom) {
	unsigned short *sp = stack_bottom;
	unsigned long *esp;
	
	struct pcb *p_pcb = get_pcb(&p_free_pcb);
	if (NULL == p_pcb)
		return;
	insert_pcb(&p_used_pcb, p_pcb);
	/*prepare stack for task*/
	*sp-- = 0x0202;//flags
	*sp-- = 0;//cs
	*sp = (unsigned short)f;//ip
	esp = (unsigned long*)sp;
	esp --;
	*esp-- = 0xAAAAAAAA;//eax
	*esp-- = 0xBBBBBBBB;//ebx
	*esp-- = 0xCCCCCCCC;//ecx
	*esp-- = 0xDDDDDDDD;//edx
	*esp-- = 0xEEEEEEEE;//ebp
	*esp-- = 0xFFFFFFFF;//esi
	*esp = 0xABABABAB;//edi
	p_pcb->stack = esp;	
	
}

void init_pcbs() {
	int i;
	for (i=1; i<PCB_CNT-1; i++) {
		pcbs[i].p_next = &pcbs[i+1];
		pcbs[i].p_prev = &pcbs[i-1];
		pcbs[i].stack = NULL;
	}
	
	pcbs[0].p_next = &pcbs[1];
	pcbs[0].p_prev = &pcbs[PCB_CNT-1];
	pcbs[PCB_CNT-1].p_next = &pcbs[0];
	pcbs[PCB_CNT-1].p_prev = &pcbs[PCB_CNT-2];
	p_free_pcb = &pcbs[0];
	p_used_pcb = NULL;
}

static struct pcb* get_pcb(struct pcb** p_pcb_pool) {
	struct pcb* p_prev = NULL;
	struct pcb* p_next = NULL;
	struct pcb* ret = NULL;
	if (NULL == *p_pcb_pool) {
		return NULL;	
	}
	p_prev = (*p_pcb_pool)->p_prev;
	p_next = (*p_pcb_pool)->p_next;
	if (*p_pcb_pool == p_prev && *p_pcb_pool == p_next) {
		ret = *p_pcb_pool;
		*p_pcb_pool = NULL;
		ret->p_next = NULL;
		ret->p_prev = NULL;
		return 	ret;
	} else {
		ret = *p_pcb_pool;
		*p_pcb_pool = p_next;
		p_prev->p_next = p_next;
		p_next->p_prev = p_prev;
		ret->p_next = NULL;
		ret->p_prev = NULL;
		return ret;	
	}
}

static void insert_pcb(struct pcb** p_pcb_pool, struct pcb* p_insert) {
	struct pcb* p_prev = NULL;
	struct pcb* p_next = NULL;
	struct pcb* ret = NULL;
	if (NULL == p_insert) {
		return;	
	} else if (NULL == *p_pcb_pool) {
		*p_pcb_pool = p_insert;
		(*p_pcb_pool)->p_next = p_insert;
		(*p_pcb_pool)->p_prev = p_insert;	
	} else {
		p_next = (*p_pcb_pool)->p_next;
		(*p_pcb_pool)->p_next = p_insert;
		p_next->p_prev = p_insert;
		p_insert->p_next = p_next;
		p_insert->p_prev = (*p_pcb_pool);
		*p_pcb_pool = p_insert;
	}
}













