#include "trap.h"
   .set noat
   .globl main
   .text
main:
   lui $s0, 0xffff 
   lui $s1, 0x0001
   lui $s6, 0x0002
   lui $s7, 0xfffe   
   nop
   nop
   nop
   nop
   nop       
   add $s2, $s0, $s1
   add $s2, $s6, $s1
   add $s2, $s0, $s7
   addi $s3, $s0, 0xffff
   addi $s3, $s0, 0x0001
   addi $s3, $s1, 0x0001
   addu $s4, $s0, $s1
   addu $s4, $s6, $s1
   addu $s4, $s0, $s7
   addiu $s5, $s0, 0x0001
   addiu $s5, $s0, 0xffff
   addiu $s5, $s1, 0x0001
   sub $s2, $s0, $s1
   sub $s2, $s0, $s7
   sub $s2, $s1, $s0
   subu $s3, $s0, $s1
   subu $s3, $s0, $s7
   subu $s3, $s1, $s7
   slt $s4, $s0, $s1
   slti $s5, $s0, 0x0001
   sltu $s4, $s0, $s1
   sltiu $s5, $s0, 0x0001
   mult $s0, $s1
   mfhi $t0
   mflo $t1
   multu $s0, $s1
   mfhi $t2
   mflo $t3
   


   HIT_GOOD_TRAP		#stop temu
   HIT_DECODE_TRAP
