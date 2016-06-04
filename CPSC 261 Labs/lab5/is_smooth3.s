	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	movl	$1, %dl
.L4:					
	cmpl	%esi, %edx
	jge		.L2															
	movl	(%rdi,%rdx,8), %eax			
	subl	-8(%rdi,%rdx,8), %eax		
	addl	$2, %eax
	addl	$1, %edx					
	cmpl	$4, %eax					
	jbe		.L4
	xorl	%eax, %eax
	ret							  					
.L2:															
	movl	$1, %al					
	ret																
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits