#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


class MyClass(object):
    def __init__(self):
        self._handlers = {}

    def run(self):
        pass

    def listen(self, event):
        def wrapper(callback):
            if not callable(callback):
                raise TypeError('callback is not callable')
            if event in self._handlers:
                self._handlers[event].append(callback)
                return
            self._handlers[event] = [callback]
        return wrapper

    def emit(self, event, data=None):
        if event not in self._handlers:
            return
        for handler in self._handlers[event]:
            handler(data)


mc = MyClass()

@mc.listen('foo')
def handle_foo(event):
    print('event foo fired!')


mc.run()
mc.emit('foo')
