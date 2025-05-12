			# This code was produced by the CERI Compiler
	.data
	.align 8
a:	.quad 0
b:	.quad 0
c:	.quad 0
d:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	push $10
	pop a
	push $20
	pop b
	push a
	push b
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop c
	push a
	push b
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	push $2
	pop %rbx
	pop %rax
	mulq	%rbx
	push %rax	# MUL
	pop d
Keyword detected: IF
	push a
	push b
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	je Vrai2	# If equal
	push $0		# False
	jmp Suite2
Vrai2:	push $0xFFFFFFFFFFFFFFFF		# True
Suite2:
	pop %rax
	cmpq $0, %rax
	je ELSE0
	push $100
	pop c
	jmp FinIf0
ELSE0:
	push $200
	pop c
FinIf 0:
Keyword detected: WHILE
While 2:	#Debut de la boucle While 
	push c
	push $300
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	jb Vrai4	# If below
	push $0		# False
	jmp Suite4
Vrai4:	push $0xFFFFFFFFFFFFFFFF		# True
Suite4:
	pop %rax
	cmpq $0, %rax
	je FinWhile2	# Sorti avec condition fausse
	push c
	push $1
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop c
	jmp While2
FinWhile2:	# Fin de la boucle While
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
