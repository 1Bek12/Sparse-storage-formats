#include <iostream>
#include "Hf4StF.h"
#include <ap_axi_sdata.h>
#include <hls_stream.h>

void ELL_t( d_in ELL_clm_indx[ROW_A][ELL_COL], d_in ELL_val[ROW_A][ELL_COL], d_in B[COL_A], d_out C_H[ROW_A] )

{
#pragma HLS PIPELINE off
#pragma HLS INTERFACE mode=m_axi port=ELL_clm_indx offset=slave
#pragma HLS INTERFACE mode=m_axi port=ELL_val      offset=slave
#pragma HLS INTERFACE mode=m_axi port=B            offset=slave
#pragma HLS INTERFACE mode=m_axi port=C_H          offset=slave

#pragma HLS INTERFACE mode=s_axilite port=return bundle=control

for(int i=0; i<ROW_A; i++)

{
#pragma HLS PIPELINE II=1
    for(int j=0; j<ELL_COL; j++)
    {
        int k=ELL_clm_indx[i][j];
        int val=ELL_val[i][j];
        C_H[i]=C_H[i]+val*B[k];

    }
}

}
