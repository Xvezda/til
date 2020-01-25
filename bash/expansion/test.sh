#!/usr/bin/env bash
set -e

ESCSEQ_RED="\033[1;31m"
ESCSEQ_RST="\033[0m"

function debug_print() {
    1>&2 printf "${ESCSEQ_RED}"
    1>&2 echo "$(basename $0):$LINENO: $@"
    1>&2 printf "${ESCSEQ_RST}"
}

# foo=x
bar=baz
baz=hello

debug_print ":- expansion"
echo ${foo:-bar}
echo ${foo}
unset foo

debug_print ":= expansion"
echo ${foo:=bar}
echo ${foo}
unset foo

debug_print ":+ expansion"
echo ${foo:+bar}
echo ${foo}
unset foo

debug_print ":? expansion"
echo ${foo:?bar}  # Exits on error
echo ${foo}
unset foo

echo this is invisible
