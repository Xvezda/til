#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


from multiprocessing import Process

def fn(name):
    from time import sleep
    from random import random
    sleep(int(random()*10))
    print('hello,', name)


def main():
    p = []
    p.append(Process(target=fn, args=('alex',)))
    p.append(Process(target=fn, args=('bob',)))
    p.append(Process(target=fn, args=('michael',)))
    p.append(Process(target=fn, args=('james',)))
    p.append(Process(target=fn, args=('john',)))

    for ps in p:
        ps.start()

    for ps in p:
        ps.join()


if __name__ == '__main__':
    main()

