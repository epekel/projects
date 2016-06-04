	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	movl	$1, %edx
	movq 	(%rdi), %r9
	movq	$0, %rax
.L4:					
	cmpq	%rsi, %rdx
	jge		.L2	
	movq	(%rdi, %rdx, 8), %r10
	movq	%r10, %r11											
	addq	$2, %r11					
	cmpq	$4, %r11					
	ja		.L5
	movq	%r10, %r9
	incq	%rdx
	jmp	.L4
							  					
.L2:															
	movl	$1, %eax					
	ret		
.L5:
	rep
	ret														
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits


# array[0] store in r9, array[index] store in r10 r9 = r10, increment?
# reduce memory access, branch, can use more registers
# decrement size instead of using index, try to fix data hazards
# offset register
# shift
# 