#include "trap.h"
   .set noat
   .globl main
   .text
main:
   lui $s0, 0xabcd 
   lui $s1, 0x1234
   lui $s2, 0x000a
   lui $s3, 0xff12   
   nop
   nop
   nop
   nop
   nop       
   ori $s0, $s0, 0xabcd
   ori $s1, $s1, 0x1234
   ori $s2, $s2, 0x000a
   ori $s3, $s3, 0x0001
   nop
   nop
   nop
   nop
   nop
   multu $s1, $s2
   addu $t0, $s0, $s1
   addi $t1, $s0, 0xffff
   xor $t2, $s0, $s1
   srl $t3, $s0, 5
   sh $s1, 0($0)
   sb $s0, 2($0)
   sb $s2, 3($0)
   mtlo $t0
   mfhi $t4
   nop
   nop
   nop
   nop
   nop
   slt $t5, $t4, $t1
   lw $t6, 0($0)
   nop
   nop
   nop
   nop
   nop
   sub $t7, $t6, $t5
   
   
   HIT_GOOD_TRAP		#stop temu
   HIT_DECODE_TRAP
