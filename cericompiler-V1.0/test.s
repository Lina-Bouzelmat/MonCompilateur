			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
	.align 8
i:	.quad 0
j:	.quad 0
k:	.quad 0
x:	.double 0.0
c:	.byte 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
For0:
	pushq $3
	popq %rbx
	cmpq %rbx, i
	jg FinFor0
	# Debut du Block
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, j(%rip)
For1:
	pushq $2
	popq %rbx
	cmpq %rbx, j
	jg FinFor1
	# Debut du Block
	movq j(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq i(%rip), %rax
	pushq %rax
	movq j(%rip), %rax
	pushq %rax
	popq %rbx
	popq %rax
	imulq %rbx, %rax
	pushq %rax
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, k(%rip)
	movq k(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	# Fin de Block
	movq j(%rip), %rax
	addq $1, %rax
	movq %rax, j(%rip)
	jmp For1
FinFor1:
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, k(%rip)
For2:
	pushq $2
	popq %rbx
	cmpq %rbx, k
	jg FinFor2
	# Debut du Block
	pushq $65	# empile le caractère 'A'
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, c(%rip)
	movq c(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	pushq $66	# empile le caractère 'B'
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, c(%rip)
	movq c(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	# Fin de Block
	movq k(%rip), %rax
	addq $1, %rax
	movq %rax, k(%rip)
	jmp For2
FinFor2:
	# Fin de Block
	movq i(%rip), %rax
	addq $1, %rax
	movq %rax, i(%rip)
	jmp For0
FinFor0:
	movabs $4609434218613702656, %rax	# charge le flottant 1.5 (4609434218613702656)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movq x(%rip), %rax
	pushq %rax
	fldl (%rsp)
	addq $8, %rsp
	subq $8, %rsp
	fstpl (%rsp)
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	movq x(%rip), %rax
	pushq %rax
	movabs $4607182418800017408, %rax	# charge le flottant 1 (4607182418800017408)
	pushq %rax
	fldl 8(%rsp)
	fldl (%rsp)
	addq $16, %rsp
	faddp
	subq $8, %rsp
	fstpl (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movq x(%rip), %rax
	pushq %rax
	fldl (%rsp)
	addq $8, %rsp
	subq $8, %rsp
	fstpl (%rsp)
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
