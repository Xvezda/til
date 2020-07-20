#!/usr/bin/env bash

seq 10 | while read line; do \
    if [ $(( $line % 2 )) -eq 0 ]; then echo $line; fi; done
