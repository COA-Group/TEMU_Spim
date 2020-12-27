#include "trap.h"
   .set noat
   .globl main
   .globl func
   .text
main:
   li $s0, 4          #$at = 0x10101010
   sw $s0, 0($zero)
   li $s1, 8
   sw $s1, 4($zero)
   addi $t0 , $zero , 0x18
   jal func
   HIT_GOOD_TRAP		#stop temu
   
func:
   lw $t0, 0($zero)
   lw $10, 4($zero)
   jr $ra
   HIT_DECODE_TRAP
