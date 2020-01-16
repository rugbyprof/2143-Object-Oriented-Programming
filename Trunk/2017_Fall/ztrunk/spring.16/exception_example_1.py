lst1 = [1,2,3,3,4,5,6,5,4,3,4,5,0,9,8,7,6,6]
lst2 = [2,3,4,5,6,4,3,4,5,6,5,4,5,1,2,3,2,1]

for i in range(len(lst1)):
    try:
        print(lst2[i] / lst1[i])
    except ZeroDivisionError:
        print( "Silly wabbit, you can't divide by zero!")
    

dict = {'one':1,'two':2,'three':3,'four':4,'five':5}


try:
    print(dict['six'])
except KeyError:
    print( "Key doesn't exist!")