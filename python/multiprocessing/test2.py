#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


import six
from itertools import product
from multiprocessing import Process


def worker(arr):
    for item in arr:
        print(item)


def main():
    p = []
    it = product('abcdef', repeat=6)

    while True:
        try:
            arr = []
            for _ in range(10000):
                try:
                    arr.append(six.next(it))
                except StopIteration as err:
                    raise
        except StopIteration as err:
            break
        p.append(Process(target=worker, args=(arr,)))

    for ps in p:
        ps.start()

    for ps in p:
        ps.join()


if __name__ == '__main__':
    main()

