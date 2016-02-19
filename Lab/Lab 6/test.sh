#!/bin/bash

gunzip < hw.tar.gz | tar xf -
mkdir -m go-rwx .gnupg
gpg --homedir .gnupg --import hw-pubkey.asc
gpg --verify hw.tar.gz.sig hw.tar.gz
awk '200 < length' log.txt hw.txt
