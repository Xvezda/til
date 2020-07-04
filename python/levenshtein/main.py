#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


def levenshtein_matrix(a, b):
    matrix = []
    matrix.append(range(len(b)+1))
    for i in range(1, len(a)+1):
        matrix.append([i] + [0]*len(b))

    for j, y in enumerate(list(a)):
        for i, x in enumerate(list(b)):
            if x == y:
                matrix[j+1][i+1] = matrix[j][i]
            else:
                matrix[j+1][i+1] = 1 + min(
                    matrix[j][i],
                    matrix[j][i+1],
                    matrix[j+1][i]
                )
    return matrix


def levenshtein_distance(a, b):
    matrix = levenshtein_matrix(a, b)
    return matrix[-1][-1]


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()

    parser.add_argument('--test', '-t', action='store_true')
    parser.add_argument('a', nargs='?')
    parser.add_argument('b', nargs='?')
    args = parser.parse_args()

    if args.test:
        assert levenshtein_distance('foo', 'bar') == 3
        assert levenshtein_distance('bar', 'baz') == 1
        print('passed')
    else:
        print(levenshtein_distance(args.a, args.b))

