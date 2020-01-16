from __future__ import print_function
import colorama
from colorama import Fore, Back, Style
from random import randint, choice
from string import printable
import sys
import os
import time
import threading
import textwrap

class PrintScreen(object):

    def __init__(self):
        # Fore, Back and Style are convenience classes for the constant ANSI strings that set
        #     the foreground, background and style. The don't have any magic of their own.
        self.ForeGrounds = [ Fore.RED, Fore.GREEN, Fore.YELLOW, Fore.BLUE, Fore.MAGENTA, Fore.CYAN, Fore.WHITE ]
        self.BackGrounds = [ Back.BLACK, Back.RED, Back.GREEN, Back.YELLOW, Back.BLUE, Back.MAGENTA, Back.CYAN, Back.WHITE ]
        self.Styles = [ Style.DIM, Style.NORMAL, Style.BRIGHT ]

        self.screen_width , self.screen_height = self.getTerminalSize()

        self.MinY, self.MaxY = 1, self.screen_height
        self.MinX, self.MaxX = 1, self.screen_width
        
    def getTerminalSize(self):
        env = os.environ
        def ioctl_GWINSZ(fd):
            try:
                import fcntl, termios, struct, os
                cr = struct.unpack('hh', fcntl.ioctl(fd, termios.TIOCGWINSZ,'1234'))
            except:
                return
            return cr
        cr = ioctl_GWINSZ(0) or ioctl_GWINSZ(1) or ioctl_GWINSZ(2)
        if not cr:
            try:
                fd = os.open(os.ctermid(), os.O_RDONLY)
                cr = ioctl_GWINSZ(fd)
                os.close(fd)
            except:
                pass
        if not cr:
            cr = (env.get('LINES', 25), env.get('COLUMNS', 80))

        return int(cr[1]), int(cr[0])



    def printScreen(self,start_x,start_y,width,height):
        colorama.init()
        # gratuitous use of lambda.
        pos = lambda y, x: '\x1b[%d;%dH' % (y, x)

        foreground = choice(ForeGrounds)
        background = BackGrounds[0]
        style = Styles[2]

        num = 1
        line = 0
        listNum = []
        
        while len(str(num)) < (width*height):
            listNum = textwrap.wrap(str(num), width=width)
            for element in listNum:
                print('%s%s%s%s%s' % (pos(start_y+(line%height), start_x), foreground, background, style, element), end='')
                line += 1
            line = 0
            num *= 2
            
    def printstars(self,n):
        for i in range(n+1):
            print(i*'*',end="")
            print()                

if __name__ == '__main__':
    
    screen = PrintScreen()
    screen.printstars(10)


    
