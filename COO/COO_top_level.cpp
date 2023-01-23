#include <iostream>
#include "Hf4StF.h"
#include <vector>
#include <ap_axi_sdata.h>
#include <hls_stream.h>

void COO_t(
		   d_in COO_row[N],
		   d_in COO_col[N],
		   d_in COO_val[N],
		   d_in B[COL_A],
		   d_in C_H[ROW_A])
{


#pragma HLS INTERFACE mode=m_axi      port=COO_row   offset=slave  bundle=A
#pragma HLS INTERFACE mode=m_axi      port=COO_col   offset=slave  bundle=A
#pragma HLS INTERFACE mode=m_axi      port=COO_val   offset=slave  bundle=A
#pragma HLS INTERFACE mode=m_axi      port=B         offset=slave  bundle=A
#pragma HLS INTERFACE mode=m_axi      port=C_H       offset=slave  bundle=A

#pragma HLS INTERFACE mode=s_axilite port=return bundle=control_signals

//#pragma HLS PIPELINE off

	int r=0, c=0, val=0;
	for(int i=0; i<nz_val_A_COO; i++)
	{
	    r=COO_row[i];
		c=COO_col[i];
		val=COO_val[i];
		C_H[r]=C_H[r]+val*B[c];
	}
}
