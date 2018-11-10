Composition is a way of aggregating objects together by making some objects attributes of other objects.
According to some formal definitions the term composition implies that the two objects are quite strongly linked – one object can be thought of as belonging exclusively to the other object. If the owner object ceases to exist, the owned object will probably cease to exist as well. If the link between two objects is weaker, and neither object has exclusive ownership of the other, it can also be called aggregation.  
Source: [ [1] ]

Here are four classes which show several examples of aggregation and composition:

```python
class Student:
    def __init__(self, name, student_number):
        self.name = name
        self.student_number = student_number
        self.classes = []

    def enrol(self, course_running):
        self.classes.append(course_running)
        course_running.add_student(self)


class Department:
    def __init__(self, name, department_code):
        self.name = name
        self.department_code = department_code
        self.courses = {}

    def add_course(self, description, course_code, credits):
        self.courses[course_code] = Course(description, course_code, credits, self)
        return self.courses[course_code]


class Course:
    def __init__(self, description, course_code, credits, department):
        self.description = description
        self.course_code = course_code
        self.credits = credits
        self.department = department
        self.department.add_course(self)

        self.runnings = []

    def add_running(self, year):
        self.runnings.append(CourseRunning(self, year))
        return self.runnings[-1]


class CourseRunning:
    def __init__(self, course, year):
        self.course = course
        self.year = year
        self.students = []

    def add_student(self, student):
        self.students.append(student)


maths_dept = Department("Mathematics and Applied Mathematics", "MAM")
mam1000w = maths_dept.add_course("Mathematics 1000", "MAM1000W", 1)
mam1000w_2013 = mam1000w.add_running(2013)

bob = Student("Bob", "Smith")
bob.enrol(mam1000w_2013)
```
Why are there two classes which both describe a course? This is an example of the way that translation of real-life concepts into objects in your code may not always be as straightforward as it appears. Would it have made sense to have a single course object which has both description, code and department attributes and a list of students?
There are two distinct concepts, both of which can be called a “course”, that we need to represent: one is the theoretical idea of a course, which is offered by a department every year and always has the same name and code, and the other is the course as it is run in a particular year, each time with a different group of enrolled students. We have represented these two concepts by two separate classes which are linked to each other. Course is the theoretical description of a course, and CourseRunning is the concrete instance of a course.

We have defined several relationships between these classes:

1.A student can be enrolled in several courses (CourseRunning objects), and a course (CourseRunning) can have multiple students enrolled in it in a particular year, so this is a many-to-many relationship. A student knows about all his or her courses, and a course has a record of all enrolled students, so this is a bidirectional relationship. These objects aren’t very strongly coupled – a student can exist independently of a course, and a course can exist independently of a student.

2.A department offers multiple courses (Course objects), but in our implementation a course can only have a single department – this is a one-to-many relationship. It is also bidirectional. Furthermore, these objects are more strongly coupled – you can say that a department owns a course. The course cannot exist without the department.

3.A similar relationship exists between a course and its “runnings”: it is also bidirectional, one-to-many and strongly coupled – it wouldn’t make sense for “MAM1000W run in 2013” to exist on its own in the absence of “MAM1000W”.
Sources:

1. http://python-textbok.readthedocs.org/en/1.0/Object_Oriented_Programming.html#composition

[1]:http://python-textbok.readthedocs.org/en/1.0/Object_Oriented_Programming.html#composition