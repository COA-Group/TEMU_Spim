#include "trap.h"
   .set noat
   .globl main
   .text
main:
   lui $s0, 0x800a           
   lui $s1, 0x000c
   nop
   nop
   nop
   nop
   nop
   addi $s0, $s0, 0x000a
   addi $s1, $s1, 0x000c
   addi $s5, $zero, 5
   nop
   nop
   nop
   nop
   nop
   and $s2, $s0, $s1
   andi $s3, $s0, 0x800c
   andi $s4, $s0, 0x000c
   or $s2, $s0, $s1
   ori $s3, $s0, 0x800c
   ori $s4, $s0, 0x000c
   nor $s2, $s0, $s1
   xor $s2, $s0, $s1
   xori $s3, $s0, 0x800c
   xori $s4, $s0, 0x000c
   sll $s2, $s0, 5
   sllv $s2, $s0, $s5
   sra $s3, $s0, 5
   srav $s3, $s0, $s5
   sra $s2, $s1, 5
   srav $s2, $s1, $s5
   srl $s3, $s0, 5
   srlv $s3, $s0, $s5
   srl $s2, $s1, 5
   srlv $s2, $s1, $s5


   HIT_GOOD_TRAP		#stop temu
   HIT_DECODE_TRAP
