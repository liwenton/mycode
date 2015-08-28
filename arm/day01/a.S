	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"hello.c"
	.text
	.align	2
	.global	func
	.type	func, %function
func:
	.fnstart
.LFB0:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	.save {fp}
.LCFI0:
	.setfp fp, sp, #0
	add	fp, sp, #0
.LCFI1:
	.pad #20
	sub	sp, sp, #20
.LCFI2:
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	str	r2, [fp, #-16]
	ldr	r3, [fp, #-12]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-12]
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.LFE0:
	.fnend
	.size	func, .-func
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
.LCFI3:
	.setfp fp, sp, #4
	add	fp, sp, #4
.LCFI4:
	mov	r0, #10
	mov	r1, #20
	mov	r2, #30
	bl	func
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp!, {fp, pc}
.LFE1:
	.fnend
	.size	main, .-main
	.ident	"GCC: (Sourcery G++ Lite 2009q3-67) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
