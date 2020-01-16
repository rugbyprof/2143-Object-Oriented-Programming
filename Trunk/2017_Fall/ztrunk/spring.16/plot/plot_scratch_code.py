import matplotlib.pyplot as plt
from yahoo_finance import Share

"""
Scratch pad from class below:
"""    

"""
Example usage of the yahoo finance library in which each stock is 
stored in it's own variable (not best solution)
"""

# Create an instance of the 'Share' class instantiated with the symbol 'YHOO'
# and assign it to the variable 'banana' 
banana = Share('YHOO')
openingPrice = banana.get_open()    # Get opening price
currentPrice = banana.get_price()   # Get opening price

# Get the historical prices for IBM for the year 2015
historicalData = banana.get_historical('2015-01-01', '2015-12-31')

# Create an instance of the 'Share' class instantiated with the symbol 'IBM'
# and assign it to the variable 'ibm' 
ibm = Share('IBM')
openingPrice = ibm.get_open()       # Get opening price
currentPrice = ibm.get_price()      # Get current price

# Get the historical prices for IBM for the year 2015
historicalData = ibm.get_historical('2015-01-01', '2015-12-31')

stock = Share('CUDA')
openingPrice = stock.get_open()     # Get opening price
currentPrice = stock.get_price()    # Get current price

# Get the historical prices for IBM for the year 2015
historicalData = stock.get_historical('2015-01-01', '2015-12-31')

"""
Remember the dictionary type in python? Here's a dictionary that holds
key value pairs.
"""
Shares = {}

# Assign stock prices to our "shares" dictionary
Shares['IBM'] = 111.11
Shares['GOOG'] = 523.32 


"""
Now lets use a dictionary that holds more than just key=>values 
Let use a dictionary of dictionaries to store our yahoo finance data.
"""

# Create a dictionary
Shares = {}  

# Create a dictionary
Shares = {}            

# A new dictionary assigned to a specific key (Dictionary of Dictionaries)
Shares['IBM'] = {}      

# Assign an instance of the yahoo finance class (Share) to the key 'object'  
# in the dictionary access with the key 'IBM'
Shares['IBM']['object'] = Share('IBM')   

# Get the opening price for IBM                  
Shares['IBM']['open'] = Shares['IBM']['object'].get_open() 

# Get the current price for IBM  
Shares['IBM']['price'] = Shares['IBM']['object'].get_price() 

# Get the historical prices for IBM for the year 2015
Shares['IBM']['historical'] = Shares['IBM']['object'].get_historical('2015-01-01', '2015-12-31')

# Now do the same thing for yahoo
Shares['YHOO'] = {}  
Shares['YHOO']['object'] = Share('YHOO')
Shares['YHOO']['open'] = Shares['YHOO']['object'].get_open() 
Shares['YHOO']['price'] = Shares['YHOO']['object'].get_price()
Shares['YHOO']['historical'] = Shares['YHOO']['object'].get_historical('2015-01-01', '2015-12-31')


"""
Printing out the entire container of data doesn't really give us access to all the data.
"""
print(Shares)

"""
We need to traverse the Dictionary of Dictionaries to gain access to the data
"""

for key in Shares:
    print(key,Shares[key])
    for subkey in Shares[key]:
        print(subkey,Shares[key][subkey])
        
        
        
"""
And lastly, here is a simple plot with two randomly generated lines
"""
L = [random.randint(10, 100) for i in range(25)]
M = [random.randint(10, 100) for i in range(25)] 
plt.plot(L)
plt.plot(M)
plt.ylabel('Random Numbers')
plt.show()