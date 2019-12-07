	.file	"my_lock.C"
	.globl	gm
	.bss
	.align 8
	.type	gm, @object
	.size	gm, 8
gm:
	.zero	8
	.text
	.globl	_Z9benchmarkPv
	.type	_Z9benchmarkPv, @function
_Z9benchmarkPv:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -56(%rbp)
	movq	gm(%rip), %rax
	movl	28(%rax), %eax
	movl	%eax, -60(%rbp)
	movq	gm(%rip), %rax
	movl	32(%rax), %eax
	movl	%eax, -64(%rbp)
	movq	gm(%rip), %rax
	movl	36(%rax), %eax
	movl	%eax, -68(%rbp)
	movq	gm(%rip), %rax
	movl	40(%rax), %r15d
	movl	$0, %r13d
	movl	$0, %r12d
	movl	$0, %r14d
	jmp	.L2
.L7:
	movq	gm(%rip), %rax
	movq	48(%rax), %rax
	movq	%rax, %rdi
	call	_Z6s_lockP10simplelock
	movl	$0, %ebx
	jmp	.L3
.L4:
	addl	$1, %r12d
	addl	$1, %ebx
.L3:
	cmpl	-64(%rbp), %ebx
	jl	.L4
	movq	gm(%rip), %rax
	movq	48(%rax), %rax
	movq	%rax, %rdi
	call	_Z8s_unlockP10simplelock
	movl	$0, %ebx
	jmp	.L5
.L6:
	addl	$1, %r13d
	addl	$1, %ebx
.L5:
	cmpl	-68(%rbp), %ebx
	jl	.L6
	addl	$1, %r14d
.L2:
	cmpl	-60(%rbp), %r14d
	jl	.L7
	movq	gm(%rip), %rax
	movq	16(%rax), %rax
	movslq	%r15d, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leal	0(%r13,%r12), %edx
	movl	%edx, (%rax)
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	_Z9benchmarkPv, .-_Z9benchmarkPv
	.section	.rodata
	.align 8
.LC0:
	.string	"Usage: my_loc problem p M K\nAborting..."
	.align 8
.LC1:
	.string	"available result number is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	cmpl	$4, -68(%rbp)
	je	.L9
	movl	$.LC0, %edi
	call	puts
	movl	$0, %edi
	call	exit
.L9:
	movq	gm(%rip), %rbx
	movq	-80(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, 24(%rbx)
	movl	24(%rbx), %eax
	movl	%eax, -20(%rbp)
	movq	gm(%rip), %rax
	movl	$2000000, 28(%rax)
	movq	gm(%rip), %rbx
	movq	-80(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, 36(%rbx)
	movq	gm(%rip), %rbx
	movq	-80(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, 32(%rbx)
	movq	gm(%rip), %rbx
	movl	-20(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, 16(%rbx)
	movq	16(%rbx), %rax
	movq	%rax, -32(%rbp)
	movq	gm(%rip), %rbx
	movl	-20(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, (%rbx)
	movq	(%rbx), %rax
	movq	%rax, -40(%rbp)
	movq	gm(%rip), %rbx
	movl	-20(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, 8(%rbx)
	movq	8(%rbx), %rax
	movq	%rax, -48(%rbp)
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -56(%rbp)
	movq	gm(%rip), %rax
	movq	48(%rax), %rax
	movq	%rax, %rdi
	call	_Z11s_lock_initP10simplelock
	movl	$0, -64(%rbp)
	jmp	.L10
.L11:
	movq	gm(%rip), %rax
	movl	-64(%rbp), %edx
	movl	%edx, 40(%rax)
	movl	-64(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	leaq	(%rdx,%rax), %rdi
	leaq	-64(%rbp), %rax
	movq	%rax, %rcx
	movl	$_Z9benchmarkPv, %edx
	movl	$0, %esi
	call	pthread_create
	movl	-64(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -64(%rbp)
.L10:
	movl	-64(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L11
	movl	$0, -64(%rbp)
	jmp	.L12
.L13:
	movl	-64(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	movl	-64(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -64(%rbp)
.L12:
	movl	-64(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L13
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	$0, -60(%rbp)
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$10, %edi
	call	putchar
	movl	$0, %eax
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-36)"
	.section	.note.GNU-stack,"",@progbits
