#include "trap.h"
   .set noreorder
   .globl main
   .text
main:
   ori $v0, $zero, 0x100    # $v0 = 256(0x100)
   ori $v1, $zero, 0x99     # $v1 = 153(0x99)
   div $v0, $v1             #  hi = 103(0x67)
                            #  lo = 1(0x1)
   mfhi $a0                 # $a0 = hi = 103(0x67)
   mflo $a1                 # $a1 = lo = 1(0x1)
   nop
   HIT_GOOD_TRAP
   HIT_DECODE_TRAP 
