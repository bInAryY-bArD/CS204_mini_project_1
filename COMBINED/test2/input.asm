.data
n : .byte 3
.text
lui x20 65536
addi x20 x20 4
auipc x3 65536
lb x3 -8(x3)
addi x4, x0, 10
addi x5, x0, 11
addi x6, x0, 12
jal x1, func
beq x0, x0, exit
func:
addi x2, x2, -8
sw x1, 4(x2)
sb x3, 3(x2)
sb x4, 2(x2)
sb x5, 1(x2)
sb x6, 0(x2)
addi x7, x0, 1
bne x3, x7, label
add x8, x5, x0
addi x31, x0, 4
sll x4, x4, x31
add x8, x8, x4
addi x31, x0, 8
sll x3, x3, x31
add x8, x8, x3
sw x8, 0(x20)
addi x20, x20, 4
lw x1, 4(x2)
addi x2, x2, 8
jalr x0, x1, 0
label:
addi x3, x3, -1
lb x5, 0(x2)
lb x6, 1(x2)
jal x1, func
lb x3, 3(x2)
lb x5, 1(x2)
lb x4, 2(x2)
add x8, x5, x0
addi x31, x0, 4
sll x4, x4, x31
add x8, x8, x4
addi x31, x0, 8
sll x3, x3, x31
add x8, x8, x3
sw x8, 0(x20)
addi x20, x20, 4
lb x3, 3(x2)
addi x3, x3, -1
lb x4, 0(x2)
lb x5, 1(x2)
lb x6, 2(x2)
jal x1, func
lw x1, 4(x2)
addi x2, x2, 8
jalr x0, x1, 0
exit:
