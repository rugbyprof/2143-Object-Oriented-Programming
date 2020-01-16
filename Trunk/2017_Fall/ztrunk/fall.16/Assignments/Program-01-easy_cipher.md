# Program 1 - Easy Cipher
Due: October 3<sup>rd</sup> by class time.

### Requirements

### Decryption
- Using the starter code [HERE](../simple_cipher_starter.py) complete the `decrypt` method so that **bob** can read **alices's** message.
- Running the starter (and inputting: hello world) will result in the following:

```
Message: hello world
plainText: hello world
cipherText: KHOORZRUOG
cleanText: HELLOWORLD
shift: 3

plainText: None
cipherText: KHOORZRUOG
cleanText: None
shift: 3
```

- Notice that **Bob's** output shows `None` for plainText and cleanText, we need to fix that. 

### String Cleaning

- Let's say I input the following: #hello-world, What's up!!!
- It would end up like the following

```
Message: #hello-world, What's up!!!
plainText: #hello-world, What's up!!!
cipherText: ZKHOORJZRUOGIZKDWDVXSXXX
cleanText: #HELLO-WORLD,WHAT'SUP!!!
shift: 3

plainText: None
cipherText: ZKHOORJZRUOGIZKDWDVXSXXX
cleanText: None
shift: 3
```

- It may end up working ok, but I want us to only use the letters A-Z and 0-9 (alpha numeric) before the string gets encrypted and decrypted. 
- So we need to add additional cleaning the the `cleanData` method to achieve this. 
- Best way is to use a regular expression (google if you like) but below is an ok solution.
- Hint: 

```python
AlphaNumeric = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9']

if not '#' in AlphaNumeric:
    print("not in there!")
else;
    print("it's alphanumeric") 
```

### Comments

- You should complete the remainder of the commenting for the methods, and for any code you might add that needs it.


### Tests

If your code doesn't provide the same output as below, something is wrong. The test 
should first encrypt the text, then decrypt the text and compare the output.

- Test1:

```
Input: hello world
Output: HELLOWORLD
```

- Test2:
```
Input: hello           world
Output: HELLOWORLD
```

- Test3:
```
Input:       good morn*ing,viet()nam ---1+-9*6 9
Output: GOODMORNINGVIETNAM1969
```

- Test4:
```
Input: @th   e g#oo---d th(e b&ad an )d th_)e ug&%$ly((
Output: THEGOODTHEBADANDTHEUGLY
```


