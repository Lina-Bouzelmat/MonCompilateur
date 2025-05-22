			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
FormatString4:	.string "%lld\n"
	.align 8
x:	.double 0.0
y:	.double 0.0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	movabs $4614253070214989087, %rax	# charge le flottant 3.14 (4614253070214989087)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movabs $0, %rax	# charge le flottant 0 (0)
	pushq %rax
	movq x(%rip), %rax
	pushq %rax
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	fsubp
	fchs
	subq $8, %rsp
	fstpl (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movq x(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	movabs $4612811918334230528, %rax	# charge le flottant 2.5 (4612811918334230528)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, y(%rip)
	movabs $0, %rax	# charge le flottant 0 (0)
	pushq %rax
	movq y(%rip), %rax
	pushq %rax
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	fsubp
	fchs
	subq $8, %rsp
	fstpl (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, y(%rip)
	movq y(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
