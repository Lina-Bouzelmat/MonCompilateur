			# This code was produced by the CERI Compiler
	.data
FormatString1:	.string "%llu\n"
FormatString2:	.string "%f\n"
FormatString3:	.string "%c\n"
	.align 8
a:	.quad 0
b:	.quad 0
c:	.quad 0
x:	.double 0.0
y:	.double 0.0
ch1:	.byte 0
ch2:	.byte 0
bool1:	.quad 0
bool2:	.quad 0
	.text		# The following lines contain the program
	.globl main	# The main function must be visible from outside
main:			# The main function body :
	movq %rsp, %rbp	# Save the position of the stack's top
	# Debut du Block
	pushq $42
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, a(%rip)
	pushq $4614253070214989087	# empile le flottant 3.14
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, x(%rip)
	pushq $65	# empile le caractère 'A'
	movq (%rsp), %rax
	addq $8, %rsp
	movb %al, ch1(%rip)
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, bool1(%rip)
	pushq $10
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, b(%rip)
	movq a(%rip), %rax
	pushq %rax
	movq b(%rip), %rax
	pushq %rax
	popq %rbx
	popq %rax
	addq %rbx, %rax	# ADD
	pushq %rax
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, c(%rip)
	movq x(%rip), %rax
	pushq %rax
	movsd (%rsp), %xmm0
	addq $8, %rsp
	movsd %xmm0, y(%rip)
	pushq $1
	movq (%rsp), %rax
	addq $8, %rsp
	movq %rax, a(%rip)
For0:
	pushq $5
	popq %rbx
	cmpq %rbx, a
	jg FinFor0
	movq a(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	movq a(%rip), %rax
	addq $1, %rax
	movq %rax, a(%rip)
	jmp For0
FinFor0:
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
	movq ch1(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString3, %rdi
	movl $0, %eax
	call printf@PLT
	movq bool1(%rip), %rax
	pushq %rax
	popq %rsi
	movq $FormatString1, %rdi
	movl $0, %eax
	call printf@PLT
	# Fin de Block
	movq %rbp, %rsp		# Restore the position of the stack's top
	ret			# Return from main function
