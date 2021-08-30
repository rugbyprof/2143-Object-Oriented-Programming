from random import randint 

with open("input.dat",'w') as f:
    for i in range(33):
        f.write(f"{randint(1,99)}\n")

