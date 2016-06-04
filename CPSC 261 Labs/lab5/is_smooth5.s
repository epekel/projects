	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	subq	$1, %rsi
	xorl	%eax, %eax
.L4:					
	cmpq	$0, %rsi 
	jl	.L2
	movq	(%rdi, %rsi, 8), %rcx
	movq	-8(%rdi, %rsi, 8), %r8
	movq	-16(%rdi, %rsi, 8), %r9
	movq	-24(%rdi, %rsi, 8), %r10
	movq	-32(%rdi, %rsi, 8), %r11 														
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
	movq	%r10, %rdx
	subq	%r11, %rdx
	addq	$2, %rdx
	cmpq	$4, %rdx
	jbe		.L5
	subq	$5, %rsi
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