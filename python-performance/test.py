#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

from textwrap import dedent
from timeit import timeit


class Color:
    red = '\033[31m'
    green = '\033[32m'
    yellow = '\033[33m'
    end = '\033[0m'


def printit(*args, **kwargs):
    t = timeit(*args, **kwargs)
    print('%sstatement%s:\n' % (Color.green, Color.end),
          kwargs['stmt'],
          '\n%stime%s:' % (Color.green, Color.end),
          t, '\n')


def main():
    printit(stmt=dedent('''\
    '%s' % ('test',)
    '''))
    printit(stmt=dedent('''\
    '{}'.format('test',)
    '''))


if __name__ == '__main__':
    main()


