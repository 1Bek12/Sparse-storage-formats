#include <iostream>
#include "Hf4StF.h"


void CSC_t(  d_in ar_nz[N],d_in ar_row_idx[M], d_in ar_col_ptr[L], d_in B[COL_A], d_out C_H[ROW_A])
{


#pragma HLS INTERFACE mode=m_axi     offset=slave port=ar_nz
#pragma HLS INTERFACE mode=m_axi     offset=slave port=ar_row_idx
#pragma HLS INTERFACE mode=m_axi     offset=slave port=ar_col_ptr
#pragma HLS INTERFACE mode=m_axi     offset=slave port=B
#pragma HLS INTERFACE mode=m_axi     offset=slave port=C_H

#pragma HLS INTERFACE mode=s_axilite port=return  bundle=control_signals
//int clp=121;
	    int col_start=0, col_end=0;


		for(int i = 0; i < n_clp; ++i)
		{
			col_start = ar_col_ptr[i]  ;
			col_end   = ar_col_ptr[i+1];
			//std::cout << "nz_start: "<<col_start<<std::endl;
			//std::cout << "nz_end: "  <<col_end  <<std::endl;
	        for(int nz_id = col_start; nz_id < col_end; ++nz_id)
	        {

	        	  int j=0;
	        	  int val=0;
	              j=ar_row_idx[nz_id];
	              val=ar_nz[nz_id];
	              C_H[j]=C_H[j]+val*B[i];
	              //std::cout << "value: "<<val<<std::endl;
	              //std::cout << "B[i]: "<<B[i]<<std::endl;
	              //std::cout << "C[j]: "<<C_H[j]<<std::endl;
	        }

		}

}
