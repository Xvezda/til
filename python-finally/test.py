#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

"""Testing examples according to stackoverflow

https://stackoverflow.com/a/9688068
"""

def test1():
    try:
        return 'Immediate return'
    except:
        pass
    finally:
        print('print me')
    print('with out finally')


def test2():
    try:
        raise Exception('some exception')
    except:
        raise  # Re-throw
    finally:
        print('print me 2')
    print('with out finally 2')


def test3():
    try:
        return 'foo'
    except:
        return 'bar'
    finally:
        return 'baz'


def main():
    ret = test1()
    print(ret)
    try:
        test2()
    except:
        print('exception raised')
    ret = test3()
    print(ret)
    '''
    Result:

    print me
    Immediate return
    print me 2
    exception raised
    baz
    '''


if __name__ == '__main__':
    main()


