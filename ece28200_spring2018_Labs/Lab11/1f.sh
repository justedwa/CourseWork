#!/bin/bash
for (( i = 1; i<=5; i++))
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
