#include "trap.h"
   .set noat
   .globl main
   .text
main:
   lui $s0, 0xfffa 
   lui $s1, 0x0001
   lui $s6, 0x0008
   lui $s7, 0xff4e   
   nop
   nop
   nop
   nop
   nop       
   add $s2, $s0, $s1
   sub $s3, $s7, $s6
   mult $s0, $s1
   nop
   nop
   sltu $s4, $s2, $s3
   and $s5, $s2, $s0
   xori $s2, $s3, 0xabcd
   mflo $s3
   sll $s3, $s7, 3
   sra $s4, $s7, 8
   sw $s0, 0($0)
   mfhi $s2
   nop
   nop
   nop
   nor $s5, $s3, $s4
   lhu $s3, 2($0)
   lbu $s4, 1($0)
   nop
   nop
   nop
   nop
   add $s2, $s3, $s4
   slt $s5, $s3, $s4
   
   
   HIT_GOOD_TRAP		#stop temu
   HIT_DECODE_TRAP
