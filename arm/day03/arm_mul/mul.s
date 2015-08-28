.text
.global _start
.global _mul

_start:
    mov r0,#1
    mov r1,#1
    mov r2,#4
    bl _mul
    b   .
_mul:
    add r1,r1,#1
    mul r0,r1,r0
    cmp r1,r2
    moveq pc,lr
    b _mul
.end
