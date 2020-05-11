#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import logging
logging.basicConfig()
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)


def traverse(tree, max_depth=5,
             list_=lambda x: x,
             get=(lambda x, y: x)):
    """Non-Recursive tree traversal function"""
    context = tree
    memo = []
    callstack = [context]

    while True:
        logger.debug('callstack: %s' % (callstack,))
        logger.debug('entry: %s' % (context,))

        try:
            keys = list_(context)
        except AttributeError:
            if not callstack:
                break
            # Return to previous context
            logger.debug('end point: %s' % (context,))
            context = callstack.pop()
            continue

        logger.debug('keys: %s' % (keys,))
        try:
            key = keys.pop()
            while key in memo:
                key = keys.pop()
        except IndexError:
            # Out of keys
            if context is tree:
                # Break when context is root
                break
            context = callstack.pop()
            continue
        memo.append(key)
        callstack.append(context)
        logger.debug('get: %s, %s' % (context, key))
        context = get(context, key)


def traverse_dict(tree, max_depth=5):
    return traverse(tree, max_depth,
                    list_=lambda x: x.keys(),
                    get=(lambda x, y: x.get(y)))


def traverse_dict_rec(tree, max_depth=5):
    """Recursive tree traversal function"""
    context = tree
    print(context)

    if not hasattr(context, 'keys'):
        return

    for key in context.keys():
        traverse_dict_rec(context.get(key))


def traverse_list(tree, max_depth=5):
    return traverse(tree, max_depth,
                    list_=lambda x: raise AttributeError() if type(x) is str else x,
                    get=(lambda x, y: y))


def main():
    data = {
        'foo': {
            'bar': 2,
            'spam': {
                'egg': 4
            }
        },
        'baz': 1,
        'hello': {
            'world': 3,
        }
    }
    traverse_dict(data)

    data = [
        'a',
        [
            'b', 'c', 'd'
        ], 'e', 'f',
    ]
    traverse_list(data)



if __name__ == '__main__':
    main()


