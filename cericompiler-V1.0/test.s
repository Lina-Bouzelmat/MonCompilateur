			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
	.align 8
i:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	pushq $0
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
For0:
	pushq $10
	popq %rbx
	cmpq %rbx, i(%rip)
	jg FinFor0
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq i(%rip), %rax
	addq $2, %rax
	movq %rax, i(%rip)
	jmp For0
FinFor0:
	pushq $5
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
For1:
	pushq $1
	popq %rbx
	cmpq %rbx, i(%rip)
	jl FinFor1
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq i(%rip), %rax
	subq $1, %rax
	movq %rax, i(%rip)
	jmp For1
FinFor1:
	pushq $100
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
For2:
	pushq $0
	popq %rbx
	cmpq %rbx, i(%rip)
	jl FinFor2
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq i(%rip), %rax
	subq $25, %rax
	movq %rax, i(%rip)
	jmp For2
FinFor2:
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
