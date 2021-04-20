class Borg:
    __shared_state = {}
    def __init__(self):
        self.__dict__ = self.__shared_state


# class Request:

#     count=0
    

#     def __init__(self):
#         self.number = type(self).count    # modifies the instance variable "this->number"
#         type(self).count += 1               # modifies the class variable "Request::count"
    
class Request:

    count = 0

    def get_count(self):
        return type(self).count

    def set_count(self,val):
        type(self).count = val

    count = property(get_count, set_count)
    


def foo(fname,lname,ssn):
    """This function does something with a person. 
        Params:
            string fname : duh first name
            string lname : duh last name
            string ssn   : social security number
    """
    print(f"{fname}, {lname}, {ssn}")

    pass

class Person:
    def __init__(self,fname=None,lname=None,age=None):
        self._fname = fname
        self._lname = lname
        self._age = age

    def setFname(self,newname):
        self._fname = newname

    def __str__(self):
        return f'{self._fname} {self._lname} {self._age}'

class Student(Person):
    def __init__(self,fname=None,lname=None,age=None,grades=[]):
        self._grades = grades
        super().__init__(fname,lname,age)

    # def setFname(self,newname):
    #     self._fname = newname.upper()

    def __str__(self):
        s = super().__str__()
        s += ' ['
        for grade in self._grades:
            s += str(grade) + ","

        s = s[:-1] + ']'
        return s
    



setattr(foo, 'fname', 'Billy Bob' )
setattr(foo, 'lname', 'Dorksnapper' )
setattr(foo, 'ssn', '111-23-4567' )
print(getattr(foo, 'ssn'))
foo.gender ='male'
print(foo.gender)
print(foo.fname)
print(foo.ssn)

print(foo.__doc__)

a = Request()
b = Request()

print(a.count)

x1 = Request()
x2 = Request()
x1.count = 50
assert x2.count == x1.count  # no error
assert x2.count == 50    # the property is synced

print(x2.count)

p1 = Student('Juanita','Sandovol','21',[88,99,89])

print(p1)

print(p1._grades)

p1.setFname("Sally")

print(p1)
