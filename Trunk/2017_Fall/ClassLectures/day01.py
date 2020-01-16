import random

# simple print!
print("hello world")

# create a list
a = []

# prints the entire list
print(a)

# adds to the end of the list
a.append(3)

print(a)

# adds to the end of the list
a.append(5)

print(a)

# adds to the end of the list, and python doesn't care
# what a list holds. It can a mixture of all types.
a.append("mcdonalds")

print(a)

# I can also append alist to a list.
# Lists of lists is how we represent multi-dimensional data (like 2D arrays)
a.append([1,2,3,'a','b'])

print(a)

s = "hello "
t = "world"

st = s + t

# python 'overloads' the `+` sign to perform a concetenation
# when adding strings.
print(st)

# simple loop that loops 10 times
# the 'range' function returns a 'list' in this case
# the list = [0,1,2,3,4,5,6,7,8,9]
for i in range(10):
  # appand a random integer between 0 and 100
  a.append(random.randint(0,100))

# This loop  'iterates' over the 'container' 'a' placing
# subsequent values in x
for x in a:
  print(x)

# Another way of looping over a container (list). 
# This has a more traditional c++ 'feel' to it.
for j in range(len(a)):
  print(a[j])

print()

# print the last element in a list
print(a[len(a)-1])

# print the last element in a list (cooler way)
print(a[-1])

# Prints a "slice" of the list. In this case 2,3,4 (not 5).
print(a[2:5])


# Loop and jump by two's. Remember the range function takes different param numbers.
# 1. param = size of list to return
# 2. params = starting value, ending value that list will contain
# 3. params = same as 2. but adds an 'increment by' value as the third param
for i in range(0,len(a),2):
  print(a[i])

print(a)

#Insert a value into a position in the list, without overwriting another value
a.insert(7,'dont jack my list')


# This would overwrite value at a[7]
# Or error if index did not exist
a[7] = 'dont jack my list'

print(a)

# Just like appending to the list
a.insert(len(a),'please work')

print(a)

# Should error, but defaults to appending to end of list
a.insert(len(a)+3,'hmmmm')

# prints second to last item
print(a[-2])

# errors
a[len(a)+2] = '999999'
  

