    .text 
    .code 32
    .global a_strcmp

@输入参数：
@r0 :字符串1地址
@r1 :字符串2地址
@
@输出参数:
@r0 : 0     两个字符串相等
@   : 非零  两个字符串不相等
a_strcmp:

cmp_loop:
    ldrb  r2, [r0], #1
    ldrb  r3, [r1], #1
    cmp   r2, #0
    beq   str1_end
    cmp   r2, r3
    beq   cmp_loop
str1_end:
    sub   r0, r2, r3
    mov   pc, lr

    .end 
