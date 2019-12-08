#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


def main():
  import sub.lib
  from sub.lib import relpath
  with open(relpath(__file__, './sub/bar'), 'r') as f:
    content = f.read()
    print('print from main.py:', content)


if __name__ == '__main__':
  main()

