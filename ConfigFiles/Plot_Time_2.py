
# This program measures the speed of the different programs for increasing number of objects in the BaSim simulation.
# Using several config files generated with preconfig.py, the different versions of the program are called and the time
# of execution is written in the file results.txt. From there, we can plot the information in Python.

# BaSim_Old: No change made
# BaSim_1: Changed that there is no iteration through MTs for bound motors
# BaSim_2: Now check first binding>random, then proceed with the within

# Every simulation is run 10 seconds and 60 seconds, to see the effects of the length of the simulation also
# (Once the steady state of the system is reached it shouldn't really matter)
# In this new version, also different binding affinities are used, to see if we see an effect


import re
from matplotlib import pyplot as plt
from matplotlib.lines import Line2D

f = open("results2.txt")

timelist = list()

for line in f.readlines():
    if line.find("real")!=-1:
        raw = line.split()
        times = re.split("[A-z]",raw[1])
        realtime = float(times[0])*60+float(times[1])
        timelist.append(realtime)

x = range(0,len(timelist)/12)

print len(x)
print len(timelist[0::12])

a = plt.axes()

a.plot(x,timelist[0::12],label="BaSim_old, bind 1")
a.plot(x,timelist[2::12],label="BaSim_1, bind 1")
a.plot(x,timelist[4::12],label="BaSim_2, bind 1")
a.plot(x,timelist[6::12],"--",label="BaSim_old, bind 3")
a.plot(x,timelist[8::12],"--",label="BaSim_1, bind 3")
a.plot(x,timelist[10::12],"--",label="BaSim_2, bind 3")
plt.legend()
plt.title("Simulation of 10 secs")

b = plt.figure()

plt.plot(x,timelist[1::12],label="BaSim_old, bind 1")
plt.plot(x,timelist[3::12],label="BaSim_1, bind 1")
plt.plot(x,timelist[5::12],label="BaSim_2, bind 1")
plt.plot(x,timelist[7::12],"--",label="BaSim_old, bind 3")
plt.plot(x,timelist[9::12],"--",label="BaSim_1, bind 3")
plt.plot(x,timelist[11::12],"--",label="BaSim_2, bind 3")
plt.legend()
plt.title("Simulation of 60 secs")
plt.show()
