#!/usr/bin/env bash


function substr() {
    echo -n "${1:$2:$3}"
}


function main() {
    echo $(substr 'hello' 1 3)

    return 0
}


main

