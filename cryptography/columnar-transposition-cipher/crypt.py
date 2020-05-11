#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (C) 2020 Xvezda <xvezda@naver.com>

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import re
import sys

if sys.version_info[0] < 3:
    input = raw_input


def order(key):
    orders = [0] * len(key)
    chars = list(key)
    k = 1
    # Make orders
    while min(orders) == 0 and len(chars) > 0:
        c = min(chars)
        i = key.index(c)
        while orders[i] > 0:
            i = key[i+1:].index(c) + i + 1
        orders[i] = k
        k += 1
        chars.pop(chars.index(c))
    return orders


def repl(text, from_=' ', to='_'):
    result = text
    regexs = [r'^(' + from_ +  '*)', r'(' + from_ + '*)$']
    for regex in regexs:
        result = re.sub(regex, lambda m: len(m.group(0))*to, result)
    return result


def encrypt(key, text):
    orders = order(key)
    matrix = []
    i = 0
    # Mapping
    while text[i:i+len(key)]:
        frag = text[i:i+len(key)]
        matrix.append(frag + (' ' * (len(key) - len(frag))
                      if len(frag) < len(key)
                      else ''))
        i += len(key)
    tokens = [''] * len(key)
    for i in range(len(key)):
        for item in matrix:
            tokens[orders[i]-1] += item[i]
    result = ''.join(tokens)
    return repl(result)


def decrypt(key, text):
    orders = order(key)
    matrix = []
    i = 0
    k = (len(text) // len(key)) + (1 if len(text) % len(key) > 0 else 0)
    while text[i:i+k]:
        frag = text[i:i+k]
        matrix.append(list(frag))
        i += k
    result = ''
    for i in range(k):
        for o in orders:
            result += matrix[o-1].pop(0)
    return repl(result, from_=r'_', to=' ')


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--encrypt', '-e', action='store_true', default=True)
    parser.add_argument('--decrypt', '-d', action='store_true')
    args = parser.parse_args()

    text = input('input: ')
    key = input('key: ')

    if args.decrypt:
        dec = decrypt(key, text)
        print(dec)
        return 0

    if args.encrypt:
        enc = encrypt(key, text)
        print(enc)



if __name__ == '__main__':
    main()

