class A(object):
    def __init__(self):
        self.foo = 1


class B(object):
    def __init__(self):
        self.bar = 2


class C(A, B):
    def __init__(self):
        for base in getattr(self.__class__, '__bases__'):
            base.__init__(self)


if __name__ == '__main__':
    c = C()
    print(c.foo)
    # Expected to work
    print(c.bar)

