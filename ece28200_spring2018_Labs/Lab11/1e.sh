#!/bin/bash
read NUM
if [ $NUM -lt 10 ]
then
	let "NUM = NUM*2"
	echo $NUM
else
	let "NUM = NUM*3"
	echo $NUM
fi
