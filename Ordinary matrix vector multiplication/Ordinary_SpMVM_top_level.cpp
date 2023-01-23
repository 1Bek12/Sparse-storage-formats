#include <iostream>
#include "Hf4StF.h"
#include <ap_axi_sdata.h>
#include <hls_stream.h>
void Ordinary_SpMVM_t(d_in A[ROW_A][COL_A], d_in B[COL_A] ,d_out C_H[ROW_A])
{

#pragma HLS INTERFACE mode=m_axi port=A   offset=slave
#pragma HLS INTERFACE mode=m_axi port=B   offset=slave
#pragma HLS INTERFACE mode=m_axi port=C_H offset=slave

#pragma HLS INTERFACE mode=s_axilite port=return bundle=control_signal


	Ordinary_SpMVM_t_label7:for(int i = 0; i < ROW_A; i++)
	{

      for(int j = 0; j < COL_A; j++)
		  {

		         C_H[i] = C_H[i] + A[i][j]*B[j];
		  }
    }
}
