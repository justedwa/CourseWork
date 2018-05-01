#!/bin/bash

if [ `ls | grep checkin.txt | wc -l` == 0 ]
then
	touch checkin.txt
fi

echo "Welcome!"
echo `uname -a`
echo "Please enter your name:"
read USER
echo "--Hello $USER--"
echo `date`
if [ `date +%H` -ge 18 ]
then
	echo "Warning Late to Work"
	echo "LATE [`date`] $USER" >> checkin.txt
else
	echo "Welcome to Work: $USER"
	echo "[`date`] $USER" >> checkin.txt
fi


