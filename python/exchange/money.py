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

# Backward compatible
import six


class Exchanger(object):
  def __init__(self, unit=None):
    self._rate = {}
    if unit:
      self.unit = unit

  @property
  def unit(self):
    return self._unit

  @unit.setter
  def unit(self, value):
    if not isinstance(value, Money):
      raise ValueError('unit is not `Money` class instance')
    self._unit = value
    self.add(value)

  def add(self, currency):
    self._rate[currency.__class__] = currency

  def update(self, currency):
    if currency.__class__ not in self._rate.keys():
      raise Exception('currency not exists')
    self.add(currency)

  def exchange(self, currency, to=None):
    try:
      from_amount = self._rate[currency.__class__]
    except KeyError as error:
      raise Exception('currency not defined')
    unit_class = self._unit.__class__
    unit_amount = currency / from_amount
    try:
      if to:
        to_amount = self._rate[to] * unit_amount
        return to(to_amount)
    except KeyError as error:
      raise Exception('destination currency undefined')
    return unit_class(unit_amount)

  def equal(self, a, b):
    if not isinstance(a, Money) or not isinstance(b, Money):
      raise ValueError('all arguments should be `Money` type')
    return self.exchange(a) == self.exchange(b)


class Money(float):
  # New overwrite required when extra arguments are given.
  # https://stackoverflow.com/a/35944423
  def __new__(self, amount=1, sign=''):
    return float.__new__(self, amount)

  def __init__(self, amount=1, sign=''):
    self._sign = sign

  def __str__(self):
    ret = '%.2f%s' % (float(self), self._sign)
    # Encode when python version 2
    if six.PY2: return ret.encode('utf-8')
    return ret

  def __eq__(self, other):
    if not isinstance(other, self.__class__):
      if isinstance(other, Money):
        raise ValueError('`%s` cannot be compared without exchanger'
                         % other.__class__.__name__)
      else:
        raise ValueError('`%s` does not inherited `Money` class')
    return self.__hash__() == hash(other)

  def __hash__(self):
    return hash((self.__class__, float(self), self._sign))


## @brief Define currencies
#
# All currencies should inherits `Money` class.
class Cent(Money):
  def __init__(self, amount=1):
    super(Cent, self).__init__(amount, sign='¢')
# Alias
Penny = Cent


class Dollar(Penny):
  def __init__(self, amount=1):
    super(Cent, self).__init__(amount, sign='$')


class Won(Money):
  def __init__(self, amount=10):
    super(Won, self).__init__(amount, sign='₩')
# Alias
KRWon = Won

class JPYen(Money):
  def __init__(self, amount=10):
    super(JPYen, self).__init__(amount, sign='¥')


def main():
  # Key currency is dollar
  ex = Exchanger(Dollar())
  # 100 cent is 1 dollar
  ex.add(Penny(100))
  # 1177 won is 1 dollar
  ex.add(KRWon(1177.50))
  # 109.11 yen is 1 dollar
  ex.add(JPYen(109.11))

  # Exchange 1000 won to japan yen
  result = ex.exchange(KRWon(1000), to=JPYen)
  print('[1000 %s -> %s] result:' % (KRWon.__name__, JPYen.__name__), result)


if __name__ == "__main__":
  main()
