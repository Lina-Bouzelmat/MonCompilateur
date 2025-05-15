			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
	.align 8
a:	.quad 0
b:	.quad 0
c:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	push $5
	push $3
	pop %rbx
	pop %rax
	addq	%rbx, %rax	# ADD
	push %rax
	pop a
	push a
	push $2
	pop %rbx
	pop %rax
	mulq	%rbx
	push %rax	# MUL
	pop b
	push a
	push b
	pop %rax
	pop %rbx
	cmpq %rax, %rbx
	jb Vrai2	# If below
	push $0		# False
	jmp Suite2
Vrai2:	push $0xFFFFFFFFFFFFFFFF		# True
Suite2:
	pop %rax
	cmpq $0, %rax
	je ELSE0
	push b
	push a
	pop %rbx
	pop %rax
	subq	%rbx, %rax	# SUB
	push %rax
	pop c
	jmp FinIf0
ELSE0:
	push $0
	pop c
FinIf0:
	push a
	pop %rsi		# valeur à afficher
	movq $FormatString1, %rdi	# format
	movl $0, %eax
	push %rbp		# sauvegarder base pointer
	call printf@PLT
	pop %rbp		# restaurer base pointer
	push b
	pop %rsi		# valeur à afficher
	movq $FormatString1, %rdi	# format
	movl $0, %eax
	push %rbp		# sauvegarder base pointer
	call printf@PLT
	pop %rbp		# restaurer base pointer
	push c
	pop %rsi		# valeur à afficher
	movq $FormatString1, %rdi	# format
	movl $0, %eax
	push %rbp		# sauvegarder base pointer
	call printf@PLT
	pop %rbp		# restaurer base pointer
While2:
	push c
	push $10
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
	push c
	pop %rsi		# valeur à afficher
	movq $FormatString1, %rdi	# format
	movl $0, %eax
	push %rbp		# sauvegarder base pointer
	call printf@PLT
	pop %rbp		# restaurer base pointer
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
