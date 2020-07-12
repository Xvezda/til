#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


import re
import requests


def foo(url):
    """Returns url's title"""
    r = requests.get(url)
    if r.status_code != 200:
        raise RuntimeError('status code %d' % r.status_code)
    title_match = re.search(r'<title>(.*)</title>', r.text, re.I)
    if not title_match:
        raise RuntimeError('title not found')
    return title_match.group(1)


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('url')
    args = parser.parse_args()

    print(foo(args.url))

