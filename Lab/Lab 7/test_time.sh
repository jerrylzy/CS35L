#!/bin/bash

echo 'tr2b:'
time ./tr2b 'a' 'x' < input_a.txt > output_tr2b

echo 'tr2u:'
time ./tr2u 'a' 'x' < input_a.txt > output_tr2u

tr 'a' 'x' < input_a.txt > output_tr

diff -u output_tr output_tr2b
diff -u output_tr output_tr2u

rm output_*

