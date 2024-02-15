section .text
    global main
extern ExitProcess
main:
    mov rcx,256
    call ExitProcess