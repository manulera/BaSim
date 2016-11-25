
# This program measures the speed of the different programs for increasing number of objects in the BaSim simulation.
# Using several config files generated with preconfig.py, the different versions of the program are called and the time
# of execution is written in the file results.txt. From there, we can plot the information in Python.

# BaSim_Old: No change made
# BaSim_1: Changed that there is no iteration through MTs for bound motors
# BaSim_2: Now check first binding>random, then proceed with the within