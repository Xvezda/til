#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


from time import sleep
from random import random
from threading import Thread, Event, Lock

event = Event()
lock = Lock()

class MyThread(Thread):
    def __init__(self, num):
        super(MyThread, self).__init__()
        self.num = num
        self.delay = random()*10 + 1

    def run(self):
        print('%d: delay for %.2f...' % (self.num, self.delay))
        event.wait(timeout=self.delay)
        # event.set()
        print('%d: done!' % (self.num))


def main():
    pool = []
    for i in range(10):
        pool.append(MyThread(i))

    map(lambda x: x.start(), pool)

    for t in pool:
        t.join()



if __name__ == '__main__':
    main()

