import json
import sys

if __name__ == "__main__":
    with open("quotes.1.json") as f1:
        j1 = json.load(f1)

    with open("quotes.2.json") as f2:
        j2 = json.load(f2)


newQuotes = []
for row in j1:
    q = {}
    q["Quote"] = row["quoteText"]
    q["Author"] = row["quoteAuthor"]
    newQuotes.append(q)

for row in j2:
    q = {}
    q["Quote"] = row["Quote"]
    q["Author"] = row["Author"]
    newQuotes.append(q)

# print(newQuotes)
print(len(newQuotes))

with open("quotes_all.json", "w") as f:
    json.dump(newQuotes, f, indent=4)
