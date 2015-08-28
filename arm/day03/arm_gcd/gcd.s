.text
.global _start
.global gcd
.code 32

_start:
  mov r0,#20
  mov r1,#12
  bl gcd
  @R0,R1
  b  .
gcd:
  cmp r0,r1
  moveq pc,lr
  subcs r0,r0,r1
  subcc r1,r1,r0
  b gcd
.end
