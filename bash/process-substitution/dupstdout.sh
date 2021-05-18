#!/bin/bash


# Duplicate foobar to stderr
# Now, one foobar is from stdout and another one is from stderr
echo foobar | tee >(cat >&2)

