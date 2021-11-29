## Assignment 6 - Uml Diagrams
#### Due: 12-03-2021 (Friday @ 12:00 p.m.)


## Overview

Quite simply we want to design a class or set of classes that will allow us to print out an individual students transcripts representing the collection of all their courses taken and calculating a GPA for the student. 

>**Academic Transcripts** are a set of documents to show the student's records of studies like the courses completed, grades obtained, subject wise marks, degrees and awards. 
>
><sup>For our purposes we want the "courses completed", "grades obtained" and the calculated students "GPA".</sup>

To say we just want a `Transcript Class` is an over simplification. Your transcript class will depend on other classes and data files. In the [code](code) folder, there are some helper files giving you a rudimentary start, but more importantly, there are data files basically defining each data component. You should at a minimum have a class to represent each different data file type, with your goal being to represent each data type: Schedule, Students, and Grades along with any relationships between the data necessary to ultimately create an academic transcript.


## Data Files

### Student

- mid : Mustang identification number
- classification: 

```json
[
  {
    "label": "freshman", 
    "hours": {
      "min" : 0,
      "max": 30
    }
  },
  {
    "label": "sophomore", 
    "hours": {
      "min" : 31,
      "max": 60
    }
  },
  {
    "label": "junior", 
    "hours": {
      "min" : 61,
      "max": 90
    }
  },
  {
    "label": "senior", 
    "hours": {
      "min" : 91,
      "max": null
    }
  }
]
```

The other fields are self explanatory.

```json
  {
    "mid": 20224127,
    "first_name": "Kalli",
    "last_name": "Pottinger",
    "email": "kpottingerq@noaa.gov",
    "classification": "Junior"
  }
```

### Grades

- key: Student `mid` points to an array of grades where:
  - grade: Letter grade "A","B","C","D","F" 
  - crn: unique identifier relating this grade to a course
  - semester: semester grade earned
  - year: year grade earned

```json
{
    "20237236": [
        {
            "grade": "B",
            "crn": "20486",
            "semester": "Spring",
            "year": 2021
        },
        {
            "grade": "D",
            "crn": "21702",
            "semester": "Spring",
            "year": 2021
        },
        ...
```

### Schedule

The only relevant information you need for your transcripts are listed here:

- Crn : unique identifer for a course
- Subj: Subject like english, history, or math.
- Crse: A number providing the level of the course 1000's = Fresman 4000's are senior level. Not necessary for your code design, but interesting. This, however is important, the last digit in the Crse = the number of hours the course is worth. Example: 2143 is a "3" hour course, where 1044 is a "4" hour class.
- Title: string title  
- Year: duh
- Semester: same

Below is a full data example for a course, where all the info isn't needed for this project.

```json
{
    "Col": "SE",
    "Crn": "11424",
    "Subj": "CMPS",
    "Crse": "2143",
    "Sect": "101",
    "Title": "Object-Oriented Programming",
    "PrimaryInstructor": "Terry Griffin",
    "Max": 27,
    "Curr": 27,
    "Aval": " ",
    "Days": "MWF",
    "Begin": "1200pm",
    "End": "1250pm",
    "Bldg": "BO",
    "Room": "304",
    "Year": 2021,
    "Semester": "Fall"
},
```

### GPA

The GPA for a student is a formula that calculates a value from 0 - 4. 
Why 0-4? Well in most systems, we use a "quality" point system where each letter grade is given a specific amount of quality points. The points are very simple:

- A = 4
- B = 3
- C = 2
- D = 1
- F = 0

So, given that each course has the same number of hours, here are a few examples of GPA:

- A, B, A, B = 4+3+4+3 = 14/4 = 3.5 
- C, B, A = 2+3+4 = 9/3 = 3.0
- C, C, A = 2+2+4 = 8/3 = 2.6
- A, A, B, F = 4+4+4+0 = 11/4 = 2.75 

This is a very simplified view at GPA. It assumes all courses are equal, which they are not. A `4` hour course is worth `4` times a `1` hour course. Even though the majority of courses are 3 hours, we still need to account for the others by using a weighted average. Here is a formula:

>`TQP` = Total Quality Points Earned 
>
>`HA` = Total Hours Attempted
>
>`TQP / HA  = GPA`

Using the first example from above we had A, B, A, B. Let's assume each class was a 3 hour class:

- TQP = A(3), B(3), A(3), B(3) = (4*3)+(3*3)+(4*3)+(3*3) = 12+9+12+9 = 42(TQP) 
- HA = 3 + 3 + 3 + 3 = 12
- GPA = 42 / 12 = 3.5 (same as above)

Change each of the A's to a 1 hour weight, and watch your GPA go down. Or add in a couple of 4 hour F's, and watch it dessimate your GPA. Anyway ...

## Resources

This project is about "design" and then possibly implementation, but mostly "**design**". Below are two resources to give you an introduction to UML. Watch the video (10 minutes) and then use the second resource (if necessary) just as a reference. The video has all the information necessary for this assignment.  
 
- [UML Video on YouTube](https://www.youtube.com/embed/UI6lqHOVHic)
- [UML Resource](../../Resources/04-UML/README.md)

Here is an example (very simple) UML Class Diagram for a project I did in OOP during Covid. It shows a `sprite` that extends a `person`. Basically the "sprite" was the visual representation of a person in our visual simulation. So we had to keep track of contacts and such. It also shows a `population` class that is composed of `people`. We talk about composition a lot in class, but we don't talk about aggregation a lot. The video will describe the difference,  and it is a term you will need to know!

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19_uml_2020.png" width="200">

Create a class relationship diagram using some online platform like `lucidcharts` or `draw.io` reresenting all the items discussed above.

### Deliverables
- Create a folder in your assignments folder called `A06`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.
  - Make sure your banner is readable and does NOT have blank lines between every other row.

```
2143 
P02
Name
```