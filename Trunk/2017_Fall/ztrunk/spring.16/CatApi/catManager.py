#NjYwMTQ

import xmltodict
import urllib2
import json

# url = 'http://thecatapi.com/api/images/get?format=xml&results_per_page=1'
# wget.download(url, bar=bar_thermometer)

response = urllib2.urlopen('http://thecatapi.com/api/images/get?format=xml&results_per_page=3')
xml = response.read()

# with open('path/to/file.xml') as fd:
#     doc = xmltodict.parse(fd.read())


doc = xmltodict.parse(xml)

for image in doc['response']['data']['images']['image']:
    print image