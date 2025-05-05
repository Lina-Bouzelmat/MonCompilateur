			# This code was produced by the CERI Compiler
	.data
	.align 8
i:	.quad 0
sum:	.quad 0
max:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	push $1
	pop i
	push $0
	pop sum
	push $10
	pop max
Keyword detected: WHILE
While 0:	#Debut de la boucle While 
	push i
	push max
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	jbe Vrai2	# If below or equal
	push $0		# False
	jmp Suite2
Vrai2:	push $0xFFFFFFFFFFFFFFFF		# True
Suite2:
	pop %rax
	cmpq $0, %rax
	jge FinWhile0	# Sorti avec condition fausse
Keyword detected: BEGIN
Debut du Block 
	push sum
	push i
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop sum
	push i
	push $1
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop i
Fin de Block
	jmp While0
FinWhile0:	# Fin de la boucle While
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
