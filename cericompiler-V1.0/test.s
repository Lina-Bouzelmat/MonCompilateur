			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
FormatString4:	.string "%lld\n"
	.align 8
c:	.double 0.0
b:	.double 0.0
a:	.double 0.0
x:	.double 0.0
y:	.double 0.0
z:	.double 0.0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	movabs $4621819117588971520, %rax	# charge le flottant 10 (4621819117588971520)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, a(%rip)
	movabs $4624633867356078080, %rax	# charge le flottant 15 (4624633867356078080)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, b(%rip)
	movq a(%rip), %rax
	pushq %rax
	movq b(%rip), %rax
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
	movsd %xmm0, c(%rip)
	movq c(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	movabs $4614253070214989087, %rax	# charge le flottant 3.14 (4614253070214989087)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movabs $4617315517961601024, %rax	# charge le flottant 5 (4617315517961601024)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, y(%rip)
	movq x(%rip), %rax
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
	movsd %xmm0, z(%rip)
	movq z(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	movabs $4622100592565682176, %rax	# charge le flottant 10.5 (4622100592565682176)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movabs $4619905087747339059, %rax	# charge le flottant 7.3 (4619905087747339059)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, y(%rip)
	movq x(%rip), %rax
	pushq %rax
	movq y(%rip), %rax
	pushq %rax
	movabs $4617315517961601024, %rax	# charge le flottant 5 (4617315517961601024)
	pushq %rax
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	faddp
	subq $8, %rsp
	fstpl (%rsp)
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	fsubp
	fchs
	subq $8, %rsp
	fstpl (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, z(%rip)
	movq z(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	movabs $4611686018427387904, %rax	# charge le flottant 2 (4611686018427387904)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, a(%rip)
	movabs $4613937818241073152, %rax	# charge le flottant 3 (4613937818241073152)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, b(%rip)
	movq a(%rip), %rax
	pushq %rax
	movq b(%rip), %rax
	pushq %rax
	pushq $5
	fildq (%rsp)
	addq $8, %rsp
	subq $8, %rsp
	fstpl (%rsp)
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	fsubp
	fchs
	subq $8, %rsp
	fstpl (%rsp)
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	fmulp
	subq $8, %rsp
	fstpl (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, c(%rip)
	movq c(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
