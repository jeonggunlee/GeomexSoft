	.file	"vector.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.section	.text.startup,"ax",@progbits
.LHOTB0:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB4596:
	.cfi_startproc
	movl	$1000, %edx
	.p2align 4,,10
	.p2align 3
.L2:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	vmovaps	va(%rax), %ymm0
	addq	$32, %rax
	vaddps	vb-32(%rax), %ymm0, %ymm0
	vmovaps	%ymm0, va-32(%rax)
	cmpq	$160000000, %rax
	jne	.L3
	subl	$1, %edx
	jne	.L2
	vzeroupper
	ret
	.cfi_endproc
.LFE4596:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE0:
	.section	.text.startup
.LHOTE0:
	.comm	vb,160000000,32
	.comm	va,160000000,32
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
