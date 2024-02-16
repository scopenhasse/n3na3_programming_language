section .text
    global main
extern ExitProcess
main:
    mov rcx,9
    call ExitProcess