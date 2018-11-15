#!/usr/bin/env python3
"""
ioreg displays the I/O Kit registry.  It shows the heirarchical registry structure as an inverted tree.
This script lists the ioreg output to a tmp file and then finds the battery and keyboard percentages in
a very brute force / un-inspired way.

It works for me though.
"""
import subprocess
import sys
import os

def myReplace(line):
    """
    Cleans a list of characters off the ioreg line with the 
    battery percentages. Yes regex exists, I know.
    """
    chars = ['"','|',' ',',',"\n"]
    for c in chars:
        line = line.replace(c,'')
    return line

# Run ioreg command
# Why dump to file? I had issues converting from a byte type to utf-8
# losing line endings. I didn't want to spend any more time (minutes)
# so I moved on.
output = subprocess.getoutput("ioreg -l > /tmp/ioreg.out")

# Flags to turn on mouse battery life value, or keyboard
mouse = False
keyboard = False

# Dictionary of results
batteryLife = {"mouse":None,"keyboard":None}

# Open temp file
ioreg = open("/tmp/ioreg.out","r")

# Search for magic mouse and magic keyboard in file.
# Find either, turn mouse or keyboard flag on and other off.
# Next "batterypercent" value will be associated with device
# with a flag that is on.
for line in ioreg.readlines():
    if line.lower().find("magic mouse") > 0:
        mouse = True
        keyboard = False
    if line.lower().find("magic keyboard") > 0:
        mouse = False
        keyboard = True
    if line.lower().find("batterypercent") > 0:
        line = myReplace(line)
        key,val = line.split('=')
        if mouse:
            batteryLife['mouse'] = val
        elif keyboard:
            batteryLife['keyboard'] = val

print("🖱️  = 🔋%s " % batteryLife['mouse'])
print("⌨️  = 🔋%s " % batteryLife['keyboard'])