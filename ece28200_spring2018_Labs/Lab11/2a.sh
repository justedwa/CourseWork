#!/bin/bash
echo "Enter the number of lines for the pattern"
read x
for (( i = 1; i<=x; i++))
	do
	#echo $i
	let "j = 0"
		while [ $j -lt $i ]
		do
		echo -n o
		let "j = j + 1"
		done
	echo -e
	done
