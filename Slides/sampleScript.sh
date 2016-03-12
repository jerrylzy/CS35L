#!/bin/bash

# Built in shell variables
ls -l
echo "My first script!"
echo "Script name = $0, First arg = $1, Second arg = $2, ..."
echo "Number of arguments = $#"

#int and string variables
varValue=10
strValue="hello world strValue"
echo $varValue
echo $strValue

#For loops
for (( c=1; c<=5; c++ ))
do
    echo "Value of c is $c"
done

#While loops
c=1
while [ $c -lt 6 ]
do
    echo "Value of c is $c"
    let c=c+1
done

#Conditionals
COUNT=5
if [ $COUNT -gt 1 ]
then
    echo "Hello World!"
elif [ $COUNT -eq 5 ]
then
    echo "Hello World again!"
else
    echo "End of world!"
fi

#Reading from STDIN
while read NAME
do
    echo "Input text is:$NAME"
done

#Meaning of backticks, single quotes and double quotes
c=100
echo "Value of c = $c"
echo 'Value of c = $c'
temp=`ls -l`
temp1=$(ls -l)
echo "Backticks output : $temp"
echo "Dollar( output : $temp1"

#Another variant of iterating using for loops
printf "$temp \n"
for foo in $temp
do
    echo "next word is $foo"
done

#For debugging
set -x

