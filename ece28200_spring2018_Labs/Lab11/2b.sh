#!/bin/bash
NUM1=$( ls -l | wc -l )
let "NUM1 = NUM1 - 1"
echo "Total file in current directory: $NUM1"
NUM2=$( ls -l | grep *.txt | wc -l )
echo "Total text files in current directory: $NUM2"
