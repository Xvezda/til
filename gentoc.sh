#!/bin/sh

find . -maxdepth 2 -type d \! -regex '.*\.git.*' \
    | sed '1d' \
    | while read line; do
        depth=$(echo "$line" | grep -o '/' | wc -l)
        if [ $depth -eq 2 ]; then
            printf "  "
        fi
        prefix="$(echo "$line" | tr './' ' ' \
            | awk '{ print $NF }' | tr '_-' ' ')"
        echo "- [$prefix]($line)"
    done
