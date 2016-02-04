#!/bin/bash

dir=$1

RESULT=`ls $dir | sort`
HIDDEN=`ls -a $dir | grep '^\.' | sort`
let count=0
declare -a FDARR

restore="$IFS"
IFS=$'\n'

for HFILE in $HIDDEN
do
    if [ -L "$dir/$HFILE" ]
    then
	:
    elif [ ! -f "$dir/$HFILE" ]
    then
	:
    elif [ ! -r "$dir/$HFILE" ]
    then
	echo "$HFILE is not readable"
    else
	FDARR[$count]="$dir/$HFILE"
	let count=count+1
    fi
done

for FILE in $RESULT
do
    if [ -L "$dir/$FILE" ]
    then
        :
    elif [ ! -f "$dir/$FILE" ]
    then
        :
    elif [ ! -r "$dir/$FILE" ]
    then
        echo "$FILE is not readable"
    else
        FDARR[$count]="$dir/$FILE"
        let count=count+1
    fi
done

for (( i=0; i<$count; i++ ))
do
    for (( j=i+1; j<$count; j++ ))
    do
        cmp -s "${FDARR[$i]}" "${FDARR[$j]}"
        if [ $? -eq 0 ]
        then
            ln -fP "${FDARR[$i]}" "${FDARR[$j]}"
	    FDARR[$j]=FDARR[$i]
        fi
    done
done

IFS=$restore
