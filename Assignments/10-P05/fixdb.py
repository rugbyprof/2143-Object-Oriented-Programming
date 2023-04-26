import json

with open("database.json") as f:
    data = json.load(f)

newdata = {}

for k, v in data.items():
    print(k)
    newdata[k] = []
    for item in data[k]:
        if "classes" in item:
            del item["classes"]
        newdata[k].append(item)

print(newdata)
with open("database_fixed.json", "w") as f:
    json.dump(newdata, f)
