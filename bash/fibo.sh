#!/bin/sh
read num
a=0
b=1
if [ $num -ge 1 ]
then
echo "$a"
fi
if [ $num -ge 2 ]
then
echo "$b"
fi
for((i=2;i<num;i++))
do
c=`expr $a + $b`
a=$b
b=$c
echo "$c"
done