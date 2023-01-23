#include <iostream>
#include "header_csr.h"
using namespace std;
void CSR_t( d_in ar_nz[M], d_in ar_col_idx[N], d_in ar_row_ptr[L], d_in B[COL_A], d_out C_H[ROW_A]){


//#pragma HLS INTERFACE mode=s_axilite              port=rwp
#pragma HLS INTERFACE mode=m_axi     offset=slave port=ar_nz
#pragma HLS INTERFACE mode=m_axi     offset=slave port=ar_col_idx
#pragma HLS INTERFACE mode=m_axi     offset=slave port=ar_row_ptr
#pragma HLS INTERFACE mode=m_axi     offset=slave port=B
#pragma HLS INTERFACE mode=m_axi     offset=slave port=C_H

#pragma HLS INTERFACE mode=s_axilite port=return  bundle=control_signals

for(int i = 0; i < n_rwp; i++)
{
     int row_start=0, row_end=0;
	 row_start=ar_row_ptr[i];
     row_end=ar_row_ptr[i+1];
     for(int k=row_start; k < row_end; k++)
     {
			int j=0;
			int val=0;
			j      =   ar_col_idx[k];
			val    =   ar_nz[k];

			C_H[i]=C_H[i]+B[j]*val;
		}
	}

}
