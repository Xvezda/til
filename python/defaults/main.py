#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


def foo(bar=None, *args, **kwargs):
    print('bar:', bar)
    print('__defaults__:', foo.__defaults__)
    print('dir:', dir(foo))

    baz = kwargs.get('baz', None)
    print('baz:', baz)
    if 'baz' not in kwargs.keys():
        print('baz not set')
    else:
        print('baz set')


if __name__ == '__main__':
    foo()
    foo(baz=None)


