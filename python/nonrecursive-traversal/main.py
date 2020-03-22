#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import logging
logging.basicConfig()
logger = logging.getLogger(__name__)
# logger.setLevel(logging.DEBUG)


def traverse_dict(tree, max_depth=5):
    """Non-Recursive tree traversal function"""
    context = tree
    memo = []
    callstack = [context]

    while True:
        logger.debug('callstack: %s' % (callstack,))
        logger.debug('entry:', context)
        if not hasattr(context, 'keys'):
            if not callstack:
                break
            # Return to previous context
            print('end point:', context)
            context = callstack.pop()
            continue

        keys = context.keys()
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
        context = context.get(key)


def traverse_dict_rec(tree, max_depth=5):
    """Recursive tree traversal function"""
    context = tree
    print(context)

    if not hasattr(context, 'keys'):
        return

    for key in context.keys():
        traverse_dict_rec(context.get(key))


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



if __name__ == '__main__':
    main()


