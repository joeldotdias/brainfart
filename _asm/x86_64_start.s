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
