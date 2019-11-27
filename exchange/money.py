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

import six


class Exchanger(object):
  def __init__(self, unit=None):
    if not issubclass(unit.__class__, Money):
      raise ValueError('unit is not `Money` class instance')
    self._unit = unit
    self._rate = {}

  def add(self, currency):
    try:
      self._rate[currency.__class__] = currency
    except (AttributeError, KeyError) as error:
      raise
    except:
      pass

  def exchange(self, currency, to=None):
    try:
      from_amount = self._rate[currency.__class__].amount
      unit_class = self._unit.__class__
      unit_amount = currency.amount / from_amount
    except KeyError:
      raise Exception('currency not defined')
    try:
      if to:
        to_amount = self._rate[to].amount * unit_amount
        return to(to_amount)
    except KeyError:
      raise Exception('destination currency undefined')
    return unit_class(unit_amount)


class Money(object):
  def __init__(self, amount=1, sign=''):
    self._sign = sign
    self._amount = amount

  def __str__(self):
    ret = u'{}{}'.format(self._amount, self._sign)
    if six.PY2: return ret.encode('utf-8')
    return ret

  def __int__(self):
    return self._amount

  def __long__(self):
    return self._amount

  def __float__(self):
    return float(self._amount)

  def __eq__(self, other):
    return self.__hash__() == hash(other)

  def __hash__(self):
    pass

  @property
  def amount(self):
    return self._amount


class Cent(Money):
  def __init__(self, amount=1):
    super(Cent, self).__init__(amount, sign='¢')

  def __hash__(self):
    return hash((Cent, self.amount, self.sign))

Penny = Cent


class Dollar(Penny):
  def __init__(self, amount=1):
    super(Cent, self).__init__(amount, sign='$')

  def __hash__(self):
    return hash((Cent, self.amount, self.sign))


class Won(Money):
  def __init__(self, amount=10):
    super(Won, self).__init__(amount, sign='₩')

  def __hash__(self):
    return hash((Won, self.amount, self.sign))


def main():
  ex = Exchanger(Dollar())
  ex.add(Won(1200))
  result = ex.exchange(Won(1200))
  print(result)


if __name__ == "__main__":
  main()
