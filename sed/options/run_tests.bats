#!/usr/bin/env bats


@test "silent output" {
    result="$(echo 'ignore this' | sed -n '')"
    [[ "$result" = "" ]]
}

@test "foo to bar substitution" {
    result="$(echo 'foo' | sed -f foo2bar.sed)"
    [[ "$result" = "bar" ]]
}

