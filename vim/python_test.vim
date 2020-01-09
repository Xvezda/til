function! PythonTest(foo, bar)
python << EOP

from __future__ import print_function

import vim

def hello():
    foo = vim.eval('a:foo')
    bar = vim.eval('a:foo')
    print('foo:', foo, ', bar:', bar)

hello()

EOP
endfunction

call PythonTest('hello', 'world')
