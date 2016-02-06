#!/bin/bash

tmp=$(mktemp -d)
cd $tmp
touch -d '1918-11-11 11:00 GMT' wwi-armistice
touch now
sleep 1
touch now1
