//addadd
#include "../TEMU/temu/include/temu.h"
#include "stdlib.h"
#include <sys/types.h>
#include <regex.h>


enum {
    NOTYPE = 256, //spaces
    NUM,          //decimal number 十进制
    HEX,          //hexadecimal number 十六进制0x开头
    REG,          //reg name 寄存器 $开头

    LBK,
    RBK,

    EQ,           //equal
    NEQ,          //not equal

    AND,          //与
    OR,           //或
    ADD,
    REV,
    SLH,
    SUB,          //-
    STAR          //*
};

static struct rule {
    char *regex;
    int token_type;
} rules[] = {
    {"\\b0[xX][0-9a-fA-F]+\\b",HEX},      // hexadecimal number
    {"\\$(zero|at|v0|v1|a0|a1|a2|a3|t0|t1|t2|t3|t4|t5|t6|t7|s0|s1|s2|s3|s4|s5|s6|s7|t8|t9|k0|k1|gp|sp|fp|ra|pc)",REG},                 // reg name
    {"!=",NEQ},                           // not equal
    {"&&",AND},                           // and
    {"\\|\\|",OR},                         // or
    {" +",	NOTYPE},		      // spaces
    {"==", EQ},			      // equal
    {"\\+",ADD},                          // add
    {"-",SUB},                            // sub
    {"\\*",STAR},                          // multi
    {"/",SLH},                            // divide
    {"\\(",LBK},                          // left bracket
    {"\\)",RBK},                          // right bracket
    {"\\b[0-9]+\\b",NUM},               // number
    {"!",REV}                          //
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

void init_regex() {
    int i;
    char error_msg[128];
    int ret;

    for(i = 0; i < NR_REGEX; i ++) {
        ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
        if(ret != 0) {
            regerror(ret, &re[i], error_msg, 128);
            Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
        }
    }
}

typedef struct token {
    int type;
    char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
    int position = 0;
    int i;
    regmatch_t pmatch;
    nr_token = 0;
    while(e[position] != '\0') {//check all token
        for(i = 0; i < NR_REGEX; i ++) {//for a token, check all roles
            if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {//the token is valid
                char *substr_start = e + position;
                int substr_len = pmatch.rm_eo;
                position += substr_len;
                switch(rules[i].token_type) {//confirm token type
                    case NOTYPE: break;
                    case NUM: case HEX: case REG:
                        sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
                    default:
                        tokens[nr_token].type = rules[i].token_type;
                        nr_token ++;
                }
                break;
            }
        }
        if(i == NR_REGEX) {//invalid token, return failed
            printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
            return false;
        }
    }
    return true;
}

bool check_parentheses(int p, int q) {
    if (tokens[p].type == LBK && tokens[q].type == RBK) {//there are a pair of brackets
        int buf[32];
        int i, j = 0, rec = -1;
        for (i = p; i <= q; i++) {//Make sure the brackets appear in pairs
            if (tokens[i].type == LBK) buf[j++] = i;
            else if (tokens[i].type == RBK) {
                if (j == 0) return false;
                rec = buf[--j];
            }
        }
        if (rec == p) return true;
    }
    return false;//not in pairs
}

int find_domn(int p, int q) {
    int i;
    int bracket_level = 0;
    int dominated_op = -1;
    for(i = p; i <= q; i ++) {//check all tokens
        switch(tokens[i].type) {//check the caculate level by token type
            case REG: case NUM: case HEX: break;
            case LBK:
                bracket_level ++;
                break;
            case RBK:
                bracket_level --;
                if(bracket_level < 0) {
                    return 0;
                }
                break;
            case STAR:
                if(tokens[i-1].type > REG //'token before '*' is not a number'
                    || i == 0) {//'*' is the first token
                    //this is a pointer token , not a multiplication token
                    if(tokens[i+1].type != LBK//not like *(<< expr >>)
                            && q-p != 1){//not like *(num|hex|reg)
                        //pointer token don't need to calculate
                        break;
                    }
                }
            case SUB:
                if(tokens[i-1].type > REG //'token before '-' is not a number'
                    || i == 0) {//'-' is the first token
                    //this is a negative token , not a sub token
                    if(tokens[i+1].type != LBK//not like - ( << expr >> )
                            && q-p != 1){//not like - (num|hex|reg)
                        //negative token don't need to calculate
                        break;
                    }
                }
            default:
                if(bracket_level == 0) {
                    if(dominated_op == -1) {
                        dominated_op = i;
                    }
                }
                break;
        }
    }
    return dominated_op;
}

int eval(int p, int q) {
    if (p > q) {// bad expression!
        assert(0);
    }
    else if (p == q) {// this is a value or a register
        switch (tokens[p].type) {//find result by the given token
            //char* rec = NULL;
            char temp[6];
            case NUM:
                return atoi(tokens[p].str);
            case HEX:
                return strtol(tokens[p].str, NULL, 16);
            case REG:
                strcpy(temp, tokens[p].str);
                for(int i = 0 ; i < 32 ; i++){
                    if(!strncmp(temp , regfile[i] , strlen(regfile[i]))){
                        return reg_w(i);
                    }
                }
                if (!strncmp(temp, "$pc" , 3)) return cpu.pc;
        }
    }
    else if (check_parentheses(p, q) == true) return eval(p + 1, q - 1);//there are a pair of brackets
    else {//need to calculate
        int op = find_domn(p, q);
        if (tokens[op].type == '!') {
            uint32_t val= eval(op + 1, q);
            return !val;
        }
        if (tokens[op].type == SUB
            && (tokens[op-1].type > REG ||//'token before '-' is not a number'
                op == 0)) {//'-' is the first token
            uint32_t val= eval(op + 1, q);
            return -val;
        }
        if (tokens[op].type == STAR
            && (tokens[op-1].type > REG ||//'token before '*' is not a number'
                op == 0)) {//'*' is the first token
            uint32_t val= eval(op + 1, q);
            return mem_read(val , 4);
        }
        int eval1 = eval(p, op - 1);
        int eval2 = eval(op + 1, q);
        switch(tokens[op].type) {
            case ADD: return eval1 + eval2;
            case SUB: return eval1 - eval2;
            case STAR: return eval1 * eval2;
            case SLH: return eval1 / eval2;
            case AND: return eval1 && eval2;
            case OR:  return eval1 || eval2;
            case EQ: return eval1 == eval2;
            case NEQ: return eval1 != eval2;
            default: assert(0);
        }
    }
    return 0;
}

uint32_t expr(char *e, bool *success) {
    if(!make_token(e)) {
        *success = false;
        return 0;
    }
       *success =true;
    int ret = 0;
    ret = eval(0 , nr_token-1);
    return ret;
}

