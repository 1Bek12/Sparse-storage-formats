import time
from pynq import PL
import pynq

from pynq.overlay import Overlay
Ordinary = Overlay("./Simple.bit")
print("Done")
Ordinary
for i in Ordinary.ip_dict:
    print(i)
from pynq import allocate
import numpy as np
from numpy import loadtxt
A            = pynq.buffer.allocate(shape=(30,30), dtype=np.uint32)
B            = pynq.buffer.allocate(shape=(30,), dtype=np.uint32)
C            = pynq.buffer.allocate(shape=(30,), dtype=np.uint32)

A_loaded = loadtxt('./S.txt', dtype='int')


for i in range(30):
    for j in range(30):
        A[i][j]=A_loaded[i][j]
        

        
B[:]=1
C[:]=0
print(A)
print(B)
print(C)

A1=A.device_address
B1=B.device_address
C1=C.device_address

A.sync_to_device()
B.sync_to_device()
C.sync_to_device()

A.flush
B.flush
C.flush

print(time.time_ns())
Ordinary.Ordinary_SpMVM_t_0.s_axi_control.write(0x10,A1)
Ordinary.Ordinary_SpMVM_t_0.s_axi_control.write(0x18,B1)
Ordinary.Ordinary_SpMVM_t_0.s_axi_control.write(0x20,C1)
Ordinary.Ordinary_SpMVM_t_0.s_axi_control_signal.write(0x00,1)
print(time.time_ns())
print(C)

print(C)

C.freebuffer()
C[:]=0
print(C)
