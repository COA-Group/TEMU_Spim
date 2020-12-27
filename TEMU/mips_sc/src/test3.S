#include "trap.h"
   .set noat
   .globl main
   .text
main:
   addi $s0, $zero, 0x3ca5           
   addi $s1, $zero, 0xa53c
   addi $s2, $zero, 4
   nop
   nop
   nop
   nop
   nop
   sb $s0, 0($zero)
   sb $s0, 1($zero)
   sb $s0, -2($s2)
   sb $s1, -1($s2)
   sh $s1, 0($s2)
   sh $s0, 2($s2)
   sw $s0, 4($s2)
   lb $s3, 1($zero)
   lb $s4, -1($s2)
   lbu $s3, 1($zero)
   lbu $s4, -1($s2)
   lh $s3, 0($s2)
   lh $s4, 2($s2)
   lhu $s3, 0($s2)
   lhu $s4, 2($s2)
   lw $s3, 4($s2)
   mthi $s0
   nop
   nop
   nop
   nop
   nop
   mtlo $s0
   nop
   nop
   nop
   nop
   nop
   mfhi $s5
   mflo $s6
   nop
   nop
   nop
   nop
   nop
   add $s7, $s5, $s6


   HIT_GOOD_TRAP		#stop temu
   HIT_DECODE_TRAP
