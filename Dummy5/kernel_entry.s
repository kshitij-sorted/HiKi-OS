.section .multiboot
.align 4
.long 0x1BADB002             # magic number
.long 0x00010003             # flags: align modules + memory info
.long -(0x1BADB002 + 0x00010003)  # checksum

.section .text
.global _start
_start:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss

    mov $stack_top, %esp

    call kernel_main

    cli
.halt:
    hlt
    jmp .halt

.section .bss
    .lcomm stack, 4096
stack_top:
