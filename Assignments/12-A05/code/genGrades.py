from random import randint
from random import shuffle
import glob
import os
import sys
import json



def combineSchedules():
  files = glob.glob("./schedules/*.json")

  courses = []

  for file in files:
    with open(file) as f:
      courses.extend(json.loads(f.read()))

  with open("./schedules/all.json","w") as f:
    f.write(json.dumps(courses,indent=4))

students = []
courses = []

grades = []
grades.extend(['A']*10)
grades.extend(['B']*30)
grades.extend(['C']*30)
grades.extend(['D']*20)
grades.extend(['F']*5)

with open("./schedules/all.json") as f:
  courses = json.loads(f.read()) 

with open("students.json") as f:
  students = json.loads(f.read()) 


def getRandomGrade():
    shuffle(grades)
    return grades[randint(1,len(grades)-1)]

def genGrades():
  files = glob.glob("./schedules/*.json")

  coursesList = []

  for file in files:
    with open(file) as f:
      coursesList.append(json.loads(f.read()))

  studGrades = {}

  z = 1
  for student in students:
    print(f"{z}")
    z += 1
    glist = []
    for courses in coursesList:
      if 'summer' in file:
        x = randint(0,2)
      else:
        x = randint(2,6)
      for i in range(x):
          g = getRandomGrade()
          c = courses[randint(1,len(courses)-1)]
          while not 'Semester' in c or not 'Year' in c or not 'Crn' in c:
            c = courses[randint(1,len(courses)-1)]
          r = {"grade":g,"crn":c["Crn"],"semester":c["Semester"],"year":c["Year"]}
          glist.append(r)
    studGrades[student["mid"]] = glist

  with open("grades.json","w") as f:
    f.write(json.dumps(studGrades,indent=4))

if __name__=='__main__':
  genGrades()
  #print(students)
