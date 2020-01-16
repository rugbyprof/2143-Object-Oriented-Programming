#!/usr/bin/python
# -*- coding: utf-8 -*-
import urllib
from ftfy import fix_encoding
import re
import string

exclude = set(string.punctuation)


response = urllib.urlopen('http://www.gutenberg.org/files/2600/2600-0.txt')
print(response.info())
html = response.read()
response.close() 

words = {}

html = html.split()
print(len(html))

def addWord(words,word):
    if not word in words:
        words[word] = 0
    words[word] += 1

for word in html:
    word = fix_encoding(word.decode('utf-8').lower())
    word = ''.join(ch for ch in word if ch not in exclude)
    if word.find(u"\u2014") > 0:
        word = word.split(u"\u2014")

    if not type(word) is list:
        addWord(words,word)
    else:
        for w in word:
            addWord(words,w) 

print(words)
