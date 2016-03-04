#!/usr/local/cs/bin/bash

gunzip <srt.tgz | tar xf -
(cd srt && make clean check) 2>&1 | diff -u - make-log.txt
awk '200 < length' log.txt readme.txt
