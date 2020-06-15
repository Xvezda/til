#!/usr/bin/env python
# -*- coding: utf-8 -*-


def foo():
    from module import hello  # Import from function
    hello()

def baz():
    from module import bar
    bar()


if __name__ == '__main__':
    # How many times module say imported?
    foo()
    baz()  # imported, bar or just bar?
    foo()
    baz()

