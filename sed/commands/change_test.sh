#!/usr/bin/env bash

echo foo | sed -f change.sed
printf 'foo\nbar' | sed -f change.sed
