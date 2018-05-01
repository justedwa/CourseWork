#!/bin/bash

echo Sorting acmart.html
cat acmart.html | grep href= | tee -i links
sed 's/<.*href="//' < links > linkstmp
sed 's|\s\s\s||' < linkstmp > links
sed 's/".*>//' < links > linkstmp
sed 's|^|http://ctan.math.utah.edu/ctan/tex-archive/macros/latex/contrib/acmart/|' < linkstmp > links
rm linkstmp
