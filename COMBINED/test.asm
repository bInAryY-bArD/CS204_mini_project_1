.data
n : .dword 101 102 -1
i : .asciiz "Y e l l"
g : .word 378, 5, 7, 27 -1
G : .byte 88 8
e : .half 23, 43
r : .byte 32
.text
lb x4, 5(x4)
addi x3, x4, -5
add x5, x7, x8
lal:
ld x4, 0(x1)
lal_again:
and x5, x5, x3
add x1, x1, x1
lui x3, 840
sb x1 2(x4)
jal x9, die
beq x0, x0, lal
die:
