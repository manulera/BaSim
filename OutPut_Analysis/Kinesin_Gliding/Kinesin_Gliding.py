

## import re
import numpy as np
from matplotlib import pyplot as plt

f = open("Output_objs.bs")

displacement_list = list()
for line in f.readlines():
    if line.find("mt1") != -1:
        raw = line.split(" ")
        displacement_list.append(float(raw[2]))

y = np.array(displacement_list)
y = 260 - y
plt.figure()

plt.plot(y)

plt.show()