#!/usr/bin/python

import curses
import time
stdscr = curses.initscr()
curses.cbreak()
curses.noecho()
stdscr.keypad(1)

try:
# Run your code here
    height,width = stdscr.getmaxyx()
    num = min(height,width)
    for x in range(num):
        stdscr.addch(x,x,'X')

    # Print Hello World along the top
    stdscr.addstr(0,10,"Hello World")

    #Draw some lines
    for x in range(8):
        stdscr.addch(4,x,curses.ACS_HLINE)
    stdscr.addch(4,8,curses.ACS_PLUS)
    stdscr.addch(4,9,curses.ACS_LRCORNER)

    stdscr.refresh()
    key = 'X'
    while key != ord('q'):
        key = stdscr.getch()
        stdscr.addch(20,25,key)
        stdscr.refresh()
finally:
    curses.nocbreak()
    stdscr.keypad(0)
    curses.echo()
    curses.endwin()
    
    


