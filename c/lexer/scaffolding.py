import re
import time
import random
import subprocess


TARGET = './main'
MAXNUM = 100
MINNUM = 1
MAXTOK = 10
MINTOK = 1
MAXSP = 5
MINSP = 0
INTVAL = .15


def rand(start, end):
    return int(random.random() * end) + start


def main():
    operators = ['+', '-', '/', '*']
    while True:
        tokens = [str(rand(MINNUM, MAXNUM))]
        for _ in range(rand(MINTOK, MAXTOK)):
            tokens.append(operators[rand(0, len(operators))])
            tokens.append(str(rand(MINNUM, MAXNUM)))
        expr = (' ' * rand(MINSP, MAXSP)).join(tokens)
        print(expr)

        output = subprocess.check_output([TARGET], input=expr.encode())
        outnum = re.search(r'([-]?\d+)', output.decode()).group(1)

        pyout = str(eval(expr.replace('/', '//')))
        print('expect: %s, result: %s' % (pyout, outnum))

        assert outnum == pyout
        time.sleep(INTVAL)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass

