	.file	"is_smooth.c"
	.text
	.globl	is_smooth
	.type	is_smooth, @function
is_smooth:
.LFB0:
	.cfi_startproc						
	movl	$1, %edx					# initialize index to 1
	jmp		.L2							# jump to .L2
.L4:									# if statement condition check
	movq	(%rdi,%rdx,8), %rax			# store array[index] in %rax
	subq	-8(%rdi,%rdx,8), %rax		# subtract array[index-1] from array[index]
	addq	$2, %rax					# since negative values look like very large unsigned integers, add 2 to the result of the 
										# previous operation stored in %rax to account for the case where the difference is -2 or -1
	cmpq	$4, %rax					# compare %rax to 4 (since we added 2)
	ja		.L5							# unsigned comparison: if %rax is above 4, jump to .L5 -> for example, if the difference is -3;
										# it will still look like a large unsigned integer after adding 2, and thus be above 4  
	addq	$1, %rdx					# increment index
.L2:									# for loop condition check
	cmpq	%rsi, %rdx					# compare index to size
	jl		.L4							# if index is less than size, jump to .L4
	movl	$1, %eax					# if not, we are done with the loop, so store the return value (1) in %eax
	ret									# return
.L5:									# inside the if statement (i.e. if statement condition is satisfied)
	movl	$0, %eax					# store the return value (0) in %eax
	ret									# return
	.cfi_endproc						
.LFE0:
	.size	is_smooth, .-is_smooth
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
