#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import textwrap


def sub_with_test():
  # Backslash will remove leading line break
  long_string = """\
    Hello, World!
    foo bar"""
  return long_string


def with_test():
  long_string = textwrap.dedent("""\
    Hello, World!
    foo bar""")
  return long_string


def wout_test():
  long_string = """
    Hello, World!
    foo bar"""
  return long_string


def main():
  print(wout_test())
  print(sub_with_test())
  print(with_test())


if __name__ == "__main__":
  main()
