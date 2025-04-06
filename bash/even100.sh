#!/bin/sh
for((i=0;i<101;i++))
do
if [ `expr $i % 2` -eq 0 ]
then
echo "$i"
fi
done