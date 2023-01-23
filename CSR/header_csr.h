#ifndef __header_csr__
#define __header_csr__
#include <iostream>



#define ROW_A 30
#define COL_A 30
typedef int d_in;
typedef int d_out;
#define  N 269  //number of non-zero elements
#define  M 269  //number of non-zero elements
#define  L 31 //number of row pointer
#define n_rwp 30
void  CSR_t( d_in ar_nz[M],d_in ar_col_idx[N], d_in ar_row_ptr[L], d_in B[COL_A], d_in C_H[ROW_A]);


#endif
