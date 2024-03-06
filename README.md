-------------------------------------------------- CS204 Mini Project --------------------------------------------------

By :  Akash (SPOC)         2022CSB1064 \n
      \tAniket Kumar Sahil   2022CSB1067

The goal of the project is to create a RISCV assembler (like the one of Venus)
 it takes an assembly code from a .asm file as input and then generate its machine code in a .mc file as output.
  Our assembler supports 31 different instructions. These include :
   
     >> R format - add, and, or, sll, slt, sra, srl, sub, xor, mul, div, rem
     >> I format - addi, andi, ori, lb, ld, lh, lw, jalr
     >> S format - sb, sw, sd, sh
     >> SB format - beq, bne, bge, blt
     >> U format - auipc, lui
     >> UJ format - jal
     
  Additionaly, the it also supports the following assembler directives: 
                      
        >> .text        >> .data        >> .byte
        >> .half        >> .word
        >> .dword       >> .asciz

  PROCESS :
    The poject has been divided into various sub parts.
          
          # Input - Output :
            It involves reading the given .asm file line by line and then separating the various terms (like the instructions, immediate values, registers, offset, etc.)
            and then writing the output into a .mc file. Here we just make a skeleton of taking input, separating terms and writing an output.
          
          # Processing instructions :
            This part involves checking the instruction of each line 
      
        
