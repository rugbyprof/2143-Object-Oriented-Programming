
import urllib
import json
import pprint
import unicodedata

pp = pprint.PrettyPrinter(indent=4)

# One time cost
#link = "https://randomuser.me/api/?results=100"
#f = urllib.urlopen(link)
#myfile = f.read()

class DataBase(object):
    def __init__(self,data_file):
        f = open(data_file,'r')
        self.data = f.read()
        self.data = json.loads(self.data)
        self.data = self.data['results']

def __str__(self):
        length = len(self.data)
        emails = ""
        for entry in self.data:
            email = unicodedata.normalize('NFKD', entry['email']).encode('ascii','ignore')
            emails = emails + str(email) + ",\n"
        return "Database size: %d, \n Email:%s" % (length,emails)

    def IndexLookup(self,i):
        return self.data[i]

    def GetUserByEmail(self,id):
        for e in self.data:
            if e['email'] == id:
                return e
        return None

    def GetUserByCity(self,city):
        for e in self.data:
            if e['location']['city'] == city:
                return e
        return None

db = DataBase('people.json')

#print(db.IndexLookup(33))
#print(db)
print(db.GetUserByEmail('frederikke.poulsen@example.com'))
print(db.GetUserByCity('bergen'))
