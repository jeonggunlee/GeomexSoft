	.file	"vec2.c"
	.comm	va,160000000,32
	.comm	vb,160000000,32
	.text
	.globl	main
	.type	main, @function
main:
.LFB3448:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x78,0x6
	movl	$0, -88(%rbp)
	jmp	.L2
.L6:
	movl	$0, -84(%rbp)
	jmp	.L3
.L5:
	movl	-84(%rbp), %eax
	cltq
	salq	$5, %rax
	addq	$vb, %rax
	vmovaps	(%rax), %ymm0
	movl	-84(%rbp), %eax
	cltq
	salq	$5, %rax
	addq	$va, %rax
	vmovaps	(%rax), %ymm1
	vmovaps	%ymm1, -80(%rbp)
	vmovaps	%ymm0, -48(%rbp)
	vmovaps	-80(%rbp), %ymm0
	vaddps	-48(%rbp), %ymm0, %ymm0
	movl	-84(%rbp), %eax
	cltq
	salq	$5, %rax
	addq	$va, %rax
	vmovaps	%ymm0, (%rax)
	addl	$1, -84(%rbp)
.L3:
	cmpl	$4999999, -84(%rbp)
	jle	.L5
	addl	$1, -88(%rbp)
.L2:
	cmpl	$999, -88(%rbp)
	jle	.L6
	nop
	popq	%r10
	.cfi_def_cfa 10, 0
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3448:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
