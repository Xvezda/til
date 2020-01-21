#!/usr/bin/env bash

function foo() {
    # $0 <- Treated as special variable like $@, $? etc...
    # echo $0 $1 $2
    echo $1 $2
}

function main() {
    # 1 as argument
    # foo 1
    # 1, 2 as arguments
    foo 1 2
    # Return value of foo
    echo $?

    return 0
}


main

