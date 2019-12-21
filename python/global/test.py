#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


foo = 1
bar = 'baz'

def sub(re=None):
    print(foo, bar)
    if re:
        sub()

def main():
    sub(True)


if __name__ == '__main__':
    main()

