.text
.global _start
.global store
.global load
.code 32
_start:
 mov r0,#0x00008e00
 mov r1,#1
 mov r3,#1
 mov r5,r0
 mov r6,r0
 bl store
 mov r0,#0x00008f00
 bl load
 b  .

store:
  str r1,[r5],#4
  cmp r1,#16
  add r1,r1,#1
  moveq pc,lr
  b store

load:
  ldr r2,[r6],#4
  str r2,[r0],#4
  cmp r3,#16
  add r3,r3,#1
  moveq pc,lr
  b load
  
@
.data
.space 1024
.end

