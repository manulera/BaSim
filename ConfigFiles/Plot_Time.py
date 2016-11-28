
# This program measures the speed of the different programs for increasing number of objects in the BaSim simulation.
# Using several config files generated with preconfig.py, the different versions of the program are called and the time
# of execution is written in the file results.txt. From there, we can plot the information in Python.

# BaSim_Old: No change made
# BaSim_1: Changed that there is no iteration through MTs for bound motors
# BaSim_2: Now check first binding>random, then proceed with the within

# Every simulation is run 10 seconds and 60 seconds, to see the effects of the length of the simulation also
# (Once the steady state of the system is reached it shouldn't really matter)
import re
from matplotlib import pyplot as plt
f = open("results.txt")

timelist = list()

for line in f.readlines():
    if line.find("real")!=-1:
        raw = line.split()
        times = re.split("[A-z]",raw[1])
        realtime = float(times[0])*60+float(times[1])
        timelist.append(realtime)

x = range(0,len(timelist)/6)

print len(x)
print len(timelist[0::6])
plt.figure()

plt.plot(x,timelist[0::6],label="BaSim_old")
plt.plot(x,timelist[2::6],label="BaSim_1")
plt.plot(x,timelist[4::6],label="BaSim_2")
plt.legend()

plt.figure()

plt.plot(x,timelist[1::6],label="BaSim_old")
plt.plot(x,timelist[3::6],label="BaSim_1")
plt.plot(x,timelist[5::6],label="BaSim_2")
plt.legend()

plt.show()
