#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


def main():
  # Implementation details
  # https://namu.wiki/w/BrainFuck
  # https://ko.wikipedia.org/wiki/brainfuck
  ptr = 0
  mem = bytearray(32768)

  import sys
  import argparse

  parser = argparse.ArgumentParser()
  parser.add_argument('file', nargs='?', help='brainfuck source code file path')

  args = parser.parse_args()
  if not args.file:
    parser.print_help()
    return 1

  with open(args.file, 'r') as f:
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
        mem[ptr] = (m+1) % 256
      elif c == '-':
        mem[ptr] = (m-1) % 256
      elif c == '.':
        sys.stdout.write(chr(m))
        sys.stdout.flush()
      elif c == ',':
        mem[ptr] = ord(sys.stdin.read(1)) % 256
      elif c == '[':
        if not mem[ptr]:
          try:
            depth = 0
            while True:
              cur += 1
              if code[cur] == ']' and not depth:
                break
              if code[cur] == '[':
                depth += 1
              elif code[cur] == ']':
                depth -= 1
          except IndexError as error:
            print('SyntaxError: following `]` cannot be found',
                  file=sys.stderr)
            return 1
      elif c == ']':
        if mem[ptr]:
          try:
            depth = 0
            while True:
              cur -= 1
              if code[cur] == '[' and not depth:
                break
              if code[cur] == ']':
                depth += 1
              elif code[cur] == '[':
                depth -= 1
          except IndexError as error:
            print('SyntaxError: following `[` cannot be found',
                  file=sys.stderr)
            return 1
      else:
        # Ignore on operators
        pass
      cur += 1


if __name__ == '__main__':
  main()

