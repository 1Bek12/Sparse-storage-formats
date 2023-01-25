import time
from pynq import PL
import pynq
from pynq.overlay import Overlay
CSR_F=Overlay("./CSR_120x120.bit")#with pipeline
print("Done")
for i in CSR_F.ip_dict:
    print(i)
from pynq import allocate
import numpy as np
from numpy import loadtxt
row_ptr = pynq.buffer.allocate(shape=(121,),  dtype=np.uint32)
col_id  = pynq.buffer.allocate(shape=(2905,), dtype=np.uint32)
val     = pynq.buffer.allocate(shape=(2905,), dtype=np.uint32)
B       = pynq.buffer.allocate(shape=(120,),  dtype=np.uint32)
C       = pynq.buffer.allocate(shape=(120,),  dtype=np.uint32)
r_ptr = loadtxt('./ar_row_ptr_CSR_120x120.txt', dtype='int')
c     = loadtxt('./ar_col_idx_CSR_120x120.txt', dtype='int')
v     = loadtxt('./ar_nz_CSR_120x120.txt',      dtype='int')
for i in range(121):
    row_ptr[i]= r_ptr[i]

for i in range(2905):
    col_id[i] = c[i]
    val[i]    = v[i]
    
B[:]=1
C[:]=0

print(B)
print(r_ptr)
print(col_id)
print(val)
row_ptr.sync_to_device()
col_id.sync_to_device()
val.sync_to_device()
B.sync_to_device()
C.sync_to_device()
row_ptr1= row_ptr.device_address
col_id1 = col_id.device_address
val1    = val.device_address
B1      = B.device_address
C1      = C.device_address
print(time.time_ns())
CSR_F.CSR_t_0.s_axi_control.write(0x10,val1)
CSR_F.CSR_t_0.s_axi_control.write(0x18, col_id1)
CSR_F.CSR_t_0.s_axi_control.write(0x20, row_ptr1)
CSR_F.CSR_t_0.s_axi_control.write(0x28, B1)
CSR_F.CSR_t_0.s_axi_control.write(0x30, C1)

print(time.time_ns())
CSR_F.CSR_t_0.s_axi_control_signals.write(0x00,1)
print(time.time_ns())

print(C)
