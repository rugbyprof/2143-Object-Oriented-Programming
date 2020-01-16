#!/usr/local/bin/python
 
"""
Matrix Stream
Sweeping of the screen surface and if column activated go for the next line
on that column print a random character (could be space or bold)
while opening a new column etc ...
=====================================================================
work (tested) with python 2.3 - 2.7
www.peileppe.com
 
"""
 
import curses
import random
import time
 
w=curses.initscr()
w.clear()
w.border()
w.keypad(1)
w.nodelay(1)
maxy, maxx =w.getmaxyx()
 
def print_randomcharacter_stream(xc,yl,ws,variation=0):
    if variation==1:
        char_stream=chr(random.randint(65,126))
        ws.addch(yl,xc,char_stream, curses.A_BOLD)
    elif variation==2:
        ws.addch(yl,xc,' ')
    else:
        char_stream=chr(random.randint(32,126))
        ws.addch(yl,xc,char_stream)
    ws.move(0,0)
    ws.refresh()
    return
 
action = ''
col_activated=[0]*(maxx-2)
flush_activated=[0]*(maxx-2)
xcol=0
generate_new=True
 
while action != ord('q'):
    while xcol <= maxx-3:
        if col_activated[xcol] > 0:
            if col_activated[xcol] >= maxy-1:
                col_activated[xcol]=1
                generate_new=True
            if flush_activated[xcol] in range(51,65):
                print_randomcharacter_stream(xcol,col_activated[xcol],w,2)
            elif flush_activated[xcol] in range(25,50):
                print_randomcharacter_stream(xcol,col_activated[xcol],w,1)
            else:
                print_randomcharacter_stream(xcol,col_activated[xcol],w)
            flush_activated[xcol]+=1
            if flush_activated[xcol] > 65:
                flush_activated[xcol]=0
            col_activated[xcol]+=1
        if generate_new :
            new_col=random.randint(1,maxx-3)
            col_activated[new_col]=1
        xcol+=1
        generate_new=False
    xcol=0
    action=w.getch()
    time.sleep(0.1)
curses.endwin()