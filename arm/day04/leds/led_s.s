.text
.global led_main
.code 32

led_main:
  @设置引脚模式
  ldr r0,=0xE0200280
  ldr r1,=0x00001111
  str r1,[r0]
 
  @设置上拉或者下拉
  ldr r2,=0xE0200288
  ldr r1,[r2]
  bic r1,r1,#0x0000000f
  str r1,[r2]
 
  ldr r2,=0xE0200284
  ldr r3,[r2]

loop:
  orr r3,r3,#0x0f
  str r3,[r2]
  bl delay
  and r3,r3,#0x00
  str r3,[r2]
  bl delay
  b loop

delay:
  mov r0,#0xF00000
delay_loop:
  subs r0,r0,#1
  bne delay_loop
  mov pc,lr

.end
