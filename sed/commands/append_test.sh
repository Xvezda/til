#!/usr/bin/env bash

echo foo | sed -f append.sed
echo
sed -f append.sed foobarbaz.txt
