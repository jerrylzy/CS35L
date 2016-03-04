#!/usr/local/cs/bin/bash

od -An -t fD -N 80000000 < /dev/urandom |
tr -s [:blank:] '\n' |
sed '/^$/d' > random.txt
