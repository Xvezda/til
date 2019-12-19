#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


import six
import itertools


def print_it(it, n=10):
    arr = []
    for _ in range(n):
        try:
            i = six.next(it)
        except StopIteration as err:
            pass
        else:
            arr.append(i)
        '''
        arr.append(i)  <- If i declare like this it will append previous value
                          So, 1, 2, 3, 4, 5, 6 becomes 1, 2, 3, 4, 5, 6, 6, 6..
                          When there's no previous value, It will raise
                          UnboundLocalError
        '''
    print(arr)


def myiter():
    yield 'foo'
    yield 'bar'
    yield 'baz'


def main():
    # Count
    it = itertools.count(10)
    print_it(it)

    # Cycle
    it = itertools.cycle([1, 2, 3, 4])
    print_it(it)

    # Repeat
    it = itertools.repeat('ab')
    print_it(it)

    # Chain
    it = itertools.chain([1, 2, 3], [4, 5, 6])
    print_it(it)

    # Compress
    it = itertools.compress('abcdef', [1, 0, 1, 0, 1, 1, 0, 1])
    print_it(it)

    # Drop while
    # Stop iteration when meets '0'
    it = itertools.dropwhile(lambda x: x, [1, 0, 1, 1])  # 0, 1, 1
    print_it(it)

    # Group by
    for key, val in itertools.groupby('aaabbcccdddaa'):
        print(key, list(val))

    # islice - Slice iterator object like list
    print(six.next(itertools.islice(myiter(), 1, 2)))  # [foo, bar, baz] -> bar

    # tee
    '''
    https://docs.python.org/3/library/itertools.html#itertools.tee
    > tee iterators are not threadsafe
    '''
    it1, it2 = itertools.tee(myiter(), 2)
    print(six.next(it1), six.next(it2))  # Should be same

    # Product
    print_it(itertools.product([1, 2], [3, 4, 5]))

    arr = [1, 2, 3]
    # Permutations
    print_it(itertools.permutations(arr, 2))

    # Combinations
    print_it(itertools.combinations(arr, 2))

    # Combinations with duplicates
    print_it(itertools.combinations_with_replacement(arr, 2))

    # All possible combinations
    print_it(itertools.product(arr, repeat=2))


if __name__ == '__main__':
    main()
