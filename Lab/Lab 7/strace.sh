#!/bin/bash

strace -o strace_outputb ./tr2b 'abc' 'xyz' < input.txt > output1.txt
strace -o strace_outputu ./tr2u 'abc' 'xyz' < input.txt > output2.txt

