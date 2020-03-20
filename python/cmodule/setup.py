from distutils.core import setup, Extension

module1 = Extension('spam',
                    sources = ['spammodule.c'])

setup (name = 'SpamDemo',
       version = '1.0',
       description = 'This is a demo package',
       author = 'Xvezda',
       author_email = 'xvezda@naver.com',
       url = 'https://docs.python.org/extending/building',
       long_description = '''
This is really just a demo package.
''',
       ext_modules = [module1])
