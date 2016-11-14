	.file	"dispatch_func.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
.LC1:
	.string	"%d %d "
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Thread:%d is assigned to core:%d\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	dispatcher_execution
	.type	dispatcher_execution, @function
dispatcher_execution:
.LFB40:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	$simlock, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$32, %rsp
	.cfi_def_cfa_offset 64
	call	pthread_mutex_lock
	movslq	num_thrds(%rip), %rdi
	salq	$2, %rdi
	call	malloc
	movq	%rax, %rbp
	movl	num_thrds(%rip), %eax
	testl	%eax, %eax
	jle	.L5
	subl	$1, %eax
	movl	$255, %esi
	movq	%rbp, %rdi
	leaq	4(,%rax,4), %rdx
	call	memset
.L5:
	movq	threads_data_filename(%rip), %rdi
	testq	%rdi, %rdi
	je	.L3
	movl	$.LC0, %esi
	call	fopen
	movq	%rax, %rbx
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L9:
	leaq	12(%rsp), %rdx
	leaq	16(%rsp), %rcx
	movl	$.LC1, %esi
	movq	%rbx, %rdi
	xorl	%eax, %eax
	call	fscanf
	movslq	12(%rsp), %rax
	movl	16(%rsp), %edx
	movl	%edx, 0(%rbp,%rax,4)
.L8:
	movq	%rbx, %rdi
	call	feof
	testl	%eax, %eax
	je	.L9
.L3:
	movl	is_terminated(%rip), %edx
	testl	%edx, %edx
	jne	.L6
	xorl	%ebx, %ebx
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L14:
	leaq	224(%r12), %rsi
	movl	%edx, 212(%r12)
	xorl	%edi, %edi
	movl	%eax, 216(%r12)
	call	clock_gettime
	movslq	212(%r12), %rdi
	movq	%rdi, %rax
	salq	$8, %rdi
	salq	$4, %rax
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_lock
	movl	212(%r12), %ecx
	movl	4(%r12), %edx
	movl	$.LC2, %esi
	xorl	%edi, %edi
	xorl	%eax, %eax
	call	core_log
	leaq	160(%r12), %rdi
	call	pthread_cond_signal
	movslq	212(%r12), %rdi
	movq	%rdi, %rax
	salq	$8, %rdi
	salq	$4, %rax
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_unlock
.L29:
	movl	global_waitingQ+12(%rip), %eax
	cmpl	$-1, %eax
	je	.L31
	movq	global_waitingQ(%rip), %rcx
	movslq	%eax, %rdx
	leaq	(%rcx,%rdx,8), %rdx
	movq	(%rdx), %r12
	movq	$0, (%rdx)
	movl	global_waitingQ+16(%rip), %edx
	cmpl	$-1, %edx
	je	.L32
.L11:
	addl	$1, %eax
	cmpl	global_waitingQ+8(%rip), %eax
	movl	%eax, global_waitingQ+12(%rip)
	je	.L33
.L12:
	cmpl	%eax, %edx
	jne	.L13
	movl	$-1, global_waitingQ+12(%rip)
	movl	$0, global_waitingQ+16(%rip)
.L13:
	movslq	4(%r12), %rax
	movl	0(%rbp,%rax,4), %edx
	movl	$1, %eax
	cmpl	$-1, %edx
	jne	.L14
	movl	%ebx, %eax
	addl	$1, %ebx
	cltd
	idivl	num_cores(%rip)
	xorl	%eax, %eax
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L33:
	movl	$0, global_waitingQ+12(%rip)
	xorl	%eax, %eax
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L32:
	movl	%eax, global_waitingQ+16(%rip)
	movl	%eax, %edx
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L31:
	movq	carr(%rip), %rdi
	call	*balance_func(%rip)
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	movq	16(%rsp), %rcx
	leaq	20000000(%rax), %rdx
	cmpq	$999999999, %rdx
	movq	%rdx, 24(%rsp)
	jle	.L16
	addq	$1, %rcx
	subq	$980000000, %rax
	movq	%rcx, 16(%rsp)
	movq	%rax, 24(%rsp)
.L16:
	leaq	16(%rsp), %rdx
	movl	$simlock, %esi
	movl	$sched_cv, %edi
	call	pthread_cond_timedwait
	movl	is_terminated(%rip), %eax
	testl	%eax, %eax
	je	.L29
.L6:
	movl	$simlock, %edi
	call	pthread_mutex_unlock
	addq	$32, %rsp
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	dispatcher_execution, .-dispatcher_execution
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	read_core_bind_file
	.type	read_core_bind_file, @function
read_core_bind_file:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movslq	num_thrds(%rip), %rdi
	salq	$2, %rdi
	call	malloc
	movq	%rax, %rbp
	movl	num_thrds(%rip), %eax
	testl	%eax, %eax
	jle	.L38
	subl	$1, %eax
	movl	$255, %esi
	movq	%rbp, %rdi
	leaq	4(,%rax,4), %rdx
	call	memset
.L38:
	movq	threads_data_filename(%rip), %rdi
	testq	%rdi, %rdi
	je	.L42
	movl	$.LC0, %esi
	call	fopen
	movq	%rax, %rbx
	jmp	.L39
	.p2align 4,,10
	.p2align 3
.L40:
	leaq	8(%rsp), %rdx
	leaq	12(%rsp), %rcx
	movl	$.LC1, %esi
	movq	%rbx, %rdi
	xorl	%eax, %eax
	call	fscanf
	movslq	8(%rsp), %rax
	movl	12(%rsp), %edx
	movl	%edx, 0(%rbp,%rax,4)
.L39:
	movq	%rbx, %rdi
	call	feof
	testl	%eax, %eax
	je	.L40
.L42:
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE38:
	.size	read_core_bind_file, .-read_core_bind_file
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.rodata.str1.8
	.align 8
.LC5:
	.string	"malloc() failed for dispatcher"
	.section	.rodata.str1.1
.LC6:
	.string	"clone() failed for dispatcher"
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	fork_dispatcher
	.type	fork_dispatcher, @function
fork_dispatcher:
.LFB39:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$16777216, %edi
	call	malloc
	testq	%rax, %rax
	je	.L51
	leaq	16777216(%rax), %rsi
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	movl	$273, %edx
	movl	$dispatcher_execution, %edi
	call	clone
	cmpl	$-1, %eax
	je	.L52
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L52:
	.cfi_restore_state
	movl	$.LC6, %edi
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	warn
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
	movl	$.LC5, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	warn
	.cfi_endproc
.LFE39:
	.size	fork_dispatcher, .-fork_dispatcher
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
