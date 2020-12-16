#include "trap.h"
   .set noat
   .globl main
   .text
main:
   li $t0, 4          #$at = 0x10101010
   mtc0 $t0 , $8
   mfc0 $t1 , $8
   HIT_GOOD_TRAP
   HIT_DECODE_TRAP 
