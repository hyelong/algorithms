	.file	"prj2_scheduling.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	static_priority
	.type	static_priority, @function
static_priority:
.LFB32:
	.cfi_startproc
	movl	176(%rdi), %ecx
	movl	168(%rdi), %r8d
	movl	172(%rdi), %edx
	cmpl	$-1, %ecx
	je	.L8
	movl	$-1, %eax
	cmpl	%eax, %edx
	je	.L3
	movl	%ecx, %eax
	subl	%edx, %eax
.L2:
	leal	(%rax,%r8), %ecx
	testl	%eax, %eax
	cmovs	%ecx, %eax
	cmpl	$0, %eax
	je	.L10
	jle	.L11
	movq	160(%rdi), %r9
	leal	(%rax,%rdx), %edi
	movl	%r8d, %eax
	.p2align 4,,10
	.p2align 3
.L7:
	movl	%edx, %ecx
	subl	%r8d, %ecx
	cmpl	%edx, %r8d
	cmovg	%edx, %ecx
	movslq	%ecx, %rcx
	movq	(%r9,%rcx,8), %rsi
	movl	4(%rsi), %ecx
	cmpl	%eax, %ecx
	jge	.L6
	cmpl	$2, 208(%rsi)
	cmove	%ecx, %eax
.L6:
	addl	$1, %edx
	cmpl	%edx, %edi
	jne	.L7
	rep ret
.L11:
	movl	%r8d, %eax
.L3:
	rep ret
	.p2align 4,,10
	.p2align 3
.L8:
	movl	%r8d, %eax
	jmp	.L2
.L10:
	movl	$-1, %eax
	ret
	.cfi_endproc
.LFE32:
	.size	static_priority, .-static_priority
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	most_remaining_time
	.type	most_remaining_time, @function
most_remaining_time:
.LFB33:
	.cfi_startproc
	movl	176(%rdi), %ecx
	movl	168(%rdi), %r8d
	movl	172(%rdi), %edx
	cmpl	$-1, %ecx
	je	.L23
	movl	$-1, %eax
	subl	%edx, %ecx
	cmpl	%eax, %edx
	je	.L18
.L17:
	leal	(%rcx,%r8), %eax
	testl	%ecx, %ecx
	cmovs	%eax, %ecx
	movl	$-1, %eax
	testl	%ecx, %ecx
	jle	.L18
	movq	160(%rdi), %r10
	leal	(%rcx,%rdx), %edi
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L22:
	movl	%edx, %ecx
	subl	%r8d, %ecx
	cmpl	%edx, %r8d
	cmovg	%edx, %ecx
	movslq	%ecx, %rcx
	movq	(%r10,%rcx,8), %rsi
	movl	56(%rsi), %ecx
	cmpl	%r9d, %ecx
	jl	.L21
	movl	4(%rsi), %eax
	movl	%ecx, %r9d
.L21:
	addl	$1, %edx
	cmpl	%edx, %edi
	jne	.L22
.L18:
	rep ret
	.p2align 4,,10
	.p2align 3
.L23:
	movl	%r8d, %ecx
	jmp	.L17
	.cfi_endproc
.LFE33:
	.size	most_remaining_time, .-most_remaining_time
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	round_robin_queue
	.type	round_robin_queue, @function
round_robin_queue:
.LFB34:
	.cfi_startproc
	movl	176(%rdi), %edx
	movl	168(%rdi), %ecx
	movl	172(%rdi), %esi
	cmpl	$-1, %edx
	je	.L32
	movl	$-1, %eax
	cmpl	%eax, %esi
	je	.L30
	movl	%edx, %eax
	subl	%esi, %eax
.L29:
	addl	%eax, %ecx
	testl	%eax, %eax
	cmovs	%ecx, %eax
	testl	%eax, %eax
	jle	.L34
	movq	160(%rdi), %rax
	movq	(%rax), %rax
	movl	4(%rax), %eax
	ret
.L34:
	orl	$-1, %eax
.L30:
	rep ret
	.p2align 4,,10
	.p2align 3
.L32:
	movl	%ecx, %eax
	jmp	.L29
	.cfi_endproc
.LFE34:
	.size	round_robin_queue, .-round_robin_queue
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	round_robin_static
	.type	round_robin_static, @function
round_robin_static:
.LFB35:
	.cfi_startproc
	movl	176(%rdi), %r11d
	movl	168(%rdi), %r9d
	movl	172(%rdi), %edx
	cmpl	$-1, %r11d
	je	.L41
	movl	$-1, %eax
	subl	%edx, %r11d
	cmpl	%eax, %edx
	je	.L51
.L37:
	leal	(%r11,%r9), %eax
	testl	%r11d, %r11d
	cmovs	%eax, %r11d
	testl	%r11d, %r11d
	jle	.L43
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	last_run_sid(%rip), %r10d
	addl	%edx, %r11d
	movq	160(%rdi), %rbx
	movl	%r9d, %r8d
	movl	$-1, %eax
	.p2align 4,,10
	.p2align 3
.L40:
	movl	%edx, %ecx
	subl	%r9d, %ecx
	cmpl	%edx, %r9d
	cmovg	%edx, %ecx
	movslq	%ecx, %rcx
	movq	(%rbx,%rcx,8), %rcx
	movl	4(%rcx), %edi
	leal	(%r9,%rdi), %ecx
	movl	%edi, %esi
	subl	%r10d, %esi
	subl	%r10d, %ecx
	cmpl	%r10d, %edi
	cmovg	%esi, %ecx
	movl	%r8d, %esi
	cmpl	%r8d, %ecx
	cmovle	%ecx, %esi
	cmovle	%edi, %eax
	addl	$1, %edx
	cmpl	%edx, %r11d
	movl	%esi, %r8d
	jne	.L40
	cmpl	$-1, %eax
	je	.L38
	movl	%eax, last_run_sid(%rip)
.L38:
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
.L51:
	rep ret
	.p2align 4,,10
	.p2align 3
.L41:
	movl	%r9d, %r11d
	jmp	.L37
.L43:
	movl	$-1, %eax
	ret
	.cfi_endproc
.LFE35:
	.size	round_robin_static, .-round_robin_static
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	get_list_count
	.type	get_list_count, @function
get_list_count:
.LFB31:
	.cfi_startproc
	movl	24(%rsp), %ecx
	movl	16(%rsp), %edx
	movl	20(%rsp), %esi
	cmpl	$-1, %ecx
	je	.L55
	xorl	%eax, %eax
	cmpl	$-1, %esi
	je	.L54
	movl	%ecx, %eax
	subl	%esi, %eax
.L53:
	addl	%eax, %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
.L54:
	rep ret
	.p2align 4,,10
	.p2align 3
.L55:
	movl	%edx, %eax
	jmp	.L53
	.cfi_endproc
.LFE31:
	.size	get_list_count, .-get_list_count
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.globl	MY_SCHED
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC5:
	.string	"static_priority"
.LC6:
	.string	"most_remaining_time"
.LC7:
	.string	"round_robin_queue"
.LC8:
	.string	"round_robin_static"
	.data
	.align 32
	.type	MY_SCHED, @object
	.size	MY_SCHED, 64
MY_SCHED:
	.quad	.LC5
	.quad	static_priority
	.quad	.LC6
	.quad	most_remaining_time
	.quad	.LC7
	.quad	round_robin_queue
	.quad	.LC8
	.quad	round_robin_static
	.globl	last_run_sid
	.align 4
	.type	last_run_sid, @object
	.size	last_run_sid, 4
last_run_sid:
	.long	-1
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
