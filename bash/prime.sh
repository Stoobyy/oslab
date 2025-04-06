#!/bin/sh
read num
flag=0
for((i=2;i<num;i++))
do
if [ `expr $num % $i` -eq 0 ]
then
flag=1
break
fi
done
if [ $flag -eq 0 ]
then
echo "$num is prime"
else
echo "$num is not prime"
fi