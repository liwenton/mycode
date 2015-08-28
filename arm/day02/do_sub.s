  .text
  .code 32
  .global do_sub

do_sub:
   mov  r0, #10
   mov  r1, #3
   sub  r0,r0,r1
   b   .
  
   .end
