#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


def main():
  # Implementation details
  #
  # https://namu.wiki/w/BrainFuck
  # https://ko.wikipedia.org/wiki/brainfuck
  ptr = 0
  mem = bytearray(32768)

  import sys
  with open(sys.argv[1], 'r') as f:
    cur = 0
    code = f.read()
    while True:
      try:
        c = code[cur]
      except IndexError as error:
        return

      try:
        m = mem[ptr]
      except IndexError as error:
        print('RuntimeError: out of memory', file=sys.stderr)
        return 1

      if c == '>':
        ptr += 1
      elif c == '<':
        ptr -= 1
      elif c == '+':
        mem[ptr] += 1
      elif c == '-':
        mem[ptr] -= 1
      elif c == '.':
        sys.stdout.write(chr(mem[ptr]))
      elif c == ',':
        mem[ptr] = ord(sys.stdin.read(1))
      elif c == '[':
        if not mem[ptr]:
          try:
            while code[cur] != ']':
              cur += 1
          except IndexError as error:
            print('SyntaxError: following `]` cannot be found',
                  file=sys.stderr)
            return 1
      elif c == ']':
        if mem[ptr]:
          try:
            while code[cur] != '[':
              cur -= 1
          except IndexError as error:
            print('SyntaxError: following `[` cannot be found',
                  file=sys.stderr)
            return 1
      else:
        # Ignore non operators
        pass
      cur += 1


if __name__ == '__main__':
  main()

