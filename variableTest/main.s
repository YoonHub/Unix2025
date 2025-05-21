	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"i = %d\n"
.LC1:
	.string	"j = %d\n"
.LC2:
	.string	"k = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	endbr64
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$10, %edx
	movl	$2, %edi
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	movl	$30, 12(%rsp)
	call	__printf_chk@PLT
	movl	$20, %edx
	leaq	.LC1(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	12(%rsp), %edx
	movl	$2, %edi
	xorl	%eax, %eax
	leaq	.LC2(%rip), %rsi
	call	__printf_chk@PLT
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
