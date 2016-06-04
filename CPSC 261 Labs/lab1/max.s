	.text
	.globl	max
max:
	cmpq    %rdi, %rsi
	jg      second
	movq    %rdi, %rax
	ret
second:
	movq    %rsi, %rax
	ret
