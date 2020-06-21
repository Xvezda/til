#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


import scope2

SPAM = 4

if __name__ == '__main__':
    locals_, globals_ = scope2.egg(bar=2)
    print(globals_['FOO'])

    try:
        print(globals_['SPAM'])
    except KeyError:
        print('nope')
