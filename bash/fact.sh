#!/bin/sh
read num
fact=1
for((i=2;i<=num;i++))
do
fact=`expr $fact \* $i`
done
echo "Factorial of $num is $fact"