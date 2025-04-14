section .bss; Creating a temporary storage (buffer) of 20 + 1(for "\n") bytes.
    buffer resb 21; buffer is a name of a variable used to store data temporarily (convension), pointing to the start of the 21 bytes.

section .text
    global _start

_start:
    mov rdi, 123876; storing the number in register rdi
    mov rcx, buffer + 20; making rcx point to the end of the 21 bytes.
    mov rax, rdi; moving the number to rax for calculations

.int2strLoop:
    xor rdx, rdx; clearing rdx (as mentioned in the notes)
    mov rbx, 10; using 10 to separate indivisual digits from the number
    div rbx; rax/rbx (quotient goes to rbx and remainder goes to rdx): we need the number in rdx
    ; register dl is a subset of rdx which contains the lower bytes of rdx. Therefore the remainder already is stored in dl
    add dl, '0'; converting the remainder into usable ASCII value (explained in notes)
    ;rcx was initially pointing to the end of 21 bytes, now as the last digit is converted into the sting, we decrement it's position
    dec rcx; rcx = rcx - 1
    mov [rcx], dl; []: Store the value present in dl at the memory address pointed by rcx
    test rax, rax; if statement for loop. if rax == 0 stop the loop, if rax != 0 keep looping
    jnz .int2strLoop ;loop statement

    mov rax, 1; Start OS
    mov rdi, 1; Print
    mov rsi, rcx; pointer to start of number string
    mov rdx, buffer + 20; move rdx to the end of te 21 reserved bytes
    sub rdx, rcx; calculating the number of bytes to print
    syscall

    ;exit 
    mov rax, 60
    xor rdi, rdi
    syscall
