    .text

    .global install_vector_handler
install_vector_handler:

    ldr  r0, =vector_start
    ldr  r1, =vector_end
    mov  r2, #0

install_copy_loop:
    ldr r3, [r0], #4
    str r3, [r2], #4
    cmp r0, r1
    ble	install_copy_loop
    mov  pc, lr

vector_start:
    ldr pc, _reset_hdl
    ldr pc, _und_hdl
    ldr pc, _swi_hdl
    ldr pc, _pabt_hdl
    ldr pc, _dabt_hdl
    b .
    ldr pc, _irq_hdl
    ldr pc, _fiq_hdl


    .extern start
_reset_hdl:
    .word  start

_und_hdl:
    .word  _und_handler

_swi_hdl:
    .word _swi_handler

_pabt_hdl:
    .word _pabt_handler

_dabt_hdl:
    .word _dabt_handler

_irq_hdl:
    .word _irq_handler

_fiq_hdl:
    .word _fiq_handler

vector_end:
  

_und_handler:
   b   .

_pabt_handler:
   b   .


_dabt_handler:
   b   .

   .extern c_irq_handler
_irq_handler:
    sub   lr, lr, #4
    stmfd sp!, {r0-r12,lr}

    @bl  c_irq_handler

    ldmfd sp!,{r0-r12,pc}^


_fiq_handler:
   b  .

   .global _swi_handler
_swi_handler:
    stmfd sp!,{r0-r12,lr}

    mrs  r4, spsr
    tst  r4, #0x20
    ldrneh r0, [lr, #-2]
    bicne  r0, r0, #0xFF00
    ldreq  r0, [lr, #-4]
    biceq  r0, r0, #0xFF000000

    bl c_swi_handler


    ldmfd sp!,{r0-r12,pc}^


	.global swi_test1
swi_test1:
    stmfd sp!, {lr}
    swi 1
    ldmfd sp!, {pc}

	.global swi_test2
swi_test2:
    stmfd sp!, {lr}
    swi 2
    ldmfd sp!, {pc}

