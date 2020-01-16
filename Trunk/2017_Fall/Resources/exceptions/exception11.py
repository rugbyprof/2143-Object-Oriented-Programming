"""
defining your own exceptions
"""

# class InvalidWithdrawal(Exception):
#     pass
    
# raise InvalidWithdrawal("You don't have $50 in your account")


class InvalidWithdrawal(Exception):
    def __init__(self, balance, amount):
        super().__init__("account doesn't have ${}".format(amount))
        self.amount = amount
        self.balance = balance
        
    def overage(self):
        return self.amount - self.balance
        
    raise InvalidWithdrawal(25, 50)
    
    
"""
Here's how to handle an invalid withdrawel.
"""



try:
    raise InvalidWithdrawal(25, 50)
except InvalidWithdrawal as e:
    print("I'm sorry, but your withdrawal is "
        "more than your balance by "
        "${}".format(e.overage()))