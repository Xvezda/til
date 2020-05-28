#!/usr/bin/env bash

for (( i=2; i<=9; i+=1 )); do
    for (( j=1; j<=9; j +=1 )); do
        printf '%d x %d = %2d\n' $i $j $(( i*j ))

        # break 1 == break
        #break 1

        # break 2 == for (( i ... )) break
        #break 2
    done
done
