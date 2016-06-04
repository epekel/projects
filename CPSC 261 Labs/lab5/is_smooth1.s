	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	movq	$1, %rdx
.L4:					
	cmpq	%rsi, %rdx
	jge		.L2															
	movq	(%rdi,%rdx,8), %rax			
	subq	-8(%rdi,%rdx,8), %rax		
	addq	$2, %rax
	addq	$1, %rdx					
	cmpq	$4, %rax					
	jbe		.L4
	movq	$0, %rax
	ret							  					
.L2:															
	movq	$1, %rax					
	ret																
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits