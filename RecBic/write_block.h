#ifndef _WRITE_BLOCK_H
#define _WRITE_BLOCK_H

#include "struct.h"

/* from make_graph */
extern int col_width;
extern void seed_update (const discrete *s);
extern void seed_deduct (const discrete *s);

/* from cluster */
extern bits16 **profile;

/*char blockfn[LABEL_LEN];*/
FILE *fw;

void scan_block (bool *cond, Block *b_ptr);
void print_bc (FILE* fw, Block *b, int num);
void test_print(FILE* fw,Block *b,int num);
#endif
