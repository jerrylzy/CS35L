#!/bin/bash

dir=`pwd`

tmp=$(mktemp -d)
cd $tmp
touch -d '1918-11-11 11:00 GMT' wwi-armistice
touch now
sleep 1
touch now1
TZ=UTC0 $dir/coreutils-with-bug/src/ls -lt --full-time wwi-armistice now now1
cd $dir
rm -rf $tmp

