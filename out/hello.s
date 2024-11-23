# GNU Assembler, AT&T syntax, x86_64 Linux

.global _start

.data

.equ SYS_EXIT, 60
.equ SUCCESS, 0
.equ SYS_WRITE,1
.equ STDOUT,1
.equ SYS_READ, 0
.equ STDIN, 0

.bss
.lcomm MEM_TAPE, 30000

.text

_start:
    leaq MEM_TAPE, %r12

	addb $10, (%r12)
	cmpb $0, (%r12)
	je LOOP_END_12

LOOP_START_1:

	addq $1, %r12
	addb $7, (%r12)
	addq $1, %r12
	addb $10, (%r12)
	addq $1, %r12
	addb $3, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	subq $4, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_1

LOOP_END_12:

	addq $1, %r12
	addb $2, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addq $1, %r12
	addb $1, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addb $7, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addb $3, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addq $1, %r12
	addb $2, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	subq $2, %r12
	addb $15, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addq $1, %r12
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addb $3, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	subb $6, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	subb $8, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addq $1, %r12
	addb $1, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	addq $1, %r12
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

    movq $SYS_EXIT, %rax
    movq $SUCCESS, %rdi
    syscall

    pop %rbp
