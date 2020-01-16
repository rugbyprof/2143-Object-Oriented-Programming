import sqlite3
import datetime
import urllib2
import urllib
import csv

conn = sqlite3.connect("guns.db")
conn.execute("DROP TABLE Guns")
conn.execute("CREATE TABLE Guns (id integer, year integer, month integer, intent text, police boolean, sex text, age integer, race text, place text, education int)")

# Specify the url
"""
"","year","month","intent","police","sex","age","race","hispanic","place","education"

Possible Queries:

Query: Determine all the different "intents"
Output:
    Homicide
    Suicide
    Undetermined
    etc.
Query: Count the occurences of each "intent"
Output:
    xxxx Homicides
    xxxx Suicides
    xxxx etc.
Query: Count the distinct races
Output:
    xxxx Asian/Pacific Islander
    xxxx Black
    xxxx Hispanic
    xxxx Native American/Native Alaskan
    xxxx White
    xxxx etc.
Query: Find the oldest victim
Query: Find the youngest victim

"""
url = 'https://raw.githubusercontent.com/fivethirtyeight/guns-data/master/full_data.csv'

# This packages the request (it doesn't make it) 
request = urllib2.Request(url)

# Sends the request and catches the response
response = urllib2.urlopen(request)

# Extracts the response
file = response.read().split("\n")

file.pop(0)

for f in file:
    f = f.replace("'","")
    f = f.replace('"','')
    items = f.split(',')
    items.pop(8)
    sql = 'INSERT INTO Guns (id,year, month, intent, police, sex, age, race, place, education) values ('
    sql += items[0] + ', '
    sql += items[1] + ', '
    sql += items[2] + ', '
    sql += "'" + items[3] + "', "
    sql += items[4] + ', '
    sql += "'" + items[5] + "', "
    sql += items[6] + ', '
    sql += "'" + items[7] + "', "
    sql += "'" + items[8] + "', "
    sql += items[9]
    sql += ")"
    print(sql)
    conn.execute(sql)
    print(items)

conn.commit()
conn.close()


