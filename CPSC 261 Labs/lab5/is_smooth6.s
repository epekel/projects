	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	movq	$0, %r11
	xorl	%eax, %eax
.L4:					
	cmpq	%rsi, %r11 
	jge		.L2
	movq	(%rdi, %r11, 8), %rcx
	movq	8(%rdi, %r11, 8), %r8
	movq	16(%rdi, %r11, 8), %r9
	movq	24(%rdi, %r11, 8), %r10
	movq	%rcx, %rdx
	subq	%r8, %rdx
	addq	$2, %rdx
	cmpq	$4, %rdx
	jbe		.L5
	movq	%r8, %rdx
	subq	%r9, %rdx
	addq	$2, %rdx
	cmpq	$4, %rdx
	jbe		.L5
	movq	%r9, %rdx
	subq	%r10, %rdx
	addq	$2, %rdx
	cmpq	$4, %rdx
	jbe		.L5
	addq	$4, %r11
	jmp		.L4
.L5:
	rep
	ret							  					
.L2:															
	movl	$1, %eax					
	ret																
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbitsemacs