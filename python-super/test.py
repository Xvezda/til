
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


def main():
  # Test class B
  b = B()


if __name__ == "__main__":
  main()
