import os,sys
import random


def clear_screen():
    """
    Clears the terminal screen.
    """

    # Clear command as function of OS
    command = "-cls" if system_name().lower()=="windows" else "clear"

    # Action
    system_call(command)

def terminal_size():
    return (os.popen('stty size', 'r').read().split())

class Maze(object):
    def __init__(self,rows=10,cols=10):
        self.rows = rows
        self.cols = cols

        self.maze = []

        for r in range(rows):
            self.maze.append([])
            for c in range(cols):
                self.maze[-1].append('#')

    def __str__(self):
        string = ""
        for row in self.maze:
            for c in row:
                string += c
            string += '\n'
    
        return string

M = Maze(10,40)
print(M)
        