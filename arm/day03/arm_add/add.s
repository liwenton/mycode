.text
.global _start
.global sum
.code 32

_start:
 mov r0,#0
 mov r1,#10
 
sum:
  add r0,r0,r1 
  sub r1,r1,#1
  cmp r1,#0
  beq sum_ok
  b sum
sum_ok:
  b  .
.end
  
  
