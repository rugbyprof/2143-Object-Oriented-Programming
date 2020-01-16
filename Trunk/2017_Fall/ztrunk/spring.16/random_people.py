import json
import requests

people = []

calls = 10
res_size = 1000

for i in range(calls):
    url = 'http://api.randomuser.me/?nat=us&results=' + str(res_size)
    response = requests.get(url)
    data = response.json()
    print(i)

    people.extend(data['results'])

filename = 'random_people.'+str(calls*res_size)+'.json'
fp = open(filename, 'w')
print(len(people))

fp.write(json.dumps(people))

# with open('people.json') as data_file:    
#     data = json.load(data_file)

# pp = pprint.PrettyPrinter(depth=4)
# pp.pprint(data['results'])

# print(len(data['results']))
# for person in data['results']:
#     pp.pprint(person['user'])
#     print()