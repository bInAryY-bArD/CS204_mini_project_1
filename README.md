# --------------------------- CS204 Mini Project ---------------------------

By :  <br>
Akash (SPOC) &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp2022CSB1064 <br>
Aniket Kumar Sahil&nbsp&nbsp&nbsp2022CSB1067

## Introduction:
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

  ## PROCESS :
  The poject has been divided into various sub parts.
      
 ### Input - Output :
Here we just make a skeleton of taking input, separating terms and writing an output.

            >> Involves reading the given .asm file line by line
            >> separating the various terms (like the instructions, immediate values, registers, offset, etc.)
            >> Writing the output into a .mc file.

### Processing : 
            
  This is the main part of our project which involves converting to machine code. Also it keeps the track of the program counter(PC). 
  
            >> First it detects the format of instruction
            >> Then it converts the code into machine code accordingly.
            >> Then it saves the string within the 'converted_code' and update into the .mc file

## Memory Handling : 
  This part handles the assembly directives of the code. We maintain a separate .txt file telling us what is stored in the memory and where.
  These assembly directives don't get converted into a machine code, instead data gets updated in the memory.

            >> First it detects the assembly directive being used.
            >> Then it uploads the value accordingly in the memory.
            >> We maintain a separate pointer which points at the next usable memory byte
            >> Weincrement it accordingly as we keep on adding data.
            
