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

	addb $11, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	addq $4, %r12
	addb $44, (%r12)
	addq $1, %r12
	addb $32, (%r12)
	subq $6, %r12
	cmpb $0, (%r12)
	je LOOP_END_191

LOOP_START_8:

	addq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_17

LOOP_START_10:

	addq $6, %r12
	addb $1, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	subq $7, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_10

LOOP_END_17:

	addq $7, %r12
	cmpb $0, (%r12)
	je LOOP_END_24

LOOP_START_19:

	subq $7, %r12
	addb $1, (%r12)
	addq $7, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_19

LOOP_END_24:

	subq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_110

LOOP_START_26:

	addq $1, %r12
	addb $10, (%r12)
	cmpb $0, (%r12)
	je LOOP_END_73

LOOP_START_29:

	subb $1, (%r12)
	subq $1, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	je LOOP_END_40

LOOP_START_33:

	addq $2, %r12
	addb $1, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	subq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_33

LOOP_END_40:

	addq $3, %r12
	cmpb $0, (%r12)
	je LOOP_END_47

LOOP_START_42:

	subq $3, %r12
	addb $1, (%r12)
	addq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_42

LOOP_END_47:

	addb $1, (%r12)
	subq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_58

LOOP_START_50:

	addq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_54

LOOP_START_52:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_52

LOOP_END_54:

	subq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_58

LOOP_START_56:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_56

LOOP_END_58:

	addq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_71

LOOP_START_60:

	subq $2, %r12
	cmpb $0, (%r12)
	je LOOP_END_67

LOOP_START_62:

	addq $3, %r12
	addb $1, (%r12)
	subq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_62

LOOP_END_67:

	addq $2, %r12
	cmpb $0, (%r12)
	je LOOP_END_71

LOOP_START_69:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_69

LOOP_END_71:

	subq $2, %r12
	cmpb $0, (%r12)
	jne LOOP_START_29

LOOP_END_73:

	addq $3, %r12
	cmpb $0, (%r12)
	je LOOP_END_82

LOOP_START_75:

	addq $2, %r12
	addb $1, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	subq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_75

LOOP_END_82:

	addq $3, %r12
	cmpb $0, (%r12)
	je LOOP_END_89

LOOP_START_84:

	subq $3, %r12
	addb $1, (%r12)
	addq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_84

LOOP_END_89:

	addb $1, (%r12)
	subq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_100

LOOP_START_92:

	addq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_96

LOOP_START_94:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_94

LOOP_END_96:

	subq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_100

LOOP_START_98:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_98

LOOP_END_100:

	addq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_108

LOOP_START_102:

	subq $2, %r12
	addb $1, (%r12)
	addq $2, %r12
	cmpb $0, (%r12)
	je LOOP_END_108

LOOP_START_106:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_106

LOOP_END_108:

	subq $7, %r12
	cmpb $0, (%r12)
	jne LOOP_START_26

LOOP_END_110:

	addq $5, %r12
	cmpb $0, (%r12)
	je LOOP_END_117

LOOP_START_112:

	addb $48, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	cmpb $0, (%r12)
	je LOOP_END_117

LOOP_START_115:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_115

LOOP_END_117:

	addb $10, (%r12)
	subq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_125

LOOP_START_120:

	subb $1, (%r12)
	addq $1, %r12
	subb $1, (%r12)
	subq $1, %r12
	cmpb $0, (%r12)
	jne LOOP_START_120

LOOP_END_125:

	addq $1, %r12
	addb $48, (%r12)
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rdi
	movq %r12, %rsi
	mov $1, %rdx
	syscall

	cmpb $0, (%r12)
	je LOOP_END_131

LOOP_START_129:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_129

LOOP_END_131:

	subq $12, %r12
	cmpb $0, (%r12)
	je LOOP_END_140

LOOP_START_133:

	addq $3, %r12
	addb $1, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	subq $4, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_133

LOOP_END_140:

	addq $4, %r12
	cmpb $0, (%r12)
	je LOOP_END_147

LOOP_START_142:

	subq $4, %r12
	addb $1, (%r12)
	addq $4, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_142

LOOP_END_147:

	subq $1, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	je LOOP_END_158

LOOP_START_150:

	addq $2, %r12
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

	subq $3, %r12
	cmpb $0, (%r12)
	je LOOP_END_158

LOOP_START_156:

	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_156

LOOP_END_158:

	subq $2, %r12
	cmpb $0, (%r12)
	je LOOP_END_167

LOOP_START_160:

	addq $2, %r12
	addb $1, (%r12)
	addq $1, %r12
	addb $1, (%r12)
	subq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_160

LOOP_END_167:

	addq $3, %r12
	cmpb $0, (%r12)
	je LOOP_END_174

LOOP_START_169:

	subq $3, %r12
	addb $1, (%r12)
	addq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_169

LOOP_END_174:

	subq $2, %r12
	cmpb $0, (%r12)
	je LOOP_END_181

LOOP_START_176:

	subq $1, %r12
	addb $1, (%r12)
	addq $1, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_176

LOOP_END_181:

	addq $1, %r12
	cmpb $0, (%r12)
	je LOOP_END_188

LOOP_START_183:

	subq $1, %r12
	addb $1, (%r12)
	addq $1, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_183

LOOP_END_188:

	subq $3, %r12
	subb $1, (%r12)
	cmpb $0, (%r12)
	jne LOOP_START_8

LOOP_END_191:

    movq $SYS_EXIT, %rax
    movq $SUCCESS, %rdi
    syscall

    pop %rbp
