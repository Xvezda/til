
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


class A(object):
  pass


class B(A):
  def __init__(self):
    s = super(B, self)
    # s = super()
    print('type;', type(s))
    attrs = dir(s)
    print('dir:', attrs)
    print('__thisclass__:', s.__thisclass__)


class C(B):
  pass


def main():
  # Test class B
  b = B()

  # Can super called from main?
  s = super(B, C)
  print('main dir:', dir(s))
  print('main __thisclass__:', s.__thisclass__)


if __name__ == "__main__":
  main()
