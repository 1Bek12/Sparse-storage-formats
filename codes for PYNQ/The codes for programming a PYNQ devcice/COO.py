import time
from pynq import PL
import pynq
from pynq.overlay import Overlay
ol = Overlay("./COO_30_60.bit")
print("Done")
ol.is_loaded()
for i in ol.ip_dict:
    print(i)
    from pynq import allocate
import numpy as np
from numpy import loadtxt
row_COO = allocate(shape=(347,), dtype=np.uint32)
col_COO = allocate(shape=(347,), dtype=np.uint32)
val_COO = allocate(shape=(347,), dtype=np.uint32)
B       = allocate(shape=(30, ), dtype=np.uint32)
C       = allocate(shape=(30, ), dtype=np.uint32)
r = loadtxt('./COO_row_indx_30.txt', dtype='int')
c = loadtxt('./COO_col_indx_30.txt', dtype='int')
v = loadtxt('./COO_val_30.txt',      dtype='int')
for i in range(347):
    row_COO[i]=r[i]
    col_COO[i]=c[i]
    val_COO[i]=v[i]
    
B[:]=1
C[:]=0
print(row_COO)
row_COO.sync_to_device()
col_COO.sync_to_device
row_COO1  =  row_COO.device_address
col_COO1  =  col_COO.device_address
val_COO1  =  val_COO.device_address
B1        =  B.device_address

C1        =  C.device_address
print(time.time_ns())
ol.COO_t_0.s_axi_control.write(0x10,row_COO1)
ol.COO_t_0.s_axi_control.write(0x18,col_COO1)
ol.COO_t_0.s_axi_control.write(0x20,val_COO1)
ol.COO_t_0.s_axi_control.write(0x28,B1)
ol.COO_t_0.s_axi_control.write(0x30,C1)
print(time.time())
ol.COO_t_0.s_axi_control_signals.write(0x00,1)
print(time.time_ns())
print(C)
