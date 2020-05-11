#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def source_foo():
    items = [1, 2, 3]
    for item in items:
        yield item


def source_bar():
    items = [4, 5, 6]
    for item in items:
        yield item


def combine(a, b):
    yield from a()
    yield from b()


if __name__ == '__main__':
    for i in combine(source_foo, source_bar):
        print(i)

