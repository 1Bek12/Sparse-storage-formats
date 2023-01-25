import time
from pynq import PL
import pynq
from pynq.overlay import Overlay
CSC_F=Overlay("./CSC_top_120x120.bit")#with pipeline
print("Done")
CSC_F=Overlay("./CSC_top_without_pipeline.bit")
print("Done")
for i in CSC_F.ip_dict:
    print(i)

from pynq import allocate
import numpy as np
from numpy import loadtxt  
col_ptr = pynq.buffer.allocate(shape=(121,),  dtype=np.uint32)
row_id  = pynq.buffer.allocate(shape=(2905,), dtype=np.uint32)
val     = pynq.buffer.allocate(shape=(2905,), dtype=np.uint32)
B       = pynq.buffer.allocate(shape=(121,),  dtype=np.uint32)
C       = pynq.buffer.allocate(shape=(121,),  dtype=np.uint32)
c_ptr = loadtxt('./ar_col_ptr_CSC_120x120.txt', dtype='int')
r     = loadtxt('./ar_row_idx_CSC_120x120.txt', dtype='int')
v     = loadtxt('./ar_nz_CSC_120x120.txt',      dtype='int')
for i in range(121):
    col_ptr[i]= c_ptr[i]

for i in range(2905):
    row_id[i] = r[i]
    val[i]    = v[i]
    
B[:]=1
C[:]=0

print(B)
print(col_ptr)
col_ptr.sync_to_device()
row_id.sync_to_device()
val.sync_to_device()
B.sync_to_device()
C.sync_to_device()

col_ptr1 = col_ptr.device_address
row_id1  = row_id.device_address
val1     = val.device_address
B1       = B.device_address
C1       = C.device_address
print(time.time_ns())


CSC_F.CSC_t_0.s_axi_control.write(0x10,val1)
CSC_F.CSC_t_0.s_axi_control.write(0x18,row_id1)
CSC_F.CSC_t_0.s_axi_control.write(0x20,col_ptr1)
CSC_F.CSC_t_0.s_axi_control.write(0x28,B1)
CSC_F.CSC_t_0.s_axi_control.write(0x30,C1)
CSC_F.CSC_t_0.s_axi_control_signals.write(0x00,1)

print(time.time_ns())
print(C)
