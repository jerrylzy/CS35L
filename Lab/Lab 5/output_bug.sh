#!/bin/bash

tmp=$(mktemp -d)
cd $tmp
touch -d '1918-11-11 11:00 GMT' wwi-armistice
touch now
sleep 1
touch now1
TZ=UTC0 ~/cs35L/lab5/coreutils/bin/ls -lt --full-time wwi-armistice now now1
cd ~/cs35L/lab5/
rm -rf $tmp

