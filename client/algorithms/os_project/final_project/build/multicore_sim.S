	.file	"multicore_sim.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"core simulation start\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"thread[%d] was blocked while thread[%d] is still running"
	.align 8
.LC2:
	.string	"thread[%d] to be preempted is in %d state"
	.align 8
.LC3:
	.string	"%8ld: scheduler preempts running thread[%d] with remain_usec=%d\n"
	.align 8
.LC4:
	.string	"%8ld: scheduler changes thread[%d] with remain_usec=%d to ready\n"
	.align 8
.LC5:
	.string	"scheduler is running with running thread[%d]!?!"
	.align 8
.LC6:
	.string	"thread[%d] was blocking but not handled!?!"
	.section	.rodata.str1.1
.LC7:
	.string	"%8ld: core[%d] is idling\n"
	.section	.rodata.str1.8
	.align 8
.LC8:
	.string	"%8ld: scheduler cannot find any thread to run: %d %d\n"
	.align 8
.LC9:
	.string	"scheduler selects thread[%d] not in ready state"
	.align 8
.LC10:
	.string	"%8ld: scheduler selects thread[%d] with remain_usec=%d to run\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB11:
	.text
.LHOTB11:
	.p2align 4,,15
	.globl	core_execution
	.type	core_execution, @function
core_execution:
.LFB38:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	leaq	24(%r15), %r13
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	xorl	%eax, %eax
	movl	$.LC0, %esi
	leaq	64(%r15), %rbx
	xorl	%r12d, %r12d
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	call	core_log
	movq	%r13, %rdi
	call	pthread_mutex_lock
	movl	$-1, %edx
	movq	%rbx, 8(%rsp)
	leaq	112(%r15), %rbx
	movslq	%edx, %rax
	movl	$-1, 232(%r15)
	movl	$-1, 236(%r15)
	cmpl	$-1, %eax
	movq	%rbx, (%rsp)
	je	.L2
.L124:
	cmpl	$-1, %edx
	jne	.L110
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	movl	200(%r15), %edx
	addq	tarr(%rip), %rax
	cmpl	$-1, %edx
	je	.L5
	movl	196(%r15), %ecx
	cmpl	$-1, %ecx
	je	.L111
.L6:
	movq	184(%r15), %rsi
	movslq	%edx, %rdi
	movq	%rax, (%rsi,%rdi,8)
	leal	1(%rdx), %eax
	cmpl	192(%r15), %eax
	movl	%eax, 200(%r15)
	je	.L112
	cmpl	%eax, %ecx
	je	.L113
.L5:
	movl	$-1, 236(%r15)
.L9:
	movl	220(%r15), %eax
	leaq	16(%rsp), %rbx
	testl	%eax, %eax
	js	.L44
.L16:
	movabsq	$2361183241434822607, %rbp
	.p2align 4,,10
	.p2align 3
.L42:
	movq	208(%r15), %rcx
	movslq	%eax, %rdx
	leaq	(%rcx,%rdx,8), %rdx
	movq	(%rdx), %r14
	movq	$0, (%rdx)
	movl	224(%r15), %edx
	cmpl	$-1, %edx
	je	.L114
.L19:
	addl	$1, %eax
	cmpl	216(%r15), %eax
	movl	%eax, 220(%r15)
	je	.L115
.L20:
	cmpl	%eax, %edx
	jne	.L21
	movl	$-1, 220(%r15)
	movl	$0, 224(%r15)
.L21:
	xorl	%edi, %edi
	movq	%rbx, %rsi
	call	clock_gettime
	movq	24(%rsp), %rsi
	subq	sim_ts+8(%rip), %rsi
	movq	%r15, %rdi
	movq	16(%rsp), %rax
	movq	24(%rsp), %rdx
	movl	56(%r14), %r8d
	movl	4(%r14), %ecx
	movq	%rax, 24(%r14)
	movq	%rsi, %rax
	movq	%rdx, 32(%r14)
	imulq	%rbp
	movq	16(%rsp), %rax
	subq	sim_ts(%rip), %rax
	sarq	$63, %rsi
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rsi, %rdx
	movl	$.LC4, %esi
	addq	%rax, %rdx
	xorl	%eax, %eax
	call	core_log
	movl	196(%r15), %r10d
	movl	$2, 208(%r14)
	movl	4(%r14), %r8d
	cmpl	$-1, %r10d
	je	.L22
	movl	192(%r15), %edi
	cmpl	$0, %edi
	jle	.L23
	movq	184(%r15), %rsi
	xorl	%eax, %eax
	movq	%rsi, %rdx
	.p2align 4,,10
	.p2align 3
.L26:
	movq	(%rdx), %rcx
	movq	%rdx, %r9
	testq	%rcx, %rcx
	je	.L24
	cmpl	4(%rcx), %r8d
	je	.L25
.L24:
	addl	$1, %eax
	addq	$8, %rdx
	cmpl	%edi, %eax
	jne	.L26
.L22:
	movl	176(%r15), %eax
	cmpl	$-1, %eax
	je	.L38
	movl	172(%r15), %edx
	cmpl	$-1, %edx
	je	.L116
.L39:
	movslq	%eax, %rsi
	addl	$1, %eax
	cmpl	168(%r15), %eax
	movq	160(%r15), %rcx
	movq	%r14, (%rcx,%rsi,8)
	movl	%eax, 176(%r15)
	je	.L117
	cmpl	%eax, %edx
	je	.L118
.L38:
	leaq	64(%r14), %rdi
	call	pthread_cond_signal
	movl	220(%r15), %eax
	testl	%eax, %eax
	jns	.L42
	movl	232(%r15), %edx
	cmpl	$-1, %edx
	jne	.L119
.L102:
	movl	236(%r15), %edx
	cmpl	$-1, %edx
	jne	.L120
.L44:
	cmpl	$-1, 172(%r15)
	je	.L121
.L45:
	testq	%r12, %r12
	je	.L46
	cmpl	$3, 208(%r12)
	je	.L47
.L46:
	movq	%r15, %rdi
	call	*sched_func(%rip)
	xorl	%edi, %edi
	movl	%eax, %ebp
	movq	%rbx, %rsi
	call	clock_gettime
	testl	%ebp, %ebp
	js	.L122
	movslq	%ebp, %rax
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	addq	tarr(%rip), %rax
	cmpl	$2, 208(%rax)
	movq	%rax, %r12
	jne	.L123
	movq	24(%rsp), %rcx
	subq	sim_ts+8(%rip), %rcx
	movabsq	$2361183241434822607, %rdx
	movl	56(%r12), %r8d
	movl	$.LC10, %esi
	movq	%r15, %rdi
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdx
	movq	16(%rsp), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movl	%ebp, %ecx
	addq	%rax, %rdx
	xorl	%eax, %eax
	call	core_log
	movl	172(%r15), %r10d
	movl	$3, 208(%r12)
	movl	4(%r12), %r8d
	cmpl	$-1, %r10d
	je	.L50
	movl	168(%r15), %edi
	cmpl	$0, %edi
	jle	.L51
	movq	160(%r15), %rsi
	xorl	%eax, %eax
	movq	%rsi, %rdx
	.p2align 4,,10
	.p2align 3
.L54:
	movq	(%rdx), %rcx
	testq	%rcx, %rcx
	je	.L52
	cmpl	4(%rcx), %r8d
	je	.L53
.L52:
	addl	$1, %eax
	addq	$8, %rdx
	cmpl	%edi, %eax
	jne	.L54
.L50:
	leaq	112(%r12), %rdi
	call	pthread_cond_broadcast
.L47:
	movq	24(%rsp), %rax
	addq	tick_ts+8(%rip), %rax
	movq	16(%rsp), %rdx
	addq	tick_ts(%rip), %rdx
	cmpq	$999999999, %rax
	movq	%rax, 24(%rsp)
	movq	%rdx, 16(%rsp)
	jle	.L66
	addq	$1, %rdx
	subq	$1000000000, %rax
	movq	%rdx, 16(%rsp)
	movq	%rax, 24(%rsp)
.L66:
	movq	(%rsp), %rdi
	movq	%rbx, %rdx
	movq	%r13, %rsi
	call	pthread_cond_timedwait
	movl	is_terminated(%rip), %eax
	testl	%eax, %eax
	jne	.L67
	movslq	236(%r15), %rax
	movl	232(%r15), %edx
	cmpl	$-1, %eax
	jne	.L124
.L2:
	cmpl	$-1, %edx
	je	.L9
	movslq	%edx, %rax
	movq	%rax, %rcx
	salq	$8, %rax
	salq	$4, %rcx
	movq	%rax, %rbp
	subq	%rcx, %rbp
	addq	tarr(%rip), %rbp
	movl	208(%rbp), %ecx
	cmpl	$3, %ecx
	jne	.L125
	leaq	16(%rsp), %rbx
	xorl	%edi, %edi
	movq	%rbx, %rsi
	call	clock_gettime
	movq	24(%rsp), %r9
	movq	16(%rsp), %rsi
	movabsq	$2361183241434822607, %rdi
	movl	56(%rbp), %r8d
	movq	%r9, %rcx
	subq	32(%rbp), %rcx
	subq	sim_ts+8(%rip), %r9
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdi
	movq	%rsi, %rax
	subq	24(%rbp), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movl	232(%r15), %ecx
	addq	%rdx, %rax
	movq	24(%rsp), %rdx
	subl	%eax, %r8d
	movq	16(%rsp), %rax
	movl	%r8d, 56(%rbp)
	movq	%rdx, 32(%rbp)
	movq	%rax, 24(%rbp)
	movq	%r9, %rax
	sarq	$63, %r9
	imulq	%rdi
	movq	%rsi, %rax
	subq	sim_ts(%rip), %rax
	movl	$.LC3, %esi
	movq	%r15, %rdi
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%r9, %rdx
	addq	%rax, %rdx
	xorl	%eax, %eax
	call	core_log
	movl	176(%r15), %eax
	movl	$2, 208(%rbp)
	cmpl	$-1, %eax
	je	.L12
	movl	172(%r15), %edx
	cmpl	$-1, %edx
	je	.L126
.L13:
	movslq	%eax, %rsi
	addl	$1, %eax
	cmpl	168(%r15), %eax
	movq	160(%r15), %rcx
	movq	%rbp, (%rcx,%rsi,8)
	movl	%eax, 176(%r15)
	je	.L127
	cmpl	%eax, %edx
	je	.L128
.L12:
	movq	8(%rsp), %rdi
	movl	$-1, 232(%r15)
	call	pthread_cond_signal
	movl	220(%r15), %eax
	testl	%eax, %eax
	jns	.L16
	movl	232(%r15), %edx
	cmpl	$-1, %edx
	je	.L102
.L119:
	movl	$.LC5, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
	.p2align 4,,10
	.p2align 3
.L23:
	je	.L22
	movq	184(%r15), %rsi
	xorl	%eax, %eax
	movq	%rsi, %r9
.L25:
	movl	200(%r15), %r8d
	cmpl	$-1, %r8d
	je	.L129
	testl	%r8d, %r8d
	jne	.L31
	leal	-1(%rdi), %r8d
	movl	%r8d, 200(%r15)
.L30:
	cmpl	%r8d, %r10d
	je	.L130
.L32:
	cmpl	%r8d, %eax
	jne	.L36
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L131:
	movslq	%edx, %rcx
	cltq
	salq	$3, %rcx
	cmpl	%r8d, %edx
	movq	(%rsi,%rcx), %rcx
	movq	%rcx, (%rsi,%rax,8)
	je	.L35
.L132:
	movq	184(%r15), %rsi
	movl	%edx, %eax
.L36:
	leal	1(%rax), %edx
	cmpl	%edi, %edx
	jne	.L131
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	cltq
	movq	(%rsi,%rcx), %rcx
	cmpl	%r8d, %edx
	movq	%rcx, (%rsi,%rax,8)
	jne	.L132
.L35:
	movq	184(%r15), %rax
	movslq	%edx, %rdx
	leaq	(%rax,%rdx,8), %r9
.L33:
	movq	$0, (%r9)
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L31:
	subl	$1, %r8d
	cmpl	%r8d, %r10d
	movl	%r8d, 200(%r15)
	jne	.L32
.L130:
	movl	$-1, 196(%r15)
	movl	$0, 200(%r15)
	xorl	%r8d, %r8d
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L117:
	xorl	%eax, %eax
	movl	$0, 176(%r15)
	cmpl	%eax, %edx
	jne	.L38
.L118:
	movl	$-1, 176(%r15)
	jmp	.L38
	.p2align 4,,10
	.p2align 3
.L116:
	movl	$0, 172(%r15)
	xorl	%edx, %edx
	jmp	.L39
	.p2align 4,,10
	.p2align 3
.L114:
	movl	%eax, 224(%r15)
	movl	%eax, %edx
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L115:
	movl	$0, 220(%r15)
	xorl	%eax, %eax
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L129:
	leal	-1(%rdi), %edx
	leal	-1(%r10), %r8d
	testl	%r10d, %r10d
	cmove	%edx, %r8d
	movl	%r8d, 200(%r15)
	jmp	.L30
.L51:
	je	.L50
	movq	160(%r15), %rsi
	xorl	%eax, %eax
.L53:
	movl	176(%r15), %r9d
	cmpl	$-1, %r9d
	je	.L133
	testl	%r9d, %r9d
	jne	.L59
	leal	-1(%rdi), %r9d
	movl	%r9d, 176(%r15)
.L58:
	cmpl	%r9d, %r10d
	je	.L134
.L60:
	cmpl	%r9d, %eax
	jne	.L62
	jmp	.L135
	.p2align 4,,10
	.p2align 3
.L136:
	movslq	%ecx, %rdx
	salq	$3, %rdx
.L64:
	movq	(%rsi,%rdx), %r8
	cltq
	cmpl	%r9d, %ecx
	movq	%r8, (%rsi,%rax,8)
	movq	160(%r15), %rsi
	je	.L63
	movl	%ecx, %eax
.L62:
	leal	1(%rax), %ecx
	cmpl	%edi, %ecx
	jne	.L136
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	jmp	.L64
.L135:
	cltq
	leaq	0(,%rax,8), %rdx
.L63:
	movq	$0, (%rsi,%rdx)
	jmp	.L50
.L121:
	cmpl	$-1, 196(%r15)
	jne	.L45
	movq	%rbx, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rsi
	subq	sim_ts+8(%rip), %rsi
	movabsq	$2361183241434822607, %rdx
	movl	4(%r15), %ecx
	movq	%r15, %rdi
	movq	%rsi, %rax
	sarq	$63, %rsi
	imulq	%rdx
	movq	16(%rsp), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rsi, %rdx
	movl	$.LC7, %esi
	addq	%rax, %rdx
	xorl	%eax, %eax
	call	core_log
	jmp	.L45
.L59:
	subl	$1, %r9d
	cmpl	%r9d, %r10d
	movl	%r9d, 176(%r15)
	jne	.L60
.L134:
	movl	$-1, 172(%r15)
	movl	$0, 176(%r15)
	xorl	%r9d, %r9d
	jmp	.L60
.L112:
	xorl	%eax, %eax
	movl	$0, 200(%r15)
	cmpl	%eax, %ecx
	jne	.L5
.L113:
	movl	$-1, 200(%r15)
	jmp	.L5
.L111:
	movl	$0, 196(%r15)
	xorl	%ecx, %ecx
	jmp	.L6
.L133:
	leal	-1(%rdi), %r9d
	leal	-1(%r10), %edx
	testl	%r10d, %r10d
	cmovne	%edx, %r9d
	movl	%r9d, 176(%r15)
	jmp	.L58
.L122:
	movq	24(%rsp), %rsi
	subq	sim_ts+8(%rip), %rsi
	movabsq	$2361183241434822607, %rdx
	movl	172(%r15), %ecx
	movl	176(%r15), %r8d
	movq	%r15, %rdi
	xorl	%r12d, %r12d
	movq	%rsi, %rax
	sarq	$63, %rsi
	imulq	%rdx
	movq	16(%rsp), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rsi, %rdx
	movl	$.LC8, %esi
	addq	%rax, %rdx
	xorl	%eax, %eax
	call	core_log
	jmp	.L47
.L127:
	xorl	%eax, %eax
	movl	$0, 176(%r15)
	cmpl	%eax, %edx
	jne	.L12
.L128:
	movl	$-1, 176(%r15)
	jmp	.L12
.L126:
	movl	$0, 172(%r15)
	xorl	%edx, %edx
	jmp	.L13
.L67:
	movq	%r13, %rdi
	call	pthread_mutex_unlock
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L110:
	.cfi_restore_state
	movl	%edx, %ecx
	movl	$.LC1, %esi
	movl	%eax, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L125:
	movl	$.LC2, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L123:
	movl	%ebp, %edx
	movl	$.LC9, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L120:
	movl	$.LC6, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
	.cfi_endproc
.LFE38:
	.size	core_execution, .-core_execution
	.section	.text.unlikely
.LCOLDE11:
	.text
.LHOTE11:
	.section	.rodata.str1.8
	.align 8
.LC12:
	.string	"malloc() failed for thread[%d]"
	.align 8
.LC13:
	.string	"clone() failed for core thread[%d]"
	.section	.text.unlikely
.LCOLDB14:
	.text
.LHOTB14:
	.p2align 4,,15
	.globl	fork_core
	.type	fork_core, @function
fork_core:
.LFB39:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movl	$33554432, %edi
	call	malloc
	testq	%rax, %rax
	movq	%rax, 8(%rbx)
	je	.L141
	addq	$33554432, %rax
	leaq	24(%rbx), %rdi
	xorl	%esi, %esi
	movq	%rax, 16(%rbx)
	call	pthread_mutex_init
	leaq	64(%rbx), %rdi
	xorl	%esi, %esi
	call	pthread_cond_init
	leaq	112(%rbx), %rdi
	xorl	%esi, %esi
	call	pthread_cond_init
	movslq	global_waitingQ+8(%rip), %r12
	movl	$8, %esi
	movq	%r12, %rdi
	call	calloc
	movl	$8, %esi
	movq	%r12, %rdi
	movq	%rax, 160(%rbx)
	movl	%r12d, 168(%rbx)
	movl	$-1, 172(%rbx)
	movl	$0, 176(%rbx)
	call	calloc
	movl	$8, %esi
	movq	%r12, %rdi
	movq	%rax, 184(%rbx)
	movl	%r12d, 192(%rbx)
	movl	$-1, 196(%rbx)
	movl	$0, 200(%rbx)
	call	calloc
	movq	16(%rbx), %rsi
	movq	%rax, 208(%rbx)
	movq	%rbx, %rcx
	xorl	%eax, %eax
	movl	%r12d, 216(%rbx)
	movl	$-1, 220(%rbx)
	movl	$0, 224(%rbx)
	movl	$273, %edx
	movl	$core_execution, %edi
	call	clone
	cmpl	$-1, %eax
	movl	%eax, (%rbx)
	je	.L142
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L142:
	.cfi_restore_state
	movl	4(%rbx), %esi
	movl	$.LC13, %edi
	xorl	%eax, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	warn
	.p2align 4,,10
	.p2align 3
.L141:
	.cfi_restore_state
	movl	$0, (%rbx)
	movl	4(%rbx), %esi
	movl	$.LC12, %edi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	warn
	.cfi_endproc
.LFE39:
	.size	fork_core, .-fork_core
	.section	.text.unlikely
.LCOLDE14:
	.text
.LHOTE14:
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
