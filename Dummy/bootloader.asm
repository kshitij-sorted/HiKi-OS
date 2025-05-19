; After loading kernel into 0x1000, enable A20 and switch to 32-bit mode:
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
    ; Setup GDT
    lgdt [gdt_descriptor]

    ; Set PE bit in CR0
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump to flush pipeline
    jmp CODE_SEG:init_pm

init_pm:
    ; Setup segments
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Jump to kernel
    jmp CODE_SEG:0x1000

; GDT
gdt_start:
    dq 0x0000000000000000 ; null
    dq 0x00CF9A000000FFFF ; code segment
    dq 0x00CF92000000FFFF ; data segment
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10
