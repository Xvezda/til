#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2019 Xvezda <https://xvezda.com/>
#
# Use of this source code is governed by an MIT-style
# license that can be found in the LICENSE file or at
# https://opensource.org/licenses/MIT.

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


class Exchanger(object):
  def __init__(self):
    self.unit = Dollor()


class Money(object):
  def __init__(self, amount=1, sign=''):
    self._sign = sign
    self._amount = amount

  def __str__(self):
    return str(self._amount) + self._sign

  def __int__(self):
    return self._amount

  def __long__(self):
    return self._amount

  def __float__(self):
    return float(self._amount)


class Cent(Money):
  def __init__(self, amount=1):
    super(Cent, self).__init__(amount, sign='¢'.encode('utf-8'))


class Penny(Cent):
  pass


class Dollar(Cent):
  def __init__(self, amount=1):
    super(Cent, self).__init__(amount, sign='$')


class Won(Money):
  def __init__(self, amount=10):
    super(Won, self).__init__(amount, sign='₩'.encode('utf-8'))


def main():
  c = Cent()
  print(c)
  d = Dollar()
  print(d)
  w = Won(100)
  print(w)


if __name__ == "__main__":
  main()
