#ifndef __Hf4StF__
#define __Hf4StF__
#include <iostream>



#define ROW_A 60
#define COL_A 60
typedef int d_in, d_out;
#define  N 1443
#define  M 1443
#define  L 61
//void  CSC_t( d_in ar_nz[N],d_in ar_row_idx[M], d_in ar_col_ptr[L], d_in B[COL_A], d_out C_H[ROW_A]);
void  Ordinary_SpMVM_t( d_in A[ROW_A][COL_A], d_in B[COL_A], d_out C_H[ROW_A]);
//void 	COO_t(d_in nz_val_A, d_in COO_row[N], d_in COO_col[N], d_in COO_val[N], d_out B[COL_A], d_in C_H[ROW_A]);
	

#endif
