.text
.global led_init
.global led_on
.global led_off
.code 32

led_init:
  @设置引脚模式
  ldr r0,=0xE0200280
  ldr r1,=0x00001111
  str r1,[r0]
 
  @设置上拉或者下拉
  ldr r2,=0xE0200288
  ldr r1,[r2]
  bic r1,r1,#0x0000000f
  str r1,[r2]
  mov pc ,lr

led_off:
  ldr r2,=0xE0200284
  orr r3,r3,#0x0f
  str r3,[r2]
  mov pc ,lr

led_on:
  ldr r2,=0xE0200284
  and r3,r3,#0x00
  str r3,[r2]
  mov pc ,lr

.end
