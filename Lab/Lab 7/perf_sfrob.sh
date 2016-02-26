#!/bin/bash

dir='./input_1000000'

echo "Default is 1000000 lines"

if [ $# -ne 0 ]
then
    if [ $1 -eq 1 ]
    then
	dir='./input_1000'
    elif [ $1 -eq 2 ]
    then
	dir='./input_10000'
    elif [ $1 -eq 3 ]
    then
	dir='./input_100000'
    elif [ $1 -eq 4 ]
    then
	dir='./input.txt'
    fi
fi

echo 'sfrob'
time ./sfrob < $dir > output_sfrob

echo 'sfrobu'
time ./sfrobu < $dir > output_sfrobu

rm output_sfrob*
