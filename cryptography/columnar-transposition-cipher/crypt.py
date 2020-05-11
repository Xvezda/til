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


def encrypt(key, text):
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
    result = re.sub(r'^(\s*)', lambda m: len(m.group(0))*'?', result)
    result = re.sub(r'(\s*)$', lambda m: len(m.group(0))*'?', result)
    return result


def main():
    text = input('input: ')
    key = input('key: ')
    enc = encrypt(key, text)
    print(enc)


if __name__ == '__main__':
    main()

