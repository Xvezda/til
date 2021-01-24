import io
import contextlib


@contextlib.contextmanager
def iostring_context(*args, **kwds):
    # __enter__
    ios = io.StringIO()
    ios.write('hello world')

    yield ios

    # __exit__
    ios.close()


with iostring_context() as s:
    s.seek(0)
    print(s.read())


import sys
try:
    # Available?
    s.seek(0)
    print(s.read())
except Exception:
    print('read from out of with block is not available',
          file=sys.stderr)


def return_context():
    with iostring_context() as s:
        return s


try:
    s = return_context()
    s.seek(0)
    print(s.read())
except Exception:
    print('read from returned value from with block is not available',
          file=sys.stderr)
