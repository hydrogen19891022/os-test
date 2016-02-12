	.global timer_irq
	.code16
	.text
timer_irq:
	
	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	pushl %ebp
	pushl %esi
	pushl %edi

	movl p_pcb_now, %eax
	movl %esp, (%eax)

	calll sched	

	movl p_pcb_now, %eax
	movl (%eax), %esp

	popl %edi
	popl %esi
	popl %ebp
	popl %edx
	popl %ecx
	popl %ebx

	mov $0x20, %dx
	mov $0x20, %al
	out %al, %dx
	popl %eax
	iret
