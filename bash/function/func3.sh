#!/usr/bin/env bash


function foo() {
    echo "hello"
}

function bar() {
    read input
    echo "$input world"
}


function main() {
    foo | bar

    return 0
}


main


