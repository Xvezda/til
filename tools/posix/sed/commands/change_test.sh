#!/usr/bin/env bash

echo foo | sed -f change.sed
echo
sed -f change.sed foobarbaz.txt
