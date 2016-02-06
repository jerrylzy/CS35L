#!/bin/bash

option=$1

gcc -std=c99 -o sfrob sfrob.c
printf '*~BO *{_CIA *hXE]D *LER #@_GZY #E\\OX #^BO #FKPS #NEM\4' |
./sfrob | od -ta > sfrob_output.txt
diff -u sfrob_output.txt eggert_output_.txt

printf '*~BO *{_CIA *hXE]D *LER     #@_GZY #E\\OX #^BO #FKPS #NEM\4' |
./sfrob | od -ta > sfrob_output.txt
diff -u sfrob_output.txt eggert_output_.txt
rm sfrob_output.txt

space='./space.txt'
cat $space | ./sfrob > space_output.txt
diff -u space_output.txt empty.txt

empty='./empty.txt'
cat $empty | ./sfrob > empty_output.txt
diff -u empty_output.txt empty.txt

map='./maps'


cat $map | ./sfrob > map_orig_output.txt

if [ $? -ne 0 ]
then
   echo "Error occurred when reading $map"
fi

#cat map_orig_output.txt | od -ta > map_output.txt 

jar='./rt.jar' 

cat $jar | ./sfrob > jar_orig_output.txt

if [ $? -ne 0 ]
then
   echo "Error reading $jar"
fi

#cat jar_orig_output.txt | od -ta > jar_output.txt

if [ $# -eq 1 ]
then
    if [ $option -eq 1 ]
    then
	rm *_output.txt
    fi
fi

