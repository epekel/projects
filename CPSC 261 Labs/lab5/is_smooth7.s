	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	movl	$1, %edx
	movl	$1, %eax												
.L4:
	cmpq	%rsi, %rdx
	jge		.L5	
	movq	-8(%rdi,%rdx,8), %r9									
	movq	(%rdi,%rdx,8), %rcx
	subq	$2, %r9	
	incq	%rdx	
	subq	%r9, %rcx					
	cmpq	$4, %rcx
	jbe		.L4												
	xorl	%eax, %eax								
.L5:									
	rep					
	ret									
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
