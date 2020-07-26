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
INTVAL = 0.15


def rand(start, end):
    return int(random.random() * (end + 1)) + start


def main():
    operators = ['+', '-', '/', '*']
    while True:
        tokens = [str(rand(MINNUM, MAXNUM))]
        for _ in range(rand(MINTOK, MAXTOK)):
            tokens.append(operators[rand(0, len(operators)-1)])
            p = rand(0, 0x10)
            # Randomly insert open parentheses
            if p % 3 == 1:
                tokens.append('(')

            tokens.append(str(rand(MINNUM, MAXNUM)))

            # Randomly insert closing parentheses
            if p % 3 == 2:
                tokens.append(')')

        expr = (' ' * rand(MINSP, MAXSP)).join(tokens)
        # Randomly remove all parentheses
        if rand(0, 2) > 0:
            expr = expr.replace('(', '').replace(')', '')

        print(expr)

        try:
            output = subprocess.check_output([TARGET], input=expr.encode())
        except subprocess.CalledProcessError:
            try:
                # Expect to fail
                pyout = str(eval(expr.replace('/', '//')))
            except ZeroDivisionError:
                pass
            except SyntaxError:
                pass
            else:
                assert 0
        else:
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

