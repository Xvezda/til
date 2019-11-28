
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


class A(object):
  pass

class B(A):
  def __init__(self):
    s = super(B, self)
    print('type;', type(s))
    print('dir:', dir(s))


def main():
  b = B()


if __name__ == "__main__":
  main()
