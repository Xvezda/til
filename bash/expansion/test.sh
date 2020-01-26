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

arr_a=("qwer" "asdf" "zxcv")
arr_b=("hello world" "this is test")

# Testing positional arguments
echo "#: $#"
echo "@: $@"
echo "*: $*"
echo "-: $-"


debug_print "array with * @"
# @, * are equivalent
echo "@: ${arr_a[@]}"
echo "*: ${arr_a[*]}"

debug_print "length expansion"
tmp="12345"
echo ${#tmp}
tmp="qwertyuiop"
echo ${#tmp}

debug_print "substitution"
echo ${tmp#qwer}
echo ${tmp#*}  # shortest -> 0
echo ${tmp##*} # longest  -> length


if [ $BASH_VERSINFO -ge 4 ]; then
    debug_print "upper lower"
    tmp="HelloWorld"
    echo ${tmp,}
fi


# Expand vairables starts with "ba"
debug_print "starts with ba"
echo "${!ba*}"

# Expand array keys
debug_print "expand array keys "
echo "\${!arr_a[@]}: ${!arr_a[@]}"
echo "\${!arr_b[@]}: ${!arr_b[@]}"

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
