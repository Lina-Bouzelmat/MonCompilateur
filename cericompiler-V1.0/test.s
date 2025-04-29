			# This code was produced by the CERI Compiler
	.data
	.align 8
a:	.quad 0
b:	.quad 0
x:	.quad 0
y:	.quad 0
z:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	push $5
	pop a
	push $10
	pop b
	push $0
	pop x
	push $1
	pop y
Keyword detected: BEGIN
Texte lu : BEGIN
Debut de la fonction Block Begin 0:
	push x
	push $1
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop x
	push y
	push $2
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop y
Keyword detected: IF
Debut de la fonction If 1:
	push x
	push $10
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	jb Vrai3	# If below
	push $0		# False
	jmp Suite3
Vrai3:	push $0xFFFFFFFFFFFFFFFF		# True
Suite3:
	pop %rax
	cmpq $0, %rax
	je Faux1
Keyword detected: BEGIN
Texte lu : BEGIN
Debut de la fonction Block Begin 3:
	push x
	push y
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop z
Keyword detected: END
	jmp FinIf1
Faux1:
