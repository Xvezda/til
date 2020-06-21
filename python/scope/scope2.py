#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


FOO = 1

def egg(bar):
    baz = 3
    print('locals:', locals())
    print('globals:', globals())


if __name__ == '__main__':
    egg(bar=2)
