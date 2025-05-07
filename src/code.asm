global _start

section .text
_start:
    mov byte [0x404034], 0x39
    push 0x40122a
    ret
