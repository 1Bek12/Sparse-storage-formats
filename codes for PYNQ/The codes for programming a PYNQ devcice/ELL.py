import time
import numpy as np
import os, warnings
from pynq import PL
import pynq
from pynq.overlay import Overlay
ol = Overlay("./ELL_30x30.bit")
print("Done")
ol?
for i in ol.ip_dict:
    print(i)
    from pynq import allocate
import numpy as np
from numpy import loadtxt

ELL_col_indx = pynq.buffer.allocate(shape=(30,20), dtype=np.uint32)
ELL_val      = pynq.buffer.allocate(shape=(30,20), dtype=np.uint32)
B            = pynq.buffer.allocate(shape=(30,), dtype=np.uint32)
C            = pynq.buffer.allocate(shape=(30,), dtype=np.uint32)
ELL_v = loadtxt('./ELL_val.txt', dtype='int')
ELL_c = loadtxt('./ELL_col.txt', dtype='int')

for i in range(30):
    for j in range(20):
        ELL_col_indx[i][j]=ELL_c[i][j]
        
for i in range(30):
    for j in range(20):
        ELL_val[i][j]=ELL_v[i][j]
        
B[:]=1
C[:]=0
ELL_col_indx1=ELL_col_indx.device_address
ELL_val1=ELL_val.device_address
B1=B.device_address
C1=C.device_address
ELL_col_indx.sync_to_device()
ELL_val.sync_to_device
B.sync_to_device()
C.sync_to_device()
print(time.time_ns())
ol.ELL_t_0.s_axi_control.write(0x10,ELL_col_indx1)
ol.ELL_t_0.s_axi_control_r.write(0x18,ELL_val1)
ol.ELL_t_0.s_axi_control_r.write(0x20,B1)
ol.ELL_t_0.s_axi_control_r.write(0x28,C1)
print(time.time_ns())
ol.ELL_t_0.s_axi_control.write(0x00,1)
print(time.time_ns())
print(C)
