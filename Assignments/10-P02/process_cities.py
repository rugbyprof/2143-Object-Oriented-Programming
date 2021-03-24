import json
import random

with open("cities.json") as f:
    data = json.loads(f.read())

#print(data)
print("digraph")
print(len(data))
for city in data:
    print(city['code'],city['name'].replace(' ','-'))
print(1000)
for i in range(1000):
    r1 = random.randint(0,len(data)-1)
    r2 = random.randint(0,len(data)-1)
    r3 = random.randint(100,1000)
    print(data[r1]['code'],'',data[r2]['code'],'',r3)