#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals


import frida

def on_message(message, data):
    print('[on_message] message:', message, 'data:', data)

session = frida.attach('cat')

script = session.create_script('''
rpc.exports.enumerateModules = function () {
    return Process.enumerateModules();
};
''')
script.on('message', on_message)
script.load()

print([m['name'] for m in script.exports.enumerate_modules()])
