#include "trap.h"
   .set noat
   .globl main
   .globl func
   .text
main:
   li $s0, 4          #$at = 0x10101010
   li $s1, 8
   addi $t0 , $zero , 0x18
   mtc0 $t0, $14
   j func
   HIT_GOOD_TRAP		#stop temu
   
func:
   add $s2, $s1, $s0
   eret
   HIT_DECODE_TRAP
