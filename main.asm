section .text
    global main
extern ExitProcess
main:
    mov rcx,90
    call ExitProcess