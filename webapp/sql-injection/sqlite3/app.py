#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


import sqlite3

from flask import Flask
from flask import request

app = Flask(__name__)


@app.route('/')
def index():
    conn = sqlite3.connect(':memory:')
    if 'prequery' in request.args:
        query = request.args.get('prequery')
        try:
            conn.executescript(query)
        except Exception:
            pass
    if 'inject' not in request.args:
        return 'Try <a href="/?inject=select%201">/?inject=&lt;payload&gt;</a>'
    query = request.args.get('inject')
    try:
        cur = conn.execute(query)
    except Exception as err:
        return '<code>Error: %s</code>' % (err,)
    else:
        return '<pre>query: %s\n%s</pre>' % (query, cur.fetchone())


if __name__ == '__main__':
    app.run(host='127.0.0.1', port='1337', debug=True)

