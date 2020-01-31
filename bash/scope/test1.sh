#!/usr/bin/env bash

function setvar() {
    FOO=x
    bar=y  # Does case matters?
    local baz=z  # What about local?
}


echo $FOO
echo $bar
echo $baz

setvar

echo $FOO
echo $bar
echo $baz
