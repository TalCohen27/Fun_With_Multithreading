	.file	"ex_1.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "Before...\12src1 is: %s \12src2 is: %s \12\0"
	.align 4
LC1:
	.ascii "After...(destination string)\12%s\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$64, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	call	___main
	movl	$543973716, 36(%esp)
	movl	$1701343043, 40(%esp)
	movl	$1684611182, 44(%esp)
	movl	$808656954, 48(%esp)
	movl	$959591730, 52(%esp)
	movl	$3290934, 56(%esp)
	movl	$1701670771, 18(%esp)
	movl	$1752461101, 22(%esp)
	movl	$1932358245, 26(%esp)
	movl	$1852404340, 30(%esp)
	movw	$103, 34(%esp)
	leal	36(%esp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %ebx
	leal	18(%esp), %eax
	movl	%eax, (%esp)
	call	_strlen
	addl	%ebx, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, 60(%esp)
	leal	36(%esp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %ecx
	leal	36(%esp), %eax
	movl	60(%esp), %edx
	movl	%eax, %esi
	movl	%edx, %edi
/APP
 # 11 "ex_1.c" 1
	rep movsb;
 # 0 "" 2
/NO_APP
	leal	36(%esp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	60(%esp), %edx
	leal	(%eax,%edx), %ebx
	leal	18(%esp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %edx
	leal	18(%esp), %eax
	movl	%eax, %esi
	movl	%ebx, %edi
	movl	%edx, %ecx
/APP
 # 12 "ex_1.c" 1
	rep movsb;
 # 0 "" 2
/NO_APP
	leal	18(%esp), %eax
	movl	%eax, 8(%esp)
	leal	36(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	60(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	60(%esp), %eax
	movl	%eax, (%esp)
	call	_free
	movl	$0, %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE7:
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
