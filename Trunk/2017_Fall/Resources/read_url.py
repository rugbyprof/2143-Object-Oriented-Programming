import urllib2
import urllib

# Specify the url
url = 'https://raw.githubusercontent.com/msorvig/cube.js/3276efff3456d16d0c220625eb409a7ba375ac00/datasets/sales.json'


# This packages the request (it doesn't make it) 
request = urllib2.Request(url)

# Sends the request and catches the response
response = urllib2.urlopen(request)

# Extracts the response
json = response.read()

# Print it out
print json 