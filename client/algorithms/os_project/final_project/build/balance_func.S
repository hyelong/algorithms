	.file	"balance_func.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	noop
	.type	noop, @function
noop:
.LFB38:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE38:
	.size	noop, .-noop
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Balancer: A ready thread[%d] is moved to core:%d \n"
	.align 8
.LC2:
	.string	"Balancer: A ready thread[%d] is added from core:%d \n"
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	less_frequent_work_stealing
	.type	less_frequent_work_stealing, @function
less_frequent_work_stealing:
.LFB39:
	.cfi_startproc
	movl	num_cores(%rip), %esi
	testl	%esi, %esi
	jle	.L37
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	xorl	%r12d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	xorl	%ebx, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L4:
	addl	$1, %r12d
	addq	$240, %rbx
	cmpl	%r12d, num_cores(%rip)
	jle	.L41
.L31:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_trylock
	testl	%eax, %eax
	jne	.L4
	movq	carr(%rip), %rax
	subq	$8, %rsp
	.cfi_def_cfa_offset 72
	pushq	176(%rax,%rbx)
	.cfi_def_cfa_offset 80
	pushq	168(%rax,%rbx)
	.cfi_def_cfa_offset 88
	pushq	160(%rax,%rbx)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	addq	$32, %rsp
	.cfi_def_cfa_offset 64
	testl	%eax, %eax
	jne	.L23
	movq	carr(%rip), %rax
	leaq	(%rax,%rbx), %rdi
	movl	232(%rdi), %ecx
	testl	%ecx, %ecx
	js	.L42
.L6:
	addq	$24, %rdi
	call	pthread_mutex_unlock
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L23:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L41:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_restore 13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_restore 14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_restore 15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L42:
	.cfi_restore_state
	movl	num_cores(%rip), %edx
	testl	%edx, %edx
	jle	.L6
	xorl	%ebp, %ebp
	xorl	%r13d, %r13d
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L7:
	addl	$1, %r13d
	addq	$240, %rbp
	cmpl	%r13d, num_cores(%rip)
	jle	.L23
	movq	carr(%rip), %rax
.L24:
	leaq	24(%rax,%rbp), %rdi
	call	pthread_mutex_trylock
	testl	%eax, %eax
	jne	.L7
	movq	carr(%rip), %rax
	subq	$8, %rsp
	.cfi_def_cfa_offset 72
	pushq	176(%rax,%rbx)
	.cfi_def_cfa_offset 80
	pushq	168(%rax,%rbx)
	.cfi_def_cfa_offset 88
	pushq	160(%rax,%rbx)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	movl	%eax, %r14d
	movq	carr(%rip), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 72
	pushq	200(%rax,%rbx)
	.cfi_def_cfa_offset 80
	pushq	192(%rax,%rbx)
	.cfi_def_cfa_offset 88
	pushq	184(%rax,%rbx)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	addl	%eax, %r14d
	movq	carr(%rip), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 72
	pushq	224(%rax,%rbx)
	.cfi_def_cfa_offset 80
	pushq	216(%rax,%rbx)
	.cfi_def_cfa_offset 88
	pushq	208(%rax,%rbx)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	addl	%eax, %r14d
	movq	carr(%rip), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 72
	pushq	176(%rax,%rbp)
	.cfi_def_cfa_offset 80
	pushq	168(%rax,%rbp)
	.cfi_def_cfa_offset 88
	pushq	160(%rax,%rbp)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	movl	%eax, %r15d
	movq	carr(%rip), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 72
	pushq	200(%rax,%rbp)
	.cfi_def_cfa_offset 80
	pushq	192(%rax,%rbp)
	.cfi_def_cfa_offset 88
	pushq	184(%rax,%rbp)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	addl	%eax, %r15d
	movq	carr(%rip), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 72
	pushq	224(%rax,%rbp)
	.cfi_def_cfa_offset 80
	pushq	216(%rax,%rbp)
	.cfi_def_cfa_offset 88
	pushq	208(%rax,%rbp)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	leal	1(%r14,%r14), %edx
	addl	%r15d, %eax
	addq	$32, %rsp
	.cfi_def_cfa_offset 64
	cmpl	%edx, %eax
	jle	.L8
	movq	carr(%rip), %rax
	subq	$8, %rsp
	.cfi_def_cfa_offset 72
	pushq	176(%rax,%rbp)
	.cfi_def_cfa_offset 80
	pushq	168(%rax,%rbp)
	.cfi_def_cfa_offset 88
	pushq	160(%rax,%rbp)
	.cfi_def_cfa_offset 96
	xorl	%eax, %eax
	call	get_list_count
	addq	$32, %rsp
	.cfi_def_cfa_offset 64
	testl	%eax, %eax
	jle	.L8
	movq	%rbp, %rdx
	addq	carr(%rip), %rdx
	movl	172(%rdx), %eax
	cmpl	$-1, %eax
	je	.L11
	movq	160(%rdx), %rsi
	movslq	%eax, %rcx
	leaq	(%rsi,%rcx,8), %rcx
	movq	(%rcx), %r14
	movq	$0, (%rcx)
	movl	176(%rdx), %ecx
	cmpl	$-1, %ecx
	je	.L43
.L12:
	addl	$1, %eax
	cmpl	168(%rdx), %eax
	movl	%eax, 172(%rdx)
	je	.L44
.L13:
	cmpl	%eax, %ecx
	jne	.L14
	movl	$-1, 172(%rdx)
	movl	$0, 176(%rdx)
.L14:
	movl	216(%r14), %eax
	testl	%eax, %eax
	je	.L15
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	movl	176(%rdi), %eax
	cmpl	$-1, %eax
	je	.L10
	movl	172(%rdi), %edx
	cmpl	$-1, %edx
	je	.L45
.L16:
	movslq	%eax, %rsi
	addl	$1, %eax
	cmpl	168(%rdi), %eax
	movq	160(%rdi), %rcx
	movq	%r14, (%rcx,%rsi,8)
	movl	%eax, 176(%rdi)
	je	.L46
	cmpl	%eax, %edx
	je	.L47
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
.L10:
	addq	$24, %rdi
	call	pthread_mutex_unlock
	jmp	.L7
.L11:
	movl	216, %eax
	ud2
	.p2align 4,,10
	.p2align 3
.L43:
	movl	%eax, 176(%rdx)
	movl	%eax, %ecx
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L44:
	movl	$0, 172(%rdx)
	xorl	%eax, %eax
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L46:
	xorl	%eax, %eax
	movl	$0, 176(%rdi)
	cmpl	%eax, %edx
	jne	.L8
.L47:
	movl	$-1, 176(%rdi)
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L45:
	movl	$0, 172(%rdi)
	xorl	%edx, %edx
	jmp	.L16
.L37:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	xorl	%eax, %eax
	ret
.L15:
	.cfi_def_cfa_offset 64
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	movl	4(%r14), %edx
	xorl	%eax, %eax
	movl	%r12d, %ecx
	movl	$.LC1, %esi
	call	core_log
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	movl	176(%rdi), %eax
	cmpl	$-1, %eax
	je	.L19
	movl	172(%rdi), %edx
	cmpl	$-1, %edx
	je	.L48
.L20:
	movslq	%eax, %rsi
	addl	$1, %eax
	cmpl	168(%rdi), %eax
	movq	160(%rdi), %rcx
	movq	%r14, (%rcx,%rsi,8)
	movl	%eax, 176(%rdi)
	je	.L49
.L21:
	cmpl	%eax, %edx
	je	.L50
.L38:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
.L19:
	movl	4(%r14), %edx
	movl	%r13d, %ecx
	movl	$.LC2, %esi
	xorl	%eax, %eax
	movl	%r12d, 212(%r14)
	call	core_log
	leaq	112(%r14), %rdi
	call	pthread_cond_signal
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_unlock
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	jmp	.L6
.L49:
	movl	$0, 176(%rdi)
	xorl	%eax, %eax
	jmp	.L21
.L48:
	movl	$0, 172(%rdi)
	xorl	%edx, %edx
	jmp	.L20
.L50:
	movl	$-1, 176(%rdi)
	jmp	.L38
	.cfi_endproc
.LFE39:
	.size	less_frequent_work_stealing, .-less_frequent_work_stealing
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.rodata.str1.8
	.align 8
.LC4:
	.string	"Balancer: Do noting, because the ready thread[%d] has already been binded to this core\n"
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	more_frequent_work_stealing
	.type	more_frequent_work_stealing, @function
more_frequent_work_stealing:
.LFB40:
	.cfi_startproc
	movl	num_cores(%rip), %esi
	testl	%esi, %esi
	jle	.L87
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	xorl	%r12d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	xorl	%ebx, %ebx
	jmp	.L81
	.p2align 4,,10
	.p2align 3
.L53:
	addl	$1, %r12d
	addq	$240, %rbx
	cmpl	%r12d, num_cores(%rip)
	jle	.L91
.L81:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_trylock
	testl	%eax, %eax
	jne	.L53
	movq	carr(%rip), %rax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	pushq	176(%rax,%rbx)
	.cfi_def_cfa_offset 64
	pushq	168(%rax,%rbx)
	.cfi_def_cfa_offset 72
	pushq	160(%rax,%rbx)
	.cfi_def_cfa_offset 80
	xorl	%eax, %eax
	call	get_list_count
	addq	$32, %rsp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	jne	.L73
	movq	carr(%rip), %rax
	leaq	(%rax,%rbx), %rdi
	movl	232(%rdi), %ecx
	testl	%ecx, %ecx
	js	.L92
.L55:
	addq	$24, %rdi
	call	pthread_mutex_unlock
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L73:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	jmp	.L55
	.p2align 4,,10
	.p2align 3
.L91:
	popq	%rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_restore 13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_restore 14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L92:
	.cfi_restore_state
	movl	num_cores(%rip), %edx
	testl	%edx, %edx
	jle	.L55
	xorl	%ebp, %ebp
	xorl	%r13d, %r13d
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L56:
	addl	$1, %r13d
	addq	$240, %rbp
	cmpl	%r13d, num_cores(%rip)
	jle	.L73
	movq	carr(%rip), %rax
.L74:
	leaq	24(%rax,%rbp), %rdi
	call	pthread_mutex_trylock
	testl	%eax, %eax
	jne	.L56
	movq	carr(%rip), %rax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	pushq	176(%rax,%rbp)
	.cfi_def_cfa_offset 64
	pushq	168(%rax,%rbp)
	.cfi_def_cfa_offset 72
	pushq	160(%rax,%rbp)
	.cfi_def_cfa_offset 80
	xorl	%eax, %eax
	call	get_list_count
	addq	$32, %rsp
	.cfi_def_cfa_offset 48
	cmpl	$1, %eax
	jle	.L57
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
.L58:
	movl	172(%rdi), %eax
	cmpl	$-1, %eax
	je	.L61
	movq	160(%rdi), %rcx
	movslq	%eax, %rdx
	leaq	(%rcx,%rdx,8), %rdx
	movq	(%rdx), %r14
	movq	$0, (%rdx)
	movl	176(%rdi), %edx
	cmpl	$-1, %edx
	je	.L93
.L62:
	addl	$1, %eax
	cmpl	168(%rdi), %eax
	movl	%eax, 172(%rdi)
	je	.L94
.L63:
	cmpl	%eax, %edx
	jne	.L64
	movl	$-1, 172(%rdi)
	movl	$0, 176(%rdi)
.L64:
	movl	216(%r14), %eax
	movl	4(%r14), %edx
	movq	%rbp, %rdi
	testl	%eax, %eax
	je	.L65
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	movl	%r12d, %ecx
	movl	$.LC4, %esi
	call	core_log
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	movl	176(%rdi), %eax
	cmpl	$-1, %eax
	je	.L60
	movl	172(%rdi), %edx
	cmpl	$-1, %edx
	je	.L95
.L66:
	movslq	%eax, %rsi
	addl	$1, %eax
	cmpl	168(%rdi), %eax
	movq	160(%rdi), %rcx
	movq	%r14, (%rcx,%rsi,8)
	movl	%eax, 176(%rdi)
	je	.L96
	cmpl	%eax, %edx
	je	.L97
.L89:
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
.L60:
	addq	$24, %rdi
	call	pthread_mutex_unlock
	jmp	.L56
.L61:
	movl	216, %eax
	ud2
	.p2align 4,,10
	.p2align 3
.L57:
	movq	carr(%rip), %rax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	pushq	176(%rax,%rbp)
	.cfi_def_cfa_offset 64
	pushq	168(%rax,%rbp)
	.cfi_def_cfa_offset 72
	pushq	160(%rax,%rbp)
	.cfi_def_cfa_offset 80
	xorl	%eax, %eax
	call	get_list_count
	addq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	testl	%eax, %eax
	jle	.L60
	cmpl	$-1, 232(%rdi)
	jne	.L58
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L93:
	movl	%eax, 176(%rdi)
	movl	%eax, %edx
	jmp	.L62
	.p2align 4,,10
	.p2align 3
.L94:
	movl	$0, 172(%rdi)
	xorl	%eax, %eax
	jmp	.L63
	.p2align 4,,10
	.p2align 3
.L96:
	xorl	%eax, %eax
	movl	$0, 176(%rdi)
	cmpl	%eax, %edx
	jne	.L89
.L97:
	movl	$-1, 176(%rdi)
	jmp	.L89
	.p2align 4,,10
	.p2align 3
.L95:
	movl	$0, 172(%rdi)
	xorl	%edx, %edx
	jmp	.L66
.L87:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	xorl	%eax, %eax
	ret
.L65:
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	.cfi_offset 6, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	.cfi_offset 14, -16
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	movl	%r12d, %ecx
	movl	$.LC1, %esi
	call	core_log
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	movl	176(%rdi), %eax
	cmpl	$-1, %eax
	je	.L69
	movl	172(%rdi), %edx
	cmpl	$-1, %edx
	je	.L98
.L70:
	movslq	%eax, %rsi
	addl	$1, %eax
	cmpl	168(%rdi), %eax
	movq	160(%rdi), %rcx
	movq	%r14, (%rcx,%rsi,8)
	movl	%eax, 176(%rdi)
	je	.L99
.L71:
	cmpl	%eax, %edx
	je	.L100
.L88:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
.L69:
	movl	4(%r14), %edx
	movl	%r13d, %ecx
	movl	$.LC2, %esi
	xorl	%eax, %eax
	movl	%r12d, 212(%r14)
	call	core_log
	leaq	112(%r14), %rdi
	call	pthread_cond_signal
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_unlock
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	jmp	.L55
.L98:
	movl	$0, 172(%rdi)
	xorl	%edx, %edx
	jmp	.L70
.L99:
	movl	$0, 176(%rdi)
	xorl	%eax, %eax
	jmp	.L71
.L100:
	movl	$-1, 176(%rdi)
	jmp	.L88
	.cfi_endproc
.LFE40:
	.size	more_frequent_work_stealing, .-more_frequent_work_stealing
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.globl	MY_BALANCE
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC6:
	.string	"noop"
.LC7:
	.string	"more_frequent_work_stealing"
.LC8:
	.string	"less_frequent_work_stealing"
	.data
	.align 32
	.type	MY_BALANCE, @object
	.size	MY_BALANCE, 48
MY_BALANCE:
	.quad	.LC6
	.quad	noop
	.quad	.LC7
	.quad	more_frequent_work_stealing
	.quad	.LC8
	.quad	less_frequent_work_stealing
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
