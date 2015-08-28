.text
.global _start
.global sum
.code 32

_start:
 mov r0,#0
 mov r1,#0
 
sum:
  add r1,r1,#1
  add r0,r0,r1 
  cmp r1,#10
  beq sum_ok
  b sum
sum_ok:
  b  .
.end
  
  
