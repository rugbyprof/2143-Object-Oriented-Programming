"""
@Program Name: Yo-Shell V1 Starter Code
@Author: Dr. Griffin

@Description:
    This code is a barebones snippet to get your shell up and running. It provides the following classes 
    (each of which is not fully implemented):
          history - manages a history of commands
          parser - handles parsing of commands into command , arguments, flags
          commander - gets commands parsed and then runs appropriate functions for command
          driver - drives the entire shell
"""

import os
import sys

"""
@Name: history
@Description:
    Maintains a history of shell commands to be used within a shell environment.
@Methods:
    push_command - add command to history
    get_commands - get all commands from history
    number_commands - get number of commands in history
"""
class history(list):
    def __init__(self):
        pass

    """
    @Name: push_command
    @Description:
        Add command to history
    @Params:
        cmd (string) - Command added to history
    @Returns: None
    """
    def push_command(self,cmd):
        self.append(cmd)
        
    """
    @Name: get_commands
    @Description:
        get all commands from history
    @Params: None
    @Returns: None
    """
    def get_commands(self):
        return self
        
    """
    @Name: number_commands
    @Description:
        get number of commands in history
    @Params: None
    @Returns: 
        (int) - number of commands
    """
    def number_commands(self):
        return len(self)

"""
@Name: parser
@Description:
    Handles parsing of commands into command , arguments, flags.
@Methods:
    parse - does actual parsing of command
"""
class parser(object):
    def __init__(self):
        self.parts = []
    """
    @Name: parse
    @Description:
        Parses command into a list (right now). 
    @Params: 
        cmd (string) - The command to be parsed
    @Returns: 
        (int) - number of commands
    """
    def parse(self,cmd):
        self.parts = cmd.split(" ")
        return self.parts
        
"""
@Name: commander
@Description:
    Maintains a history of shell commands to be used within a shell environment.
@Methods:
    run_command - Runs a parsed command
    ls - Directory_listing
    cat - File dump
"""
class commander(parser):
    def __init__(self):
        self.command = None

    """
    @Name: run_command
    @Description:
        Runs a parsed command
    @Params: 
        cmd (string) - The command
    @Returns: 
        (list) - With the command parts (It shouldn't return the list, it should RUN the appropriate command from this method.
    """
    def run_command(self,cmd):
        self.command = cmd
        self.command = self.parse(self.command)
        return self.command

    """
    @Name: ls
    @Description:
        Does a directory listing
    @Params: 
        dir (string) - The directory to be listed
    @Returns: None
    """
    def ls(dir):
        for dirname, dirnames, filenames in os.walk('.'):
            # print path to all subdirectories first.
            for subdirname in dirnames:
                print(os.path.join(dirname, subdirname))
    
        # print path to all filenames.
        for filename in filenames:
            print(os.path.join(dirname, filename))
    """
    @Name: cat
    @Description:
        Dumps a file
    @Params: 
        file (string) - The file to be dumped
    @Returns: None
    """    
    def cat(file):
        f = open(file,'r')
        print(f.read())
        
"""
@Name: driver
@Description:
    Drives the entire shell environment
@Methods:
    run_shell - Loop that drives the shel environment
"""
class driver(history,commander):
    def __init__(self):
        super().__init__()
        self.number_commands = 0
        
    """
    @Name: runShell
    @Description:
        Loop that drives the shel environment
    @Params: None
    @Returns: None
    """ 
    def runShell(self):
        number_commands = 0
        while True:
            self.input = input("parser-$ ")         # get command
            self.push_command(self.input)   		# put in history
            parts = self.run_command(self.input)
            print(parts)
            print(self.get_commands())


if __name__=="__main__":
    d = driver()    
    d.runShell()
    
    
    
    
    
    
