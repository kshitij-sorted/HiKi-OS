section .data
    addition db "Addition: ", 0
    subtraction db "Subtraction: ", 0
    newline db 0xA
    buffer times 20 db 0


section .text
    global _start

printString:
    mov rax, 1
    mov rdi, 1
    mov rcx, rsi
    xor rdx, rdx
.countLoop:
    cmp byte [rcx + rdx], 0
    je .writeIt
    inc rdx
    jmp .countLoop
.writeIt:
    syscall
    ret

int2str:
    mov rcx, 0
    mov rdx, 0
    mov rdi, rsi
    add rsi, 19
    mov byte [rsi], 0
.reverseLoop:
    mov rax, rbx
    xor rdx, rdx
    mov r10, 10
    div r10
    add dl, '0'
    dec rsi
    mov [rsi], dl 
    inc rcx
    mov rbx, rax
    test rbx, rbx
    jnz .reverseLoop
    mov rsi, rsi
    ret

    
_start:
    mov rbx, 5
    mov rcx, 10
    add rbx, rcx; addition --> rbx = 15

    mov rsi, addition
    call printString

    mov rsi, buffer
    call int2str
    call printString

    mov rsi, newline
    call printString

    mov rbx, 5
    mov rcx, 10
    sub rcx, rbx; subtraction --> rcx = 5

    mov rsi, subtraction
    call printString

    mov rsi, buffer
    call int2str
    call printString

    mov rsi, newline
    call printString


    mov rax, 60
    xor rdi, rdi
    syscall

    