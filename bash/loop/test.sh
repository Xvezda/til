#!/usr/bin/env bash


ESCSEQ_RED="\033[1;31m"
ESCSEQ_RST="\033[0m"

function debug_print() {
    1>&2 printf "${ESCSEQ_RED}"
    1>&2 echo "$(basename $0):$LINENO: $@"
    1>&2 printf "${ESCSEQ_RST}"
}


foo=("foo" "bar" "baz")

debug_print "for i in \$foo;"
for i in $foo; do  # Fail - only "foo"
    echo $i
done

debug_print "for i in \"\${foo[@]}\";"
for i in "${foo[@]}"; do  # It works
    echo $i
done


bar="hello world this is test"  # Does it work as array?

debug_print "for i in \$bar;"
for i in $bar; do  # It works! 🤔
    echo $i
done

debug_print "for i in \"\$bar;\""
for i in "$bar"; do  # Fail
    echo $i
done

debug_print "for i in \"\${bar[@]};\""
for i in "${bar[@]}"; do  # Fail
    echo $i
done


baz=("hello world" "this is test")  # Testing strings with spaces

debug_print "for i in \$bar;"
for i in $baz; do
    echo $i
done

debug_print "for i in \"\$bar;\""
for i in "$baz"; do
    echo $i
done

debug_print "for i in \"\${bar[@]};\""
for i in "${baz[@]}"; do
    echo $i
done

