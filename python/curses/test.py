import curses

# stdscr = curses.initscr()
# curses.noecho()
# curses.cbreak()
# stdscr.clear()
# curses.endwin()


def main(stdscr):
    curses.noecho()
    curses.cbreak()
    stdscr.clear()
    win = curses.newwin(1, 20, 0, 0)
    win.addstr('hello world')
    stdscr.refresh()
    win.refresh()
    while True:
        c = stdscr.getch()
        if c == ord('q'):
            break


curses.wrapper(main)
