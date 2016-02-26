#!/bin/bash

gcc -std=c99 -O2 -o sfrob sfrob.c
gcc -std=c99 -O2 -o sfrobu sfrobu.c
printf '*~BO *{_CIA *hXE]D *LER #@_GZY #E\\OX #^BO #FKPS #NEM\4' | ./sfrobu | od -ta > output_sfrobu

printf '*~BO *{_CIA *hXE]D *LER #@_GZY #E\\OX #^BO #FKPS #NEM\4' | ./sfrobs | od -ta > output_sfrobs

printf '*~BO *{_CIA *hXE]D *LER #@_GZY #E\\OX #^BO #FKPS #NEM\4' | ./sfrobs | od -ta > output_sfrob

diff -u eggert_output_.txt output_sfrob
diff -u eggert_output_.txt output_sfrobu
diff -u eggert_output_.txt output_sfrobs
./sfrobu < rt.jar > output_sfrobu
./sfrob < rt.jar > output_sfrob
diff -u output_sfrobu output_sfrob
#rm output_sfro*

