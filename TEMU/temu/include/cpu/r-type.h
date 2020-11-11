#ifndef __RTYPE_H__
#define __RTYPE_H__

make_helper(and);
decode_helper(d_and);

make_helper(or);
decode_helper(d_or);

make_helper(nor);
decode_helper(d_nor);

make_helper(xor);
decode_helper(d_xor);

make_helper(sllv);
decode_helper(d_sllv);

make_helper(sll);
decode_helper(d_sll);

make_helper(srav);
decode_helper(d_srav);

make_helper(sra);
decode_helper(d_sra);

make_helper(srlv);
decode_helper(d_srlv);

make_helper(srl);
decode_helper(d_srl);

make_helper(mfhi);
decode_helper(d_mfhi);

make_helper(mflo);
decode_helper(d_mflo);

make_helper(mthi);
decode_helper(d_mthi);

make_helper(mtlo);
decode_helper(d_mtlo);

make_helper(add);
decode_helper(d_add);

make_helper(addu);
decode_helper(d_addu);

make_helper(sub);
decode_helper(d_sub);

make_helper(subu);
decode_helper(d_subu);

make_helper(slt);
decode_helper(d_slt);

make_helper(sltu);
decode_helper(d_sltu);

make_helper(mult);
decode_helper(d_mult);

make_helper(multu);
decode_helper(d_multu);

#endif
