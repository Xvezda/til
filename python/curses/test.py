import curses

# stdscr = curses.initscr()
# curses.noecho()
# curses.cbreak()
# stdscr.clear()
# curses.endwin()


def main(stdscr):
    curses.noecho()
    curses.cbreak()
    curses.curs_set(0)  # Hide cursor

    stdscr.immedok(True)
    stdscr.clear()
    stdscr.border()

    win = stdscr.subwin(curses.LINES-2, curses.COLS-2, 1, 1)
    win.immedok(True)
    win.addstr('hello world')

    while True:
        c = stdscr.getch()
        if c == ord('q'):
            break


curses.wrapper(main)
