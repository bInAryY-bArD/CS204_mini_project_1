# ----------------------------- CS204 Mini Project -----------------------------

By :  Akash (SPOC)         2022CSB1064
      Aniket Kumar Sahil   2022CSB1067

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

  # PROCESS :
    The poject has been divided into various sub parts.
      
      ## Input - Output :
            
            >> Involves reading the given .asm file line by line
            >> separating the various terms (like the instructions, immediate values, registers, offset, etc.)
            >> Writing the output into a .mc file.
                  ** NOTE : Here we just make a skeleton of taking input, separating terms and writing an output.**

      ## Processing : 
            
            >> This is the main part of our project which involves converting to machine code.
            >> First it detects the format of instruction
            >> Then it converts the code into machine code accordingly.
            >> Then it saves the string within the 'converted_code' and update into the .mc file
