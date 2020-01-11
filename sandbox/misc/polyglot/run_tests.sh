#!/usr/bin/env bash


TARGETS=polyglot_*

for exe in $TARGETS
do
    echo $exe | sed 's/.*_//g' | awk '{ print "- " $0 }'
    ./$exe
    echo
done
