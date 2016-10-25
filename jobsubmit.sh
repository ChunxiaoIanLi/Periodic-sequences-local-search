#!/bin/bash

n=$1
a=$2
b=$3

i=1
while [ $i -le 128 ]
do
	echo sqsub -r 7d -o output/$n\_$a\_$b\_15/$i.log ./a.out $n $a $b 15
	sqsub -r 7d -o output/$n\_$a\_$b\_15/$i.log ./a.out $n $a $b 15	
    #sqsub -r 7d -o output/$n\_10/$i.log ./a.out $n $a $b 10
	i=$((i+1)) 
done