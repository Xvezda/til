#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


# https://stackoverflow.com/a/44210735/11621603
import os
import sys
import subprocess
import pkg_resources

try:
    DEVNULL = getattr(subprocess, 'DEVNULL')
except AttributeError:
    DEVNULL = open(os.devnull, 'wb')

required = {'tispoon'}
installed = {pkg.key for pkg in pkg_resources.working_set}
missing = required - installed

if missing:
    python = sys.executable
    subprocess.check_call([python, '-m', 'pip', 'install'] + list(missing),
                          stdout=DEVNULL)

try:
    import tispoon
except ImportError:
    print('failed!', file=sys.stderr)
else:
    print('success!')
