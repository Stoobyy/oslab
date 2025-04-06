#!/bin/sh
read num
rev=0
while [ $num -ne 0 ]
do
rev=`expr $rev \* 10 + \( $num % 10 \)`
num=`expr $num / 10`
done
echo "Reverse of the number is $rev"