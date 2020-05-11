#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import sys
import textwrap


with open(sys.argv[1], 'rb') as f:
    buf = f.read(256)
    print(' '.join(textwrap.wrap(buf.encode('hex'), 2)))


# vim:sw=4 expandtab
