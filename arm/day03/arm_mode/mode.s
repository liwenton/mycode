.text
.global _start
.global
.code 32

_start:
    mrs r0,cpsr
    bic r0,r0,#0x60 
    
