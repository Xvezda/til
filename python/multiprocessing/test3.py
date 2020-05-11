#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


import time
from pwn import *
from multiprocessing import Pool


def func(x):
    for i in range(x*100, x*1000):
        p.status('...')
        time.sleep(1)


if __name__ == '__main__':
    try:
        p = Pool(10)
        p.map(func, list(range(10)))
    except KeyboardInterrupt:
        p.terminate()


