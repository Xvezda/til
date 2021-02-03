# Reference: https://nbviewer.jupyter.org/github/rasbt/python_reference/blob/master/tutorials/scope_resolution_legb_rule.ipynb
#
def tryexec(expr):
    try:
        exec(expr)
    except Exception as err:
        print('expression %r raised %s!' % (expr, err.__class__.__name__))

tryexec('''
def egg():
    global ham  # Allowed
''')

tryexec('''
def foo():
    def bar():
        nonlocal baz  # Not allowed
''')

tryexec('''
a = 1
def local_unbound():
    # a = a + 1
    a += 1
local_unbound()
''')


# Additional
i = 1
[i for i in range(10)]

if i == 9:
    print('Running on Python 2')
elif i == 1:
    print('Running on Python 3')


