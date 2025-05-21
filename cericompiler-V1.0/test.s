			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
	.align 8
x:	.double 0.0
i:	.quad 0
j:	.quad 0
k:	.quad 0
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
	cmpq %rbx, i(%rip)
	jg FinFor0
	# Debut du Block
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	pushq $10
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, j(%rip)
For1:
	pushq $6
	popq %rbx
	cmpq %rbx, j(%rip)
	jl FinFor1
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
	subq $2, %rax
	movq %rax, j(%rip)
	jmp For1
FinFor1:
	movq i(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $1, %rax
	jne Case2_1
	pushq $100
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, k(%rip)
	jmp EndCase2
Case2_1:
	movq %rbx, %rax
	cmpq $2, %rax
	jne Case2_2
	pushq $200
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, k(%rip)
	jmp EndCase2
Case2_2:
	movq %rbx, %rax
	cmpq $3, %rax
	jne Case2_3
	pushq $300
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, k(%rip)
	jmp EndCase2
Case2_3:
EndCase2:
	movq k(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	# Fin de Block
	movq i(%rip), %rax
	addq $1, %rax
	movq %rax, i(%rip)
	jmp For0
FinFor0:
	pushq $0
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, j(%rip)
For3:
	pushq $3
	popq %rbx
	cmpq %rbx, j(%rip)
	jg FinFor3
	# Debut du Block
While4:
	movq i(%rip), %rax
	pushq %rax
	pushq $3
	popq %rax
	popq %rbx
	cmpq %rax, %rbx
	jb Vrai6	# If below
	pushq $0		# False
	jmp Suite6
Vrai6:	pushq $0xFFFFFFFFFFFFFFFF		# True
Suite6:
	popq %rax
	cmpq $0, %rax
	je FinWhile4	# Sorti avec condition fausse
	# Debut du Block
	movq i(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq i(%rip), %rax
	pushq %rax
	pushq $1
	popq %rbx
	popq %rax
	addq %rbx, %rax	# ADD
	pushq %rax
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq i(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $1, %rax
	jne Case6_1
	pushq $11
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase6
Case6_1:
	movq %rbx, %rax
	cmpq $2, %rax
	jne Case6_2
	pushq $22
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase6
Case6_2:
	movq %rbx, %rax
	cmpq $3, %rax
	jne Case6_3
	pushq $33
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase6
Case6_3:
EndCase6:
	# Fin de Block
	jmp While4
FinWhile4:	# Fin de la boucle While
	movq j(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	# Fin de Block
	movq j(%rip), %rax
	addq $1, %rax
	movq %rax, j(%rip)
	jmp For3
FinFor3:
	pushq $65	# empile le caractère 'A'
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, c(%rip)
While7:
	movq c(%rip), %rax
	pushq %rax
	pushq $67	# empile le caractère 'C'
	popq %rax
	popq %rbx
	cmpb %al, %bl
	jbe Vrai9	# If below or equal
	pushq $0		# False
	jmp Suite9
Vrai9:	pushq $0xFFFFFFFFFFFFFFFF		# True
Suite9:
	popq %rax
	cmpq $0, %rax
	je FinWhile7	# Sorti avec condition fausse
	# Debut du Block
	movq c(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	movq c(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $'A', %rax
	jne Case9_1
	pushq $65
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase9
Case9_1:
	movq %rbx, %rax
	cmpq $'B', %rax
	jne Case9_2
	pushq $66
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase9
Case9_2:
	movq %rbx, %rax
	cmpq $'C', %rax
	jne Case9_3
	pushq $67
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	jmp EndCase9
Case9_3:
EndCase9:
	movq c(%rip), %rax
	pushq %rax
	pushq $66	# empile le caractère 'B'
	popq %rbx
	popq %rax
	movb %bl, %bl
	movb %al, %al
	addb %bl, %al
	pushq %rax	# ADD char
	pushq $65	# empile le caractère 'A'
	popq %rbx
	popq %rax
	movb %bl, %bl
	movb %al, %al
	subb %bl, %al
	pushq %rax	# SUB char
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, c(%rip)
	# Fin de Block
	jmp While7
FinWhile7:	# Fin de la boucle While
	movabs $4614253070214989087, %rax	# charge le flottant 3.14 (4614253070214989087)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	pushq $2
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq x(%rip), %rax
	pushq %rax
	movq i(%rip), %rax
	pushq %rax
	fildq (%rsp)
	addq $8, %rsp
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
	movabs $4612811918334230528, %rax	# charge le flottant 2.5 (4612811918334230528)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	pushq $3
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq x(%rip), %rax
	pushq %rax
	movq i(%rip), %rax
	pushq %rax
	fildq (%rsp)
	addq $8, %rsp
	subq $8, %rsp
	fstpl (%rsp)
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
