			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
	.align 8
i:	.quad 0
c:	.byte 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	pushq $2
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq i(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $1, %rax
	jne Case0_1
	pushq $10
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase0
Case0_1:
	movq %rbx, %rax
	cmpq $2, %rax
	jne Case0_2
	pushq $20
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase0
Case0_2:
	movq %rbx, %rax
	cmpq $3, %rax
	jne Case0_3
	pushq $30
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase0
Case0_3:
EndCase0:
	pushq $66	# empile le caractère 'B'
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, c(%rip)
	movq c(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $'A', %rax
	jne Case1_1
	pushq $88	# empile le caractère 'X'
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase1
Case1_1:
	movq %rbx, %rax
	cmpq $'B', %rax
	jne Case1_2
	pushq $89	# empile le caractère 'Y'
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase1
Case1_2:
	movq %rbx, %rax
	cmpq $'C', %rax
	jne Case1_3
	pushq $90	# empile le caractère 'Z'
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase1
Case1_3:
EndCase1:
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq i(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $1, %rax
	jne Case2_1
	# Debut du Block
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq c(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $'B', %rax
	jne Case3_1
	pushq $89	# empile le caractère 'Y'
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase3
Case3_1:
EndCase3:
	# Fin de Block
	jmp EndCase2
Case2_1:
	movq %rbx, %rax
	cmpq $2, %rax
	jne Case2_2
	pushq $2
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase2
Case2_2:
EndCase2:
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
