	.text
	.p2align 4,,15
	.globl	arraymax
arraymax:
	movabsq $-9223372036854775808, %rax // store the minimum value of a 64 bit integer in rax
	testq	%rsi, %rsi // test if index 
	jle	.Ldone
.Lloop:
	movq    (%rdi,%rsi,8), %rcx
	cmpq	%rcx, %rax
	jge     .Lskip
	movq    %rcx, %rax
.Lskip:
	dec     %rsi
	jge	.Lloop
.Ldone:
	rep
	ret
