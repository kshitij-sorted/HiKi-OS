[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov si, msg_loading
    call print_string

    ; Load 20 sectors to 0x1000
    mov bx, 0x1000
    call load_kernel

    cli
    call enable_a20
    call switch_to_pm
    jmp $

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

switch_to_pm:
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_pm

[BITS 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Print X to verify bootloader reached here
    mov al, 'X'
    mov ah, 0x0E
    int 0x10

    jmp CODE_SEG:0x1000

print_string:
    mov ah, 0x0E
.next:
    lodsb
    or al, al
    jz .done
    int 0x10
    jmp .next
.done:
    ret

load_kernel:
    mov ah, 0x02
    mov al, 20
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, 0x00
    mov es, bx
    xor bx, bx
    int 0x13
    jc $
    ret

msg_loading db "Loading kernel...", 0

gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

times 510-($-$$) db 0
dw 0xAA55