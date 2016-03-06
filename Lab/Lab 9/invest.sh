#!/usr/local/cs/bin/bash

cd /usr/bin

list=`ls | awk 'NR%101==404474229%101'`

for exe in $list
do
    if [ $1 -eq 1 ]
    then
	printf "$ ldd "
	echo $exe
    fi
    ldd $exe
done
