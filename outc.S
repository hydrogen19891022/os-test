	.global outc
	.code16gcc
	.text
	.type outc, @function
outc:
	push %ebp
	mov %esp, %ebp
	pushl %eax
	pushl %ebx
	movb 8(%ebp), %al
	movb $0x0e, %ah
	movb $0x00, %bh
	movb $0x07, %bl
	int $0x10
	popl %ebx
	popl %eax
	mov %ebp, %esp
	pop %ebp
	retl

/*
在gcc中如果C程序有__asm__(".code16gcc");说明为实模式编译代码
但是这种方法并不会将代码生成为标准的16位代码，而仅仅是为代码添
加了操作符宽度和地址宽度前缀，使原来在保护模式下运行的32位代码
变为在实模式下运行的32位代码（即所有操作都为32位），所以在这里
必须使用32位的操作

.code16gcc和.code16的区别在于前者的`call', `ret', `enter', `leave', `push', `pop', `pusha', `popa', `pushf', and `popf' 指令都为32位宽
*/
