#!/usr/local/cs/bin/bash

cat list | grep so | sed 's/([^()]*)$//g' | sort -u
