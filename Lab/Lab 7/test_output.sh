#!/bin/bash

gcc -std=c99 -o tr2b tr2b.c
gcc -std=c99 -o tr2u tr2u.c

echo 'tr2b:'
time ./tr2b 'abc' 'xyz' < input.txt > output_tr2b

echo 'tr2u:'
time ./tr2u 'abc' 'xyz' < input.txt > output_tr2u

tr 'abc' 'xyz' < input.txt > output_tr

diff -u output_tr output_tr2b
diff -u output_tr output_tr2u

rm output_*
