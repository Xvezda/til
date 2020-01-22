#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals



def custom_print(*args, **kwargs):
    print(*args, **kwargs)


def main():
    custom_print('hello', 'world', end='')


if __name__ == '__main__':
    main()

