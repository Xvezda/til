#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


def main():
    import sys
    if 2 < sys.version_info[0]:
        import os
        import http.server as hs

        handler_class = hs.partial(hs.SimpleHTTPRequestHandler,
                                   directory=os.getcwd())
        hs.test(HandlerClass=handler_class, port=8000, bind='')
    else:
        from SimpleHTTPServer import test
        test()


if __name__ == '__main__':
    main()
