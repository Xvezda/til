#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


foo = None
bar = None

def sub(re=None):
    print(foo, bar)
    if re:
        sub()

def main():
    # global foo, bar
    foo = 1
    bar = 'baz'
    sub(True)


if __name__ == '__main__':
    main()

