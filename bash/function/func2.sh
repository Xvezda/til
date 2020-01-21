#!/usr/bin/env bash


function add() {
    return $(( $1 + $2 ))
}


function main() {
    add 1 2
    echo $?
    return 0
}


main

