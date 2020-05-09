	.file	"open_close.c"
	.section	.rodata
.LC0:
	.string	"Test\n"
.LC1:
	.string	"error\n"
.LC2:
	.string	"Please input string : "
.LC3:
	.string	"read_error\n"
.LC4:
	.string	"fp.txt"
.LC5:
	.string	"open error\n"
.LC6:
	.string	"write to open-file is error\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$12, %edi
	call	malloc
	movq	%rax, -24(%rbp)
	movl	$5, %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	call	write
	cmpq	$-1, %rax
	jne	.L2
	movl	$6, %edx
	movl	$.LC1, %esi
	movl	$2, %edi
	call	write
	movl	$1, %edi
	call	exit
.L2:
	movl	$22, %edx
	movl	$.LC2, %esi
	movl	$1, %edi
	call	write
	movq	-24(%rbp), %rax
	movl	$11, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	read
	movl	%eax, -12(%rbp)
	cmpl	$-1, -12(%rbp)
	jne	.L3
	movl	$11, %edx
	movl	$.LC3, %esi
	movl	$2, %edi
	call	write
	movl	$2, %edi
	call	exit
.L3:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	write
	movl	$384, %edx
	movl	$1025, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	open
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L4
	movl	$11, %edx
	movl	$.LC5, %esi
	movl	$2, %edi
	call	write
	movl	$3, %edi
	call	exit
.L4:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rcx
	movl	-4(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write
	movl	%eax, -8(%rbp)
	cmpl	$-1, -8(%rbp)
	jne	.L5
	movl	$28, %edx
	movl	$.LC6, %esi
	movl	$2, %edi
	call	write
	movl	$4, %edi
	call	exit
.L5:
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	close
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-36)"
	.section	.note.GNU-stack,"",@progbits
