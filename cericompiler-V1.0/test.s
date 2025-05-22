			# This code was produced by the CERI Compiler
	.data
PI:	.double 3.14159
MAX:	.quad 100
VRAI:	.quad -1
FAUX:	.quad 0
CH:	.quad 65
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
FormatString4:	.string "%lld\n"
	.align 8
i:	.quad 0
j:	.quad 0
k:	.quad 0
x:	.double 0.0
y:	.double 0.0
b:	.quad 0
c:	.byte 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	pushq $5
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq i(%rip), %rax
	pushq %rax
	movq (%rsp), %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	addq $8, %rsp
	movq PI(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	movq x(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	movq VRAI(%rip), %rax
	pushq %rax
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, b(%rip)
	movq b(%rip), %rax
	pushq %rax
	movq (%rsp), %rsi
	movq $FormatString4, %rdi
	movl $0, %eax
	call printf@PLT
	addq $8, %rsp
	movq CH(%rip), %rax
	pushq %rax
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, c(%rip)
	movq c(%rip), %rax
	pushq %rax
	movq (%rsp), %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	addq $8, %rsp
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
	movq (%rsp), %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	addq $8, %rsp
	# Fin de Block
	movq i(%rip), %rax
	addq $1, %rax
	movq %rax, i(%rip)
	jmp For0
FinFor0:
	pushq $2
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, i(%rip)
	movq i(%rip), %rax
	pushq %rax
	popq %rbx
	movq %rbx, %rax
	cmpq $1, %rax
	jne Case1_1
	movabs $4609434218613702656, %rax	# charge le flottant 1.5 (4609434218613702656)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	jmp EndCase1
Case1_1:
	movq %rbx, %rax
	cmpq $2, %rax
	jne Case1_2
	movabs $4612811918334230528, %rax	# charge le flottant 2.5 (4612811918334230528)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	jmp EndCase1
Case1_2:
	movq %rbx, %rax
	cmpq $3, %rax
	jne Case1_3
	movabs $4615063718147915776, %rax	# charge le flottant 3.5 (4615063718147915776)
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	jmp EndCase1
Case1_3:
EndCase1:
	movq x(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	movq $FormatString2, %rdi
	movl $1, %eax
	call printf@PLT
	addq $8, %rsp
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
