import numpy as np
import matplotlib.pyplot as plt
import math
import sys, os
        
path = os.path.dirname(sys.argv[0])

simdata=np.loadtxt(path+"/temp.txt")
t=simdata[:,0]
data0=simdata[:,0]
data1=simdata[:,1]
data2=simdata[:,2]
data3=simdata[:,3]

plt.plot(t,data0)
plt.plot(t,data1)
plt.plot(t,data2)
plt.plot(t,data3)

plt.savefig(path+'/temp.png')
quit()