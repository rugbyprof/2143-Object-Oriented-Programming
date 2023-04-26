""" Python version of course code.

Returns:
    [type]: [description]
"""

from random import randint
from rich import print
import json
import os
import sys


# class Grade(object):
#   def __init__(self,grade=None):
#     self.grade = grade.upper()
#     if self.grade != None:
#       self.qualityPoints = self.__qualityPoints()

#   def __qualityPoints():
#     # based on grade
#     return randint(1,4)

#   def __str__(self):
#     return f"[{self.grade}]"    

#   def __repr__(self):
#     pass
    
# class Course(object):
#   def __init__(self):
#     self.crn
#     self.subj
#     self.courseNum
#     self.instructor
#     self.semester
#     self.year


# class Transcripts(object):
#   def __init__(self,):
#     self.course = {}

# class Student(object):
#   """ Hello this is a docstring for you
#   [1,2,3,4]
#   """
#   def __init__(self):
#     self.first = None
#     self.last = None
#     self.mid = None

#   def edit(self,**kwargs):
#     """
#     @description: This is my method docstring
#     @params:
#        name (string) : students name
#     @return None
#     """
#     pass

#   def __repr__(self):
#     return "hello world"

#   def __str__(self):
#     return self.__repr__()

class Schedule(object):
  def __init__(self,semester,year):
    self.semester = semester
    self.year = year

    path = f"./schedules/{self.year}_{self.semester}_schedule.json"

    if not os.path.exists(path):
      print(f"File {path} doesn't exist!")
      sys.exit()
      
    with open(path) as f:
      self.courses = json.loads(f.read())
    

  def find(self,crn):
    for course in self.courses:
      if 'Crn' in course:
        if course['Crn'] == crn:
          return course
    return None

  def newFind(self,**kwargs):
    crn = kwargs.get('crn',None)
    keyword =kwargs.get('keyword',None)

    if crn != None:
      return self.find(crn)

    if keyword != None:
      return self.findByTitle(keyword)

  def findByTitle(self,key):
    results = []
    for course in self.courses:
      if 'Title' in course:
        if key.lower() in course['Title'].lower():
          results.append(course)
    return results

  # def __getitem__(self, key):
  #   return self.newFind(key)

  

if __name__=='__main__':
  s1 = Schedule('fall',2021)
  # s = Student()

  #print(s1.find('12485'))

  r = s1.findByTitle('advanced')

  s1.find(keyword='advanced')

  s1.find(crn='12345')

  print(r)

  # print(s.__doc__)

  # print(s.edit.__doc__)

  # print(s)