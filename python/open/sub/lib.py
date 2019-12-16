#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals



# This library tries to open bar on same directory
#
# open('./bar') will cause following error
# >>> IOError: [Errno 2] No such file or directory: u'./bar'
#
# So, we need to resolve current path
def relpath(base, path):
  import os
  abspath = os.path.abspath(base)
  if not os.path.isdir(base):
    try:
      abspath = abspath[:abspath.rindex(os.sep)+1]
    except:
      pass
  if not abspath.endswith(os.sep):
    abspath += os.sep
  return os.path.join(abspath, path)


with open(relpath(__file__, './bar'), 'r') as f:
  content = f.read()
  print('print from lib.py:', content)
