#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import weakref


if __name__ == '__main__':
    foo = lambda x: x  # I'm the key!
    bar = 'baz'

    normdict = dict()
    normdict[foo] = bar

    print('normdict before:', normdict.keys())

    del foo  # Not `del data[foo]`
    print('normdict after:', normdict.keys())

    foo = lambda x: x  # I'm the key!

    weakdict = weakref.WeakKeyDictionary()
    weakdict[foo] = bar
    print('weakdict before:', weakdict.keys())

    del foo  # Not `del data[foo]`
    print('weakdict after:', weakdict.keys())

    bar = lambda x: x

    weakdict = weakref.WeakValueDictionary()

    weakdict['bar'] = bar
    print('weakdict before:keys() - 2:', weakdict.keys())
    print('weakdict before:values() - 2:', weakdict.values())

    del bar

    print('weakdict after:keys() - 2:', weakdict.keys())
    print('weakdict after:values() - 2:', weakdict.values())
