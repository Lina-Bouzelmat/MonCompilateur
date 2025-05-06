			# This code was produced by the CERI Compiler
	.data
	.align 8
a:	.quad 0
b:	.quad 0
c:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	push $0
	pop a
	push $3
	pop b
	push $0
	pop c
Keyword detected: IF
	push b
	push a
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	ja Vrai2	# If above
	push $0		# False
	jmp Suite2
Vrai2:	push $0xFFFFFFFFFFFFFFFF		# True
Suite2:
	pop %rax
	cmpq $0, %rax
	je ELSE0
	push b
	push $1
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop a
	jmp FinIf0
ELSE0:
	push $1
	pop a
FinIf 0:
Keyword detected: BEGIN
Debut du Block 
Keyword detected: WHILE
While 3:	#Debut de la boucle While 
	push a
	push $6
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	jb Vrai5	# If below
	push $0		# False
	jmp Suite5
Vrai5:	push $0xFFFFFFFFFFFFFFFF		# True
Suite5:
	pop %rax
	cmpq $0, %rax
	je FinWhile3	# Sorti avec condition fausse
	push a
	push $1
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop a
	jmp While3
FinWhile3:	# Fin de la boucle While
Keyword detected: FOR
	push $1
	pop %rax
	movq %rax, c
For5:	# debut de la boucle for
	push $3
	pop %rbx
	cmpq %rbx, c
	jg FinFor5
	push b
	push $1
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop b
	push c
	push $1
	pop %rbx
	pop %rax
	addq %rbx, %rax
	push %rax
	pop c
	jmp For5
FinFor5:	# Fin de la boucle
Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
