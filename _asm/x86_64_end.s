
    movq $SYS_EXIT, %rax
    movq $SUCCESS, %rdi
    syscall

    pop %rbp
