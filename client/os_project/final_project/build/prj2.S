	.file	"prj2.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"[Simulator global message ]"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.type	core_log.constprop.1, @function
core_log.constprop.1:
.LFB54:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %rbx
	subq	$208, %rsp
	.cfi_def_cfa_offset 224
	testb	%al, %al
	movq	%rdx, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	je	.L3
	movaps	%xmm0, 80(%rsp)
	movaps	%xmm1, 96(%rsp)
	movaps	%xmm2, 112(%rsp)
	movaps	%xmm3, 128(%rsp)
	movaps	%xmm4, 144(%rsp)
	movaps	%xmm5, 160(%rsp)
	movaps	%xmm6, 176(%rsp)
	movaps	%xmm7, 192(%rsp)
.L3:
	movl	$loglock, %edi
	call	pthread_mutex_lock
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	leaq	224(%rsp), %rax
	movq	stdout(%rip), %rdi
	leaq	8(%rsp), %rdx
	movq	%rbx, %rsi
	movl	$16, 8(%rsp)
	movl	$48, 12(%rsp)
	movq	%rax, 16(%rsp)
	leaq	32(%rsp), %rax
	movq	%rax, 24(%rsp)
	call	vfprintf
	movl	$loglock, %edi
	call	pthread_mutex_unlock
	addq	$208, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE54:
	.size	core_log.constprop.1, .-core_log.constprop.1
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"[core=%2d, run=%2d, block=%2d]"
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	core_log
	.type	core_log, @function
core_log:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbp
	movq	%rdi, %rbx
	subq	$216, %rsp
	.cfi_def_cfa_offset 240
	testb	%al, %al
	movq	%rdx, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	je	.L10
	movaps	%xmm0, 80(%rsp)
	movaps	%xmm1, 96(%rsp)
	movaps	%xmm2, 112(%rsp)
	movaps	%xmm3, 128(%rsp)
	movaps	%xmm4, 144(%rsp)
	movaps	%xmm5, 160(%rsp)
	movaps	%xmm6, 176(%rsp)
	movaps	%xmm7, 192(%rsp)
.L10:
	movl	$loglock, %edi
	call	pthread_mutex_lock
	testq	%rbx, %rbx
	je	.L8
	movl	236(%rbx), %ecx
	movl	232(%rbx), %edx
	movl	$.LC2, %edi
	movl	4(%rbx), %esi
	xorl	%eax, %eax
	call	printf
.L9:
	leaq	240(%rsp), %rax
	movq	stdout(%rip), %rdi
	leaq	8(%rsp), %rdx
	movq	%rbp, %rsi
	movl	$16, 8(%rsp)
	movl	$48, 12(%rsp)
	movq	%rax, 16(%rsp)
	leaq	32(%rsp), %rax
	movq	%rax, 24(%rsp)
	call	vfprintf
	movl	$loglock, %edi
	call	pthread_mutex_unlock
	addq	$216, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	.cfi_restore_state
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	jmp	.L9
	.cfi_endproc
.LFE51:
	.size	core_log, .-core_log
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.rodata.str1.8
	.align 8
.LC4:
	.string	"Scheduling function %s not found!"
	.align 8
.LC5:
	.string	"Balance function %s not found!"
	.align 8
.LC6:
	.string	"Core tid=%d created with cid=%d\n"
	.align 8
.LC7:
	.string	"Thread tid=%d created with sid=%d\n"
	.align 8
.LC8:
	.string	"All user created threads terminated.\n"
	.align 8
.LC9:
	.string	"Thread tid=%d exited with status %d\n"
	.align 8
.LC10:
	.string	"Simulator system thread tid=%d exited with status %d\n"
	.section	.text.unlikely
.LCOLDB11:
	.section	.text.startup,"ax",@progbits
.LHOTB11:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB50:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	cmpl	$4, %edi
	jle	.L66
	movq	8(%rsi), %rbx
	movl	%edi, %r12d
	movq	%rbx, %rdi
	call	strlen
	cltq
	leaq	-1(%rbx,%rax), %rax
	cmpb	$43, (%rax)
	je	.L67
.L14:
	movq	MY_SCHED(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L45
	movq	MY_SCHED+16(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L46
	movq	MY_SCHED+32(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L47
	movq	MY_SCHED+48(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L68
.L16:
	cmpq	$0, sched_func(%rip)
	je	.L69
	movq	16(%rbp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol
	movq	24(%rbp), %rbx
	movl	%eax, num_thrds(%rip)
	movq	%rbx, %rdi
	call	strlen
	cltq
	leaq	-1(%rbx,%rax), %rax
	cmpb	$43, (%rax)
	je	.L70
.L18:
	movq	MY_BALANCE(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L48
	movq	MY_BALANCE+16(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L49
	movq	MY_BALANCE+32(%rip), %rsi
	movq	%rbx, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L71
.L20:
	cmpq	$0, balance_func(%rip)
	je	.L72
	movq	32(%rbp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol
	cmpl	$5, %r12d
	movl	%eax, num_cores(%rip)
	movq	$0, threads_data_filename(%rip)
	je	.L44
	movq	40(%rbp), %rdi
	cmpl	$6, %r12d
	movq	%rdi, threads_data_filename(%rip)
	je	.L44
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol
	cmpl	$7, %r12d
	movl	%eax, min_time(%rip)
	je	.L44
	movq	48(%rbp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol
	movl	%eax, max_time(%rip)
.L44:
	xorl	%edi, %edi
	movl	$sim_ts, %esi
	call	clock_gettime
	xorl	%esi, %esi
	movl	$simlock, %edi
	call	pthread_mutex_init
	xorl	%esi, %esi
	movl	$sched_cv, %edi
	call	pthread_cond_init
	xorl	%esi, %esi
	movl	$run_cv, %edi
	call	pthread_cond_init
	movslq	num_thrds(%rip), %rdi
	movl	$8, %esi
	movq	%rdi, %rbx
	call	calloc
	movl	$simlock, %edi
	movl	%ebx, global_waitingQ+8(%rip)
	movq	%rax, global_waitingQ(%rip)
	movl	$-1, global_waitingQ+12(%rip)
	movl	$0, global_waitingQ+16(%rip)
	call	pthread_mutex_lock
	movslq	num_cores(%rip), %rdi
	movl	$240, %esi
	movq	%rdi, %rbx
	call	calloc
	testl	%ebx, %ebx
	movq	%rax, carr(%rip)
	jle	.L24
	movq	%rax, %rdi
	xorl	%ebp, %ebp
	xorl	%ebx, %ebx
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L73:
	movq	carr(%rip), %rdi
.L25:
	addq	%rbp, %rdi
	movl	%ebx, 4(%rdi)
	addl	$1, %ebx
	call	fork_core
	movq	%rbp, %rdi
	addq	carr(%rip), %rdi
	xorl	%eax, %eax
	movl	$.LC6, %esi
	addq	$240, %rbp
	movl	4(%rdi), %ecx
	movl	(%rdi), %edx
	call	core_log
	cmpl	%ebx, num_cores(%rip)
	jg	.L73
.L24:
	xorl	%eax, %eax
	call	fork_dispatcher
	movslq	num_thrds(%rip), %rdi
	movl	$240, %esi
	movq	%rdi, %rbx
	call	calloc
	testl	%ebx, %ebx
	movq	%rax, tarr(%rip)
	jle	.L26
	movq	%rax, %rdx
	xorl	%ebx, %ebx
	xorl	%ebp, %ebp
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L32:
	movslq	%eax, %rdi
	addl	$1, %eax
	cmpl	global_waitingQ+8(%rip), %eax
	movq	global_waitingQ(%rip), %rsi
	movq	%rdx, (%rsi,%rdi,8)
	movl	%eax, global_waitingQ+16(%rip)
	je	.L74
	cmpl	%eax, %ecx
	je	.L75
.L31:
	movq	%rbx, %rdi
	addq	tarr(%rip), %rdi
	addl	$1, %ebp
	call	fork_thread
	movq	%rbx, %rax
	addq	tarr(%rip), %rax
	xorl	%edi, %edi
	movl	$.LC7, %esi
	addq	$240, %rbx
	movl	4(%rax), %ecx
	movl	(%rax), %edx
	xorl	%eax, %eax
	call	core_log.constprop.1
	cmpl	%ebp, num_thrds(%rip)
	jle	.L26
	movq	tarr(%rip), %rdx
.L27:
	movl	global_waitingQ+16(%rip), %eax
	addq	%rbx, %rdx
	movl	%ebp, 4(%rdx)
	movl	$-1, 212(%rdx)
	movl	$4, 208(%rdx)
	cmpl	$-1, %eax
	je	.L31
	movl	global_waitingQ+12(%rip), %ecx
	cmpl	$-1, %ecx
	jne	.L32
	movl	$0, global_waitingQ+12(%rip)
	xorl	%ecx, %ecx
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L74:
	xorl	%eax, %eax
	movl	$0, global_waitingQ+16(%rip)
	cmpl	%eax, %ecx
	jne	.L31
.L75:
	movl	$-1, global_waitingQ+16(%rip)
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L26:
	movl	$simlock, %edi
	xorl	%ebx, %ebx
	leaq	12(%rsp), %rbp
	call	pthread_mutex_unlock
	call	sched_yield
	movl	num_thrds(%rip), %ecx
	testl	%ecx, %ecx
	jle	.L29
	.p2align 4,,10
	.p2align 3
.L58:
	movq	%rbp, %rdi
	addl	$1, %ebx
	call	wait
	movzbl	13(%rsp), %ecx
	movl	%eax, %edx
	xorl	%edi, %edi
	xorl	%eax, %eax
	movl	$.LC9, %esi
	call	core_log.constprop.1
	cmpl	%ebx, num_thrds(%rip)
	jg	.L58
.L29:
	xorl	%edi, %edi
	xorl	%eax, %eax
	movl	$.LC8, %esi
	call	core_log.constprop.1
	movl	num_cores(%rip), %edx
	xorl	%ebx, %ebx
	movl	$1, is_terminated(%rip)
	leaq	12(%rsp), %rbp
	testl	%edx, %edx
	js	.L36
	.p2align 4,,10
	.p2align 3
.L57:
	movq	%rbp, %rdi
	addl	$1, %ebx
	call	wait
	movzbl	13(%rsp), %ecx
	movl	%eax, %edx
	xorl	%edi, %edi
	xorl	%eax, %eax
	movl	$.LC10, %esi
	call	core_log.constprop.1
	cmpl	%ebx, num_cores(%rip)
	jge	.L57
.L36:
	movl	num_thrds(%rip), %eax
	xorl	%ebp, %ebp
	xorl	%ebx, %ebx
	testl	%eax, %eax
	jle	.L39
	.p2align 4,,10
	.p2align 3
.L56:
	movq	%rbp, %rdi
	addq	tarr(%rip), %rdi
	addl	$1, %ebx
	addq	$240, %rbp
	call	clear_thread
	cmpl	%ebx, num_thrds(%rip)
	jg	.L56
.L39:
	movq	tarr(%rip), %rdi
	call	free
	movq	carr(%rip), %rdi
	call	free
	movq	global_waitingQ(%rip), %rdi
	testq	%rdi, %rdi
	je	.L42
	call	free
.L42:
	movl	$simlock, %edi
	movq	$0, global_waitingQ(%rip)
	call	pthread_mutex_destroy
	movl	$sched_cv, %edi
	call	pthread_cond_destroy
	movl	$run_cv, %edi
	call	pthread_cond_destroy
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L70:
	.cfi_restore_state
	movl	$1, affinity_enabled(%rip)
	movb	$0, (%rax)
	movq	24(%rbp), %rbx
	jmp	.L18
.L67:
	movl	$1, unblock_signal(%rip)
	movb	$0, (%rax)
	movq	8(%rbp), %rbx
	jmp	.L14
.L45:
	xorl	%eax, %eax
.L15:
	salq	$4, %rax
	movq	MY_SCHED+8(%rax), %rax
	movq	%rax, sched_func(%rip)
	jmp	.L16
.L48:
	xorl	%eax, %eax
.L19:
	salq	$4, %rax
	movq	MY_BALANCE+8(%rax), %rax
	movq	%rax, balance_func(%rip)
	jmp	.L20
.L46:
	movl	$1, %eax
	jmp	.L15
.L49:
	movl	$1, %eax
	jmp	.L19
.L71:
	movl	$2, %eax
	jmp	.L19
.L47:
	movl	$2, %eax
	jmp	.L15
.L68:
	movl	$3, %eax
	jmp	.L15
.L72:
	movq	8(%rbp), %rdx
	movl	$.LC5, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L69:
	movq	%rbx, %rdx
	movl	$.LC4, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	errx
.L66:
	movq	(%rsi), %rdx
	movq	stderr(%rip), %rdi
	xorl	%eax, %eax
	movq	usage(%rip), %rsi
	call	fprintf
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE50:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE11:
	.section	.text.startup
.LHOTE11:
	.globl	usage
	.section	.rodata.str1.8
	.align 8
.LC12:
	.ascii	"\nUSAGE: %s <sched_func>[+] <num_thrds> <balance_func> <num_"
	.ascii	"cores> [<threads_data_filename> <min_time> <max_tim>]\n    <"
	.ascii	"sched_func>: name of the scheduling function for a single co"
	.ascii	"re\n    <num_thrds>: number of user threads to simulate\n   "
	.ascii	" <balance_func>: name of the load balance function\n    <num"
	.ascii	"_cores>: number of processor cores to simulate\n    <threads"
	.ascii	"_binding_filename>:  Predefined core binding information for"
	.ascii	" each thread\n    <min_time>: "
	.string	"min. run time per user thread in ms (default: 1000)\n    <max_time>: max. run time per user thread in ms (default: 1500)\nNOTE: If <sched_func> is followed immediately by '+' (without quotes),\n      unblocking user threads will signal scheduler to wake up.\n\n"
	.data
	.align 8
	.type	usage, @object
	.size	usage, 8
usage:
	.quad	.LC12
	.globl	seed_multiplier
	.section	.rodata
	.align 4
	.type	seed_multiplier, @object
	.size	seed_multiplier, 4
seed_multiplier:
	.long	4001
	.globl	max_time
	.data
	.align 4
	.type	max_time, @object
	.size	max_time, 4
max_time:
	.long	1500
	.globl	min_time
	.align 4
	.type	min_time, @object
	.size	min_time, 4
min_time:
	.long	1000
	.globl	threads_data_filename
	.bss
	.align 8
	.type	threads_data_filename, @object
	.size	threads_data_filename, 8
threads_data_filename:
	.zero	8
	.globl	num_thrds
	.align 4
	.type	num_thrds, @object
	.size	num_thrds, 4
num_thrds:
	.zero	4
	.globl	num_cores
	.align 4
	.type	num_cores, @object
	.size	num_cores, 4
num_cores:
	.zero	4
	.globl	balance_func
	.align 8
	.type	balance_func, @object
	.size	balance_func, 8
balance_func:
	.zero	8
	.globl	sched_func
	.align 8
	.type	sched_func, @object
	.size	sched_func, 8
sched_func:
	.zero	8
	.globl	carr
	.align 8
	.type	carr, @object
	.size	carr, 8
carr:
	.zero	8
	.globl	tarr
	.align 8
	.type	tarr, @object
	.size	tarr, 8
tarr:
	.zero	8
	.comm	global_waitingQ,24,16
	.globl	affinity_ts
	.section	.rodata
	.align 16
	.type	affinity_ts, @object
	.size	affinity_ts, 16
affinity_ts:
	.quad	0
	.quad	600000000
	.globl	tick_ts
	.align 16
	.type	tick_ts, @object
	.size	tick_ts, 16
tick_ts:
	.quad	0
	.quad	200000000
	.globl	zero_ts
	.align 16
	.type	zero_ts, @object
	.size	zero_ts, 16
zero_ts:
	.zero	16
	.globl	is_terminated
	.bss
	.align 4
	.type	is_terminated, @object
	.size	is_terminated, 4
is_terminated:
	.zero	4
	.globl	affinity_enabled
	.align 4
	.type	affinity_enabled, @object
	.size	affinity_enabled, 4
affinity_enabled:
	.zero	4
	.globl	unblock_signal
	.align 4
	.type	unblock_signal, @object
	.size	unblock_signal, 4
unblock_signal:
	.zero	4
	.globl	block_sid
	.data
	.align 4
	.type	block_sid, @object
	.size	block_sid, 4
block_sid:
	.long	-1
	.globl	run_sid
	.align 4
	.type	run_sid, @object
	.size	run_sid, 4
run_sid:
	.long	-1
	.comm	sim_ts,16,16
	.comm	sched_cv,48,32
	.comm	run_cv,48,32
	.comm	loglock,40,32
	.comm	simlock,40,32
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
