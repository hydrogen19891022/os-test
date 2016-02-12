	.global start
	.code16gcc
	.section ".boot", "ax"
start:
	cli
	mov $0xf000, %esp
	mov $0, %ax
	mov %ax, %es
	mov $_eload_src, %eax
	subl $_sload_src, %eax
	mov %eax, %ebx
	and $0x1ff, %ebx
	mov $9, %cl
	shr %cl, %eax
	cmp $0, %ebx
	jz boot
	add $1, %eax
boot:   and $0xf, %eax
	mov $2, %ah
	mov $0, %ch
	mov $2, %cl
	mov $0, %dh
	mov $0x80, %dl
	mov $_sload_dst, %ebx
	int $0x13
	cmp $0, %ah
	jnz here
	calll main
here:	jmp here


	
	





	

