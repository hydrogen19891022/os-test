	.global inst_irq
	.code16
	.text
	.type inst_irq, @function
inst_irq:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %ds
	
	movw $0, %ax
	movw %ax, %ds
	movw 8(%ebp), %bx
	shl %bx
	shl %bx
	movw 12(%ebp), %ax
	movw %ax, (%bx)
	movw $0, 2(%bx)

	popl %ds
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	retl
	
	
