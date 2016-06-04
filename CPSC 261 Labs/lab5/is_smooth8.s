	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc
	decq	%rsi					
	movl	$2, %edx
	movl	$1, %eax
	movq	%rsi, %r11
	jmp		.L4
.L3:
	movq	%rsi, %rdx													
.L4:
	cmpq	%rsi, %rdx
	jg		.L5	
	movq	-16(%rdi, %rdx, 8), %r10
	movq	-8(%rdi,%rdx,8), %r9									
	movq	(%rdi,%rdx,8), %rcx	
	subq	$2, %r9	
	addq	$2, %rdx	
	subq	%r9, %rcx					
	cmpq	$4, %rcx
	ja		.L2
	subq	%r9, %r10
	cmpq	$4, %r10
	jbe		.L4																			
.L2:
	xorl	%eax, %eax
	ret
.L5:
	subq	%r11, %rdx	
	cmpq	$1, %rdx
	je		.L3									
	rep					
	ret									
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
