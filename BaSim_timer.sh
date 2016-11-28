#!/bin/sh

#  BaSim_timer.sh
#
#  This script will measure the running time of BaSim, for one or several versions, and will store the information in a file. This will be useful to see how program speed scales with the size of the system.
#
#
#  Created by Manuel Lera Ramirez on 24/11/16.
#  Copyright © 2016 Manuel Lera Ramirez. All rights reserved.

# Run the program

BINFOLDER=../bin/
OLD=BaSim_old
B1=BaSim_1
B2=BaSim_2


#time $PROGRAM config.bs
touch results2.txt
# Erase the file
echo ''>results2.txt


ROUNDS=$(ls|grep config_2_0 -c)
echo $ROUNDS
COUNTER=1;
for FILE in $(ls|grep config_2_0)
do
	echo ${FILE} >> results2.txt

    echo ${OLD} >> results2.txt
	echo ${OLD}
	(time ${BINFOLDER}${OLD} ${FILE} 10;) 2>> results2.txt
	(time ${BINFOLDER}${OLD} ${FILE} 60;) 2>> results2.txt

    echo ${B1} >> results2.txt
	echo ${B1}
	(time ${BINFOLDER}${B1} ${FILE} 10;) 2>> results2.txt
	(time ${BINFOLDER}${B1} ${FILE} 60;) 2>> results2.txt

    echo ${B2} >> results2.txt
	echo ${B2}
	(time ${BINFOLDER}${B2} ${FILE} 10;) 2>> results2.txt
	(time ${BINFOLDER}${B2} ${FILE} 60;) 2>> results2.txt
    echo "\n" >> results2.txt
    echo "round "${COUNTER}" of "${ROUNDS}
    COUNTER=$((COUNTER+1))
done