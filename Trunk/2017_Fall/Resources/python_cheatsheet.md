## Python Cheat Sheet:
### Builtin Methods:
- ___`input([prompt])`___ -> str
    - Read a string from standard input. The trailing newline is stripped. The prompt string, if given, is printed without a trailing newline before reading.
- ___`abs(x)`___ -> number
    - Return the absolute value of x.
- ___`chr(i)`___ -> character
    - Return a string of one character whose ASCII code is the integer i. For example, chr(97) returns the string 'a'. This is the inverse of ord().  
- ___`int(x)`___ -> int
    - Convert x to an integer, if possible. A floating point argument will be truncated towards zero.
- ___`len(x)`___ -> int
    - Return the length of the list, tuple, dict, or string x.
- ___`max(iterable)`___ -> object
- ___`max(a, b, c, ...)`___ -> object
    - With a single iterable argument, return its largest item. With two or more arguments, return the largest argument.
- ___`min(iterable)`___ -> object
- ___`min(a, b, c, ...)`___ -> object
    - With a single iterable argument, return its smallest item.
    - With two or more arguments, return the smallest argument.
- ___`ord(c)`___ -> int
    - Given a string of length one, return an integer representing the Unicode code point of the character when the argument is a unicode object, or the value of the byte when the argument is an 8-bit string. For example, ord('a') returns the integer 97 
- ___`print(value, ..., sep=' ', end='\n')`___ -> NoneType
    - Prints the values. Optional keyword arguments:
    - sep: string inserted between values, default a space.
    - end: string appended after the last value, default a newline.
- ___`open(name[, mode])`___ -> file open for reading, writing, or appending
    - Open a file. Legal modes are "r" (read), "w" (write), and "a" (append).
- ___`range([start], stop, [step])`___ -> list-like-object of int
    - Return the integers starting with start and ending with stop - 1 with step specifying the amount to increment (or decrement).
    - If start is not specified, the list starts at 0. If step is not specified, the values are incremented by 1.
    
#### random:

- ___`random.randint(a, b)`___
    - Return a random integer N such that a <= N <= b.
- ___`random.random()`___
    - Return the next random floating point number in the range [0.0, 1.0).
    
#### dict:

- ___`D[k]`___ -> object
    - Produce the value associated with the key k in D.
- ___`del D[k]`___
    - Remove D[k] from D.
- ___`k in d`___ -> bool
    - Produce True if k is a key in D and False otherwise.
- ___`D.get(k)`___ -> object
    - Return D[k] if k in D, otherwise return None.
- ___`D.keys()`___ -> list-like-object of object
    - Return the keys of D.
- ___`D.values()`___ -> list-like-object of object
    - Return the values associated with the keys of D.
- ___`D.items()`___ -> list-like-object of tuple of (object, object)
    - Return the (key, value) pairs of D, as 2-tuples.
    
#### file open for reading:

- ___`F = open('workfile', 'r')`___
    - open a file for reading
- ___`F.close()`___ -> NoneType
    - Close the file.
- ___`F.read()`___ -> str
    - Read until EOF (End Of File) is reached, and return as a string.
- ___`F.readline()`___ -> str
    - Read and return the next line from the file, as a string. Retain newline.
    - Return an empty string at EOF (End Of File).
- ___`F.readlines()`___ -> list of str
    - Return a list of the lines from the file. Each string ends in a newline.
- Loop through file printing every line:

```
for line in f:
        print line
```

#### file open for writing:

- ___`F = open('workfile', 'w')`___
    - open a file for writing
- ___`F.close()`___ -> NoneType
    - Close the file.
- ___`F.write(x)`___ -> int
    - Write the string x to file F and return the number of characters written.
    
#### list:

- ___`x in L`___ -> bool
    - Produce True if x is in L and False otherwise.
- ___`L.append(x)`___ -> NoneType
    - Append x to the end of the list L.
- ___`L.extend(iterable)`___ -> NoneType
    - Extend list L by appending elements from the iterable. Strings and lists are iterables whose elements are characters and list items respectively.
- ___`L.index(value)`___ -> int
    - Return the lowest index of value in L.
- ___`L.insert(index, x)`___ -> NoneType
    - Insert x at position index.
- ___`L.pop()`___ -> object
    - Remove and return the last item from L.
- ___`L.remove(value)`___ -> NoneType
    - Remove the first occurrence of value from L.
- ___`L.reverse()`___ -> NoneType
    - Reverse *IN PLACE*.
- ___`L.sort()`___ -> NoneType
    - Sort the list in ascending order *IN PLACE*.
    
#### str:

- ___`x in s`___ -> bool
    - Produce True if and only if x is in s.
- ___`str(x)`___ -> str
    - Convert an object into its string representation, if possible.
- ___`S.count(sub[, start[, end]])`___ -> int
    - Return the number of non-overlapping occurrences of substring sub in string S[start:end]. 
    - Optional arguments start and end are interpreted as in slice notation.
- ___`S.find(sub[, i])`___ -> int
    - Return the lowest index in S (starting at S[i], if i is given) where the string sub is found or -1 if sub does not occur in S.
- ___`S.index(sub)`___ -> int
    - Like find but raises an exception if sub does not occur in S.
- ___`S.isalpha()`___ -> bool
    - Return True if and only if all characters in S are alphabetic and there is at least one character in S.
- ___`S.isdigit()`___ -> bool
    - Return True if all characters in S are digits and there is at least one character in S, and False otherwise.
- ___`S.islower()`___ -> bool
    - Return True if and only if all cased characters in S are lowercase and there is at least one cased character in S.
- ___`S.isupper()`___ -> bool
    - Return True if and only if all cased characters in S are uppercase and there is at least one cased character in S.
- ___`str.join(sequence)`___ -> string
    - The method join() returns a string in which the string elements of sequence have been joined by str separator.
- ___`S.lower()`___ -> str
    - Return a copy of the string S converted to lowercase.
- ___`S.lstrip([chars])`___ -> str
    - Return a copy of the string S with leading whitespace removed.
    - If chars is given and not None, remove characters in chars instead.
- ___`S.replace(old, new)`___ -> str
    - Return a copy of string S with all occurrences of the string old replaced with the string new.
- ___`S.rstrip([chars])`___ -> str
    - Return a copy of the string S with trailing whitespace removed.
    - If chars is given and not None, remove characters in chars instead.
- ___`S.split([sep])`___ -> list of str
    - Return a list of the words in S, using string sep as the separator and any whitespace string if sep is not specified.
- ___`S.strip([chars])`___ -> str
    - Return a copy of S with leading and trailing whitespace removed.
    - If chars is given and not None, remove characters in chars instead.
- ___`S.upper()`___ -> str
    - Return a copy of the string S converted to uppercase.

#### Some Common Exceptions:

```python
try:
    ...
except SomeException:
    tb = sys.exc_info()[2]
    raise OtherException(...).with_traceback(tb)
```


- ___`exception TypeError`___
>Raised when an operation or function is applied to an object of inappropriate type. The associated value is a string giving details about the type mismatch.

- ___`exception ValueError`___
>Raised when a built-in operation or function receives an argument that has the right type but an inappropriate value, and the situation is not described by a more precise exception such as IndexError.

- ___`exception ZeroDivisionError`___
>Raised when the second argument of a division or modulo operation is zero. The associated value is a string indicating the type of the operands and the operation.

- ___`exception FileExistsError`___
>Raised when trying to create a file or directory which already exists. Corresponds to errno EEXIST.

- ___`exception FileNotFoundError'___
>Raised when a file or directory is requested but doesn’t exist. Corresponds to errno ENOENT.
