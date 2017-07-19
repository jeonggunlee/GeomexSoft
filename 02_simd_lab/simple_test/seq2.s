	.file	"seq2.c"
	.comm	va,80000000,32
	.comm	vb,80000000,32
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp)
	jmp	.L2
.L5:
	movl	$0, -8(%rbp)
	jmp	.L3
.L4:
	movl	-8(%rbp), %eax
	cltq
	movss	va(,%rax,4), %xmm1
	movl	-8(%rbp), %eax
	cltq
	movss	vb(,%rax,4), %xmm0
	addss	%xmm1, %xmm0
	movl	-8(%rbp), %eax
	cltq
	movss	%xmm0, va(,%rax,4)
	addl	$1, -8(%rbp)
.L3:
	cmpl	$19999999, -8(%rbp)
	jle	.L4
	addl	$1, -4(%rbp)
.L2:
	cmpl	$999, -4(%rbp)
	jle	.L5
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
