#ifndef __ITYPE_H__
#define __ITYPE_H__

make_helper(lui);
decode_helper(d_lui);

make_helper(ori);
decode_helper(d_ori);

make_helper(andi);
decode_helper(d_andi);

make_helper(xori);
decode_helper(d_xori);

make_helper(lb);
decode_helper(d_lb);

make_helper(lbu);
decode_helper(d_lbu);

make_helper(lh);
decode_helper(d_lh);

make_helper(lhu);
decode_helper(d_lhu);

make_helper(lw);
decode_helper(d_lw);

make_helper(sb);
decode_helper(d_sb);

make_helper(sh);
decode_helper(d_sh);

make_helper(sw);
decode_helper(d_sw);

make_helper(addi);
decode_helper(d_addi);

make_helper(addiu);
decode_helper(d_addiu);

make_helper(slti);
decode_helper(d_slti);

make_helper(sltiu);
decode_helper(d_sltiu);

make_helper(beq);
decode_helper(d_beq);

make_helper(g);
decode_helper(d_g);

make_helper(bgtz);
decode_helper(d_bgtz);

make_helper(blez);
decode_helper(d_blez);

make_helper(bne);
decode_helper(d_bne);
#endif
