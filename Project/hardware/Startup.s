.section .vectors
.global _start

_start:
    lui sp, %hi(_estack)
    addi sp, sp, %lo(_estack)

    # Инициализация системного таймера
    lui	a5,0x50
    li	a4,4
    sw	a4,20(a5)
    
    # Вход в функцию main
    call main
