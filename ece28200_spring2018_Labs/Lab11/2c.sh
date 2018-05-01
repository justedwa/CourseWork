#!/bin/bash
mkdir temp
for file in *.txt
do
	cp $file temp
done
zip -r txt.zip temp
rm -r temp
