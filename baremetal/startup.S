    .section .init
    .globl _start
_start:
    la   sp, _stack_top       # stack
    call main                 # saltar a main()
1:  wfi                       # ahorro de energía
    j 1b
