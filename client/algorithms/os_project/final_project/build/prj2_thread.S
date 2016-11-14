	.file	"prj2_thread.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Generated random time should be shorter than 1000 sec"
	.align 8
.LC1:
	.string	"Generated random time should be longer than 10 msec"
	.align 8
.LC2:
	.string	"Maximum random time should be longer than minimum random time"
	.align 8
.LC3:
	.string	"%8ld: thread[%d] at core[%d] is starting with remain_usec=%d\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"%8ld: thread[%d] terminated\n"
	.section	.rodata.str1.8
	.align 8
.LC6:
	.string	"%8ld: thread[%d] with remain_usec=%d begins run#%d for up to %.1f msec\n"
	.align 8
.LC7:
	.string	"thread[%d] was preempted when in %d state, run_sid=%d"
	.align 8
.LC8:
	.string	"thread[%d] failed timedwait on run_cv, rv=%d"
	.align 8
.LC9:
	.string	"thread[%d] finished run not in running state!?!"
	.align 8
.LC11:
	.string	"%8ld: [CPU_Cache Effort] thread[%d] got hitting private cache of core bonus#%d\n"
	.align 8
.LC12:
	.string	"%8ld: thread[%d] with remain_usec=%d finished run#%d\n"
	.align 8
.LC13:
	.string	"%8ld: thread[%d] with remain_usec=%d is ready for run#%d\n"
	.align 8
.LC14:
	.string	"%8ld: thread[%d] enters block#%d for %.1f msec\n"
	.align 8
.LC15:
	.string	"thread[%d] finished block not in blocked state!?!"
	.align 8
.LC16:
	.string	"thread[%d] was preempted in block state!"
	.align 8
.LC17:
	.string	"thread[%d] failed timedwait on block_cv, rv=%d"
	.align 8
.LC18:
	.string	"%8ld: thread[%d] finished block#%d\n"
	.align 8
.LC19:
	.string	"Invalid thread[%d] state: %d!!"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB20:
	.text
.LHOTB20:
	.p2align 4,,15
	.globl	thread_execution
	.type	thread_execution, @function
thread_execution:
.LFB38:
	.cfi_startproc
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
	movq	%rdi, %r13
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movl	4(%rdi), %eax
	movl	max_time(%rip), %ebx
	movl	min_time(%rip), %ebp
	addl	$1, %eax
	imull	seed_multiplier(%rip), %eax
	cmpl	$999999, %ebx
	movl	%eax, 12(%rsp)
	jg	.L60
.L2:
	cmpl	$9, %ebp
	movslq	%ebp, %r12
	jle	.L61
.L4:
	cmpl	%ebx, %ebp
	jg	.L5
	subl	%ebp, %ebx
	movslq	%ebx, %rbp
.L6:
	leaq	12(%rsp), %rdi
	movq	$0, 16(%rsp)
	call	rand_r
	movslq	%eax, %rbx
	movabsq	$8589934597, %rdx
	movl	$simlock, %edi
	imulq	%rbp, %rbx
	movq	%rbx, %rax
	mulq	%rdx
	subq	%rdx, %rbx
	shrq	%rbx
	addq	%rbx, %rdx
	shrq	$30, %rdx
	addq	%rdx, %r12
	movq	16(%rsp), %rdx
	subq	zero_ts(%rip), %rdx
	imulq	$1000000, %r12, %r12
	movq	%r12, 24(%rsp)
	subq	zero_ts+8(%rip), %r12
	imulq	$1000000, %rdx, %rcx
	movabsq	$2361183241434822607, %rdx
	movq	%r12, %rax
	sarq	$63, %r12
	imulq	%rdx
	sarq	$7, %rdx
	subq	%r12, %rdx
	addq	%rcx, %rdx
	movl	%edx, 56(%r13)
	call	pthread_mutex_lock
	cmpl	$-1, 212(%r13)
	je	.L62
.L7:
	leaq	24(%r13), %r12
	movl	$simlock, %edi
	call	pthread_mutex_unlock
	xorl	%edi, %edi
	movq	%r12, %rsi
	call	clock_gettime
	movq	32(%r13), %rcx
	subq	sim_ts+8(%rip), %rcx
	movabsq	$2361183241434822607, %rdx
	movl	56(%r13), %r9d
	movl	212(%r13), %r8d
	xorl	%edi, %edi
	movl	$.LC3, %esi
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdx
	movq	24(%r13), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movl	4(%r13), %ecx
	addq	%rax, %rdx
	xorl	%eax, %eax
	movq	%rdx, 40(%r13)
	call	core_log
	movl	56(%r13), %edi
	movq	tick_ts(%rip), %rax
	movq	tick_ts+8(%rip), %rdx
	testl	%edi, %edi
	movq	%rax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	jle	.L38
	movq	zero_ts+8(%rip), %r14
	xorl	%ebp, %ebp
.L37:
	movslq	212(%r13), %rbx
	movq	%rbx, %rax
	salq	$8, %rbx
	salq	$4, %rax
	subq	%rax, %rbx
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	addq	$24, %rdi
	call	pthread_mutex_lock
	movl	208(%r13), %ecx
	cmpl	$3, %ecx
	je	.L10
	cmpl	$4, %ecx
	je	.L11
	cmpl	$2, %ecx
	je	.L63
	movl	4(%r13), %edx
	movl	$.LC19, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
	.p2align 4,,10
	.p2align 3
.L10:
	movq	24(%rsp), %rsi
	movabsq	$2361183241434822607, %rdx
	movq	16(%rsp), %rdi
	addl	$1, %ebp
	movq	%rsi, %rcx
	subq	%r14, %rcx
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdx
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movq	%rdi, %rcx
	subq	zero_ts(%rip), %rcx
	imulq	$1000000, %rcx, %rcx
	leaq	(%rdx,%rcx), %rax
	subl	56(%r13), %eax
	testl	%eax, %eax
	jle	.L14
	imull	$1000, %eax, %eax
	cltq
	subq	%rax, %rsi
	testq	%rsi, %rsi
	movq	%rsi, 24(%rsp)
	js	.L64
.L14:
	xorl	%edi, %edi
	movq	%r12, %rsi
	call	clock_gettime
	movq	24(%rsp), %rcx
	movabsq	$2361183241434822607, %rsi
	movq	32(%r13), %rdi
	pxor	%xmm0, %xmm0
	subq	sim_ts+8(%rip), %rdi
	movl	56(%r13), %r8d
	movl	%ebp, %r9d
	subq	%r14, %rcx
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rsi
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movq	16(%rsp), %rcx
	subq	zero_ts(%rip), %rcx
	imulq	$1000000, %rcx, %rcx
	leaq	(%rdx,%rcx), %rax
	movl	4(%r13), %ecx
	cvtsi2sdq	%rax, %xmm0
	movq	%rdi, %rax
	imulq	%rsi
	movq	24(%r13), %rax
	subq	sim_ts(%rip), %rax
	sarq	$63, %rdi
	movl	$.LC6, %esi
	sarq	$7, %rdx
	subq	%rdi, %rdx
	movslq	212(%r13), %rdi
	imulq	$1000000, %rax, %rax
	divsd	.LC5(%rip), %xmm0
	addq	%rax, %rdx
	movq	%rdi, %rax
	salq	$4, %rax
	salq	$8, %rdi
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	movl	$1, %eax
	call	core_log
	movq	24(%rsp), %rax
	addq	32(%r13), %rax
	movq	16(%rsp), %rdx
	addq	24(%r13), %rdx
	cmpq	$999999999, %rax
	movq	%rax, 24(%rsp)
	movq	%rdx, 16(%rsp)
	jg	.L65
.L16:
	movq	%rbx, %rdi
	addq	carr(%rip), %rdi
	movl	4(%r13), %eax
	leaq	16(%rsp), %rdx
	leaq	24(%rdi), %rsi
	movl	%eax, 232(%rdi)
	addq	$64, %rdi
	call	pthread_cond_timedwait
	movl	208(%r13), %ecx
	cmpl	$2, %ecx
	je	.L66
	cmpl	$3, %ecx
	je	.L67
.L20:
	testl	%eax, %eax
	je	.L68
	cmpl	$110, %eax
	jne	.L69
	cmpl	$3, %ecx
	jne	.L70
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rdi
	movabsq	$2361183241434822607, %rdx
	movq	16(%rsp), %rsi
	movl	56(%r13), %r11d
	movq	%rdi, %rcx
	subq	32(%r13), %rcx
	movq	%rsi, %r9
	movq	%rdi, %r8
	subq	224(%r13), %r9
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdx
	movq	16(%rsp), %rax
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movq	%rsi, %rcx
	subq	24(%r13), %rcx
	movq	%rax, 24(%r13)
	imulq	$1000000, %rcx, %rcx
	addq	%rdx, %rcx
	movq	24(%rsp), %rdx
	subl	%ecx, %r11d
	subq	232(%r13), %r8
	movl	%r11d, 56(%r13)
	movq	%rdx, 32(%r13)
	js	.L71
.L24:
	subq	affinity_ts+8(%rip), %r8
	subq	affinity_ts(%rip), %r9
	movabsq	$2361183241434822607, %r15
	movq	%r8, %rax
	sarq	$63, %r8
	imulq	%r15
	imulq	$1000000, %r9, %r9
	sarq	$7, %rdx
	subq	%r8, %rdx
	addq	%rdx, %r9
	testq	%r9, %r9
	jle	.L39
	testl	%r11d, %r11d
	jle	.L39
	pxor	%xmm0, %xmm0
	cvtsi2sd	%ecx, %xmm0
	movl	4(%r13), %ecx
	mulsd	.LC10(%rip), %xmm0
	cvttsd2si	%xmm0, %r8d
	cmpl	%r8d, %r11d
	cmovle	%r11d, %r8d
	subq	sim_ts+8(%rip), %rdi
	subq	sim_ts(%rip), %rsi
	subl	%r8d, %r11d
	movl	%r11d, 56(%r13)
	movq	%rdi, %rax
	sarq	$63, %rdi
	imulq	%r15
	imulq	$1000000, %rsi, %rsi
	sarq	$7, %rdx
	subq	%rdi, %rdx
	movslq	212(%r13), %rdi
	addq	%rsi, %rdx
	movl	$.LC11, %esi
	movq	%rdi, %rax
	salq	$8, %rdi
	salq	$4, %rax
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	call	core_log
	movl	56(%r13), %r8d
	movq	24(%rsp), %rdi
	movq	16(%rsp), %rsi
.L25:
	subq	sim_ts+8(%rip), %rdi
	movabsq	$2361183241434822607, %rdx
	subq	sim_ts(%rip), %rsi
	movl	4(%r13), %ecx
	movl	%ebp, %r9d
	movq	%rdi, %rax
	sarq	$63, %rdi
	imulq	%rdx
	imulq	$1000000, %rsi, %rsi
	sarq	$7, %rdx
	subq	%rdi, %rdx
	movslq	212(%r13), %rdi
	addq	%rsi, %rdx
	movl	$.LC12, %esi
	movq	%rdi, %rax
	salq	$8, %rdi
	salq	$4, %rax
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	call	core_log
	movl	56(%r13), %esi
	testl	%esi, %esi
	jle	.L26
	movslq	212(%r13), %rax
	leaq	12(%rsp), %rdi
	movl	$4, 208(%r13)
	movq	$0, 16(%rsp)
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	addq	carr(%rip), %rax
	movl	4(%r13), %edx
	movl	$-1, 232(%rax)
	movl	%edx, 236(%rax)
	call	rand_r
	cltq
	movabsq	$8589934597, %rdx
	leaq	(%rax,%rax,4), %rax
	leaq	(%rax,%rax,4), %rcx
	salq	$2, %rcx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	movq	carr(%rip), %rcx
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$30, %rax
	addq	$200, %rax
	imulq	$1000000, %rax, %rax
	movq	%rax, 24(%rsp)
	movslq	212(%r13), %rax
.L27:
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	leaq	112(%rcx,%rax), %rdi
	call	pthread_cond_broadcast
	movq	carr(%rip), %rdx
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L63:
	movq	%r12, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	32(%r13), %rsi
	subq	sim_ts+8(%rip), %rsi
	movabsq	$2361183241434822607, %rdx
	movslq	212(%r13), %rdi
	movl	4(%r13), %ecx
	movl	%ebp, %r9d
	movl	56(%r13), %r8d
	movq	%rsi, %rax
	sarq	$63, %rsi
	imulq	%rdx
	movq	24(%r13), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rsi, %rdx
	movl	$.LC13, %esi
	addq	%rax, %rdx
	movq	%rdi, %rax
	salq	$8, %rdi
	salq	$4, %rax
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	call	core_log
	movq	%rbx, %rsi
	addq	carr(%rip), %rsi
	leaq	112(%r13), %rdi
	addq	$24, %rsi
	call	pthread_cond_wait
	movq	carr(%rip), %rdx
.L19:
	leaq	24(%rdx,%rbx), %rdi
	call	pthread_mutex_unlock
	movl	56(%r13), %eax
	testl	%eax, %eax
	jg	.L37
.L38:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rcx
	subq	sim_ts+8(%rip), %rcx
	movabsq	$2361183241434822607, %rdx
	movl	$.LC4, %esi
	xorl	%edi, %edi
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdx
	movq	16(%rsp), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movl	4(%r13), %ecx
	addq	%rax, %rdx
	xorl	%eax, %eax
	movq	%rdx, 48(%r13)
	call	core_log
	movslq	212(%r13), %rax
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	addq	carr(%rip), %rax
	movq	%rax, %rdi
	addq	$24, %rdi
	call	pthread_mutex_lock
	movslq	212(%r13), %rax
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	addq	carr(%rip), %rax
	movq	%rax, %rdi
	addq	$112, %rdi
	call	pthread_cond_signal
	movslq	212(%r13), %rax
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	addq	carr(%rip), %rax
	movq	%rax, %rdi
	addq	$24, %rdi
	call	pthread_mutex_unlock
	xorl	%eax, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
	.p2align 4,,10
	.p2align 3
.L11:
	.cfi_restore_state
	xorl	%edi, %edi
	movq	%r12, %rsi
	call	clock_gettime
	movq	24(%rsp), %rcx
	subq	zero_ts+8(%rip), %rcx
	movabsq	$2361183241434822607, %rsi
	pxor	%xmm0, %xmm0
	movq	32(%r13), %rdi
	subq	sim_ts+8(%rip), %rdi
	movl	%ebp, %r8d
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rsi
	sarq	$7, %rdx
	subq	%rcx, %rdx
	movq	16(%rsp), %rcx
	subq	zero_ts(%rip), %rcx
	imulq	$1000000, %rcx, %rcx
	leaq	(%rdx,%rcx), %rax
	movl	4(%r13), %ecx
	cvtsi2sdq	%rax, %xmm0
	movq	%rdi, %rax
	imulq	%rsi
	movq	24(%r13), %rax
	subq	sim_ts(%rip), %rax
	sarq	$63, %rdi
	movl	$.LC14, %esi
	sarq	$7, %rdx
	subq	%rdi, %rdx
	movslq	212(%r13), %rdi
	imulq	$1000000, %rax, %rax
	divsd	.LC5(%rip), %xmm0
	addq	%rax, %rdx
	movq	%rdi, %rax
	salq	$4, %rax
	salq	$8, %rdi
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	movl	$1, %eax
	call	core_log
	movq	24(%rsp), %rax
	addq	32(%r13), %rax
	movq	16(%rsp), %rdx
	addq	24(%r13), %rdx
	cmpq	$999999999, %rax
	movq	%rax, 24(%rsp)
	movq	%rdx, 16(%rsp)
	jg	.L72
.L28:
	movq	%rbx, %rsi
	addq	carr(%rip), %rsi
	leaq	64(%r13), %r15
	leaq	16(%rsp), %rdx
	movq	%r15, %rdi
	addq	$24, %rsi
	call	pthread_cond_timedwait
	cmpl	$4, 208(%r13)
	jne	.L73
	testl	%eax, %eax
	je	.L74
	cmpl	$110, %eax
	jne	.L75
	xorl	%edi, %edi
	movq	%r12, %rsi
	call	clock_gettime
	movq	32(%r13), %rsi
	subq	sim_ts+8(%rip), %rsi
	movabsq	$2361183241434822607, %rdx
	movslq	212(%r13), %rdi
	movl	4(%r13), %ecx
	movl	%ebp, %r8d
	movq	%rsi, %rax
	sarq	$63, %rsi
	imulq	%rdx
	movq	24(%r13), %rax
	subq	sim_ts(%rip), %rax
	imulq	$1000000, %rax, %rax
	sarq	$7, %rdx
	subq	%rsi, %rdx
	movl	$.LC18, %esi
	addq	%rax, %rdx
	movq	%rdi, %rax
	salq	$8, %rdi
	salq	$4, %rax
	subq	%rax, %rdi
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	call	core_log
	movslq	212(%r13), %rax
	movq	carr(%rip), %rsi
	movq	%rax, %rdx
	salq	$8, %rax
	salq	$4, %rdx
	subq	%rdx, %rax
	leaq	(%rsi,%rax), %rcx
	movq	%rax, %rdx
	movl	224(%rcx), %eax
	cmpl	$-1, %eax
	je	.L32
	movl	220(%rcx), %esi
	cmpl	$-1, %esi
	je	.L76
.L33:
	movslq	%eax, %r8
	addl	$1, %eax
	cmpl	216(%rcx), %eax
	movq	208(%rcx), %rdi
	movq	%r13, (%rdi,%r8,8)
	movl	%eax, 224(%rcx)
	je	.L77
	cmpl	%eax, %esi
	je	.L78
.L56:
	movq	carr(%rip), %rsi
.L32:
	movl	unblock_signal(%rip), %ecx
	testl	%ecx, %ecx
	je	.L36
	leaq	112(%rsi,%rdx), %rdi
	testq	%rdi, %rdi
	je	.L36
	call	pthread_cond_broadcast
	movq	carr(%rip), %rsi
.L36:
	leaq	24(%rsi,%rbx), %rsi
	movq	%r15, %rdi
	call	pthread_cond_wait
	leaq	12(%rsp), %rdi
	movq	$0, 16(%rsp)
	call	rand_r
	movslq	%eax, %rcx
	movabsq	$8589934597, %rdx
	imulq	$500, %rcx, %rcx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	movq	carr(%rip), %rdx
	shrq	$30, %rax
	addq	$300, %rax
	imulq	$1000000, %rax, %rax
	movq	%rax, 24(%rsp)
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L72:
	addq	$1, %rdx
	subq	$1000000000, %rax
	movq	%rdx, 16(%rsp)
	movq	%rax, 24(%rsp)
	jmp	.L28
	.p2align 4,,10
	.p2align 3
.L65:
	addq	$1, %rdx
	subq	$1000000000, %rax
	movq	%rdx, 16(%rsp)
	movq	%rax, 24(%rsp)
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L5:
	movl	$.LC2, %edi
	xorl	%eax, %eax
	xorl	%ebp, %ebp
	call	warnx
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L26:
	movslq	212(%r13), %rdx
	movq	carr(%rip), %rcx
	movl	$0, 56(%r13)
	movl	$1, 208(%r13)
	movq	%rdx, %rsi
	movq	%rdx, %rax
	salq	$8, %rdx
	salq	$4, %rsi
	subq	%rsi, %rdx
	addq	%rcx, %rdx
	movl	$-1, 236(%rdx)
	movl	$-1, 232(%rdx)
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L61:
	movl	$.LC1, %edi
	xorl	%eax, %eax
	movl	$10, %r12d
	call	warnx
	movl	$10, %ebp
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L60:
	movl	$.LC0, %edi
	xorl	%eax, %eax
	movl	$999999, %ebx
	call	warnx
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L66:
	movq	24(%rsp), %rax
	subq	32(%r13), %rax
	movq	16(%rsp), %rcx
	subq	24(%r13), %rcx
	movq	carr(%rip), %rdx
	testq	%rax, %rax
	movq	%rax, 24(%rsp)
	movq	%rcx, 16(%rsp)
	jns	.L19
.L57:
	subq	$1, %rcx
	addq	$1000000000, %rax
	movq	%rcx, 16(%rsp)
	movq	%rax, 24(%rsp)
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L77:
	xorl	%eax, %eax
	movl	$0, 224(%rcx)
	cmpl	%eax, %esi
	jne	.L56
.L78:
	movl	$-1, 224(%rcx)
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L76:
	movl	$0, 220(%rcx)
	xorl	%esi, %esi
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L67:
	movslq	212(%r13), %rsi
	movq	carr(%rip), %rdx
	movq	%rsi, %rdi
	salq	$8, %rsi
	salq	$4, %rdi
	subq	%rdi, %rsi
	cmpl	$-1, 232(%rdx,%rsi)
	jne	.L20
	movq	24(%rsp), %rax
	subq	32(%r13), %rax
	movq	16(%rsp), %rcx
	subq	24(%r13), %rcx
	testq	%rax, %rax
	movq	%rax, 24(%rsp)
	movq	%rcx, 16(%rsp)
	jns	.L19
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L64:
	subq	$1, %rdi
	addq	$1000000000, %rsi
	movq	%rdi, 16(%rsp)
	movq	%rsi, 24(%rsp)
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L71:
	subq	$1, %r9
	addq	$1000000000, %r8
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L39:
	movl	%r11d, %r8d
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L62:
	leaq	160(%r13), %rdi
	movl	$simlock, %esi
	call	pthread_cond_wait
	jmp	.L7
.L68:
	movslq	212(%r13), %rax
	movl	4(%r13), %edx
	movl	$.LC7, %esi
	movl	$1, %edi
	imulq	$240, %rax, %rax
	addq	carr(%rip), %rax
	movl	232(%rax), %r8d
	xorl	%eax, %eax
	call	errx
.L73:
	movl	4(%r13), %edx
	movl	$.LC15, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L75:
	movl	4(%r13), %edx
	movl	%eax, %ecx
	movl	$.LC17, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L70:
	movl	4(%r13), %edx
	movl	$.LC9, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L69:
	movl	4(%r13), %edx
	movl	%eax, %ecx
	movl	$.LC8, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L74:
	movl	4(%r13), %edx
	movl	$.LC16, %esi
	movl	$1, %edi
	call	errx
	.cfi_endproc
.LFE38:
	.size	thread_execution, .-thread_execution
	.section	.text.unlikely
.LCOLDE20:
	.text
.LHOTE20:
	.section	.rodata.str1.8
	.align 8
.LC21:
	.string	"malloc() failed for thread[%d]"
	.section	.rodata.str1.1
.LC22:
	.string	"clone() failed for thread[%d]"
	.section	.text.unlikely
.LCOLDB23:
	.text
.LHOTB23:
	.p2align 4,,15
	.globl	fork_thread
	.type	fork_thread, @function
fork_thread:
.LFB39:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movl	$1048576, %edi
	call	malloc
	testq	%rax, %rax
	movq	%rax, 8(%rbx)
	je	.L83
	addq	$1048576, %rax
	leaq	64(%rbx), %rdi
	xorl	%esi, %esi
	movq	%rax, 16(%rbx)
	call	pthread_cond_init
	leaq	112(%rbx), %rdi
	xorl	%esi, %esi
	call	pthread_cond_init
	leaq	160(%rbx), %rdi
	xorl	%esi, %esi
	call	pthread_cond_init
	movq	16(%rbx), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rcx
	movl	$273, %edx
	movl	$thread_execution, %edi
	call	clone
	cmpl	$-1, %eax
	movl	%eax, (%rbx)
	je	.L84
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L84:
	.cfi_restore_state
	movl	4(%rbx), %esi
	movl	$.LC22, %edi
	xorl	%eax, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	warn
	.p2align 4,,10
	.p2align 3
.L83:
	.cfi_restore_state
	movl	$0, (%rbx)
	movl	4(%rbx), %esi
	movl	$.LC21, %edi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	warn
	.cfi_endproc
.LFE39:
	.size	fork_thread, .-fork_thread
	.section	.text.unlikely
.LCOLDE23:
	.text
.LHOTE23:
	.section	.text.unlikely
.LCOLDB24:
	.text
.LHOTB24:
	.p2align 4,,15
	.globl	clear_thread
	.type	clear_thread, @function
clear_thread:
.LFB40:
	.cfi_startproc
	movl	(%rdi), %eax
	testl	%eax, %eax
	jne	.L89
	rep ret
	.p2align 4,,10
	.p2align 3
.L89:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	leaq	64(%rdi), %rdi
	call	pthread_cond_destroy
	leaq	112(%rbx), %rdi
	call	pthread_cond_destroy
	leaq	160(%rbx), %rdi
	call	pthread_cond_destroy
	movq	8(%rbx), %rdi
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	jmp	free
	.cfi_endproc
.LFE40:
	.size	clear_thread, .-clear_thread
	.section	.text.unlikely
.LCOLDE24:
	.text
.LHOTE24:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC5:
	.long	0
	.long	1083129856
	.align 8
.LC10:
	.long	858993459
	.long	1070805811
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
