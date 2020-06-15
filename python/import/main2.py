#!/usr/bin/env python
# -*- coding: utf-8 -*-


def foo():
    import module  # Import from function
    print('foo')


if __name__ == '__main__':
    # How many times module say `imported`?
    foo()
    foo()
    foo()

