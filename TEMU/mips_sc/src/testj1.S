#include "trap.h"
   .set noat
   .globl main
   .globl label1
   .globl label2
   .globl label3
   .globl label4
   .globl label5
   .globl label6
   .text
main:
   li $s0, 4          #$at = 0x10101010
   li $t0, 8
   addi $s0 , $s0 , -1
   bltz $s0, label1
   jr $t0
   
label1:
   li $s1, -4          #$at = 0x10101010
   li $t1, 36
   addi $s1 , $s1 , 1
   bgez $s1, label2
   jalr $t1
   
label2:
   li $s2, 4          #$at = 0x10101010
   addi $s2 , $s2 , -1
   blez $s2, label3
   j label2+4

label3:
   li $s3, -4          #$at = 0x10101010
   addi $s3 , $s3 , 1
   bgtz $s3, label4
   j label3+4

label4:
   li $s4, -4    
   addi $s4 , $s4 , 1
   bne $s4, $zero ,label4+4
   
label5:
   li $s5, -4          #$at = 0x10101010
   addi $s5 , $s5 , 1
   beq $s5, $zero ,label6
   j label5+4

label6:
   HIT_GOOD_TRAP
   HIT_DECODE_TRAP 
