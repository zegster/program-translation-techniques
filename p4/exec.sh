#!/bin/sh
## ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: run.sh
# Date: 5/10/2020
## ==================================================================================================== 

#Define usage message
USAGE="Usage: $0 [directory_name]"

#Check for correct number of agruments
if [ $# -lt 1 ]
then
    echo "$0: missing argument. Need to pass exactly one arguments"
    echo "$USAGE"
    echo "Exiting..."
    echo
    exit 1
fi

#Check for valid directory
if [ ! -d "$1" ]
then
	echo "$1 is not a directory. Exiting..."
	echo "$USAGE"
	echo
	exit 1
fi

#Loop through selected directory
for file in $1/*.asm
do
	echo
	echo "$file"
	./VirtMach "${file}"
done
exit 0

