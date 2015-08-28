.text
.global _start
.global _cmp
.code 32

_start:
  ldr r0,=str1
  ldr r1,=str2
  bl _cmp
  b  .

_cmp:
  ldrb r2,[r0],#1
  ldrb r3,[r1],#1
  cmp r2,#0
  beq unfit
  cmp r2,r3
  beq _cmp
   
unfit:
  cmp r3,r2
  moveq pc,lr
  b  .  
str1:
  .ascii"ABC\0"
str2:
  .asciz"ABCD"
.end
