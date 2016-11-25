#!/bin/sh

#  BaSim_timer.sh
#
#  This script will measure the running time of BaSim, for one or several versions, and will store the information in a file. This will be useful to see how program speed scales with the size of the system.
#
#
#  Created by Manuel Lera Ramirez on 24/11/16.
#  Copyright © 2016 Manuel Lera Ramirez. All rights reserved.

# Run the program

BINFOLDER=././bin/
PROGRAM1=BaSim_old


#time $PROGRAM config.bs
touch results.txt
# Erase the file 
''>results.txt

for FILE in $(ls|grep config0)
do
	echo ${FILE} >> results.txt
    echo ${PROGRAM1} >> results.txt
	(time ${BINFOLDER}${PROGRAM1} ${FILE};) 2>> results.txt

    echo "\n" >> results.txt
done