# Encapsulation
While not exactly common in python encapsulation is an important OOP concept. Encapsulation boils down to hiding or limiting access to data or data manipulators in a class. This allows for user accessed data and methods to be separated from the business logic. Keeping the data manipulation private and away from the user allows for changes and additions to be made to the class more easily.    

Wiki definition:
    If a class disallows calling code from accessing internal object data and forces access through methods only, this is a strong form of abstraction or information hiding known as encapsulation. Some languages (Java, for example) let classes enforce access restrictions explicitly, for example denoting internal data with the private keyword and designating methods intended for use by code outside the class with the public keyword. Methods may also be designed public, private, or intermediate levels such as protected (which typically allows access from other objects of the same class, but not objects of a different class). In other languages (like Python) this is enforced only by convention (for example, private methods may have names that start with an underscore). Encapsulation prevents external code from being concerned with the internal workings of an object. This facilitates code refactoring, for example allowing the author of the class to change how objects of that class represent their data internally without changing any external code (as long as "public" method calls work the same way).  



### Example of Encapsulation in php
```PHP
<?php
class Account {
    /**
     * How much money is currently in the account
     * @var float
     */
    private $accountBalance;

    /**
     * @param float $currentAccountBalance Initialize account to this dollar amount
     */
    public function __construct($currentAccountBalance) {
        $this->accountBalance = $currentAccountBalance;
    }

    /**
     * Add money to account
     * @param float $money Dollars to add to balance
     * @return void
     */
    public function add($money) {
        $this->accountBalance += $money;
    }

    /**
     * Remove money from account
     * @param float $money Dollars to subtract from balance
     * @throws Exception
     * @return void
     */
    public function withdraw($money) {
        if ($this->accountBalance < $money) {
            throw new Exception('Cannot withdraw $' . $money . ' from account as it contains $' . $this->accountBalance);
        }
        $this->accountBalance -= $money;
    }

    /**
     * Get current account balance, that takes all additions and subtractions into consideration.
     * @return float
     */
    public function getAccountBalance() {
        return $this->accountBalance;
    }
}

// Create a new object from the Account class with a starting balance of $500.00
$myAccount = new Account(500.00);

// We have clearly defined methods for adding and subtracting money from the Account
// If we didn't have a method for withdraw(), nothing would prevent us from withdrawing more money than was available in the account
$myAccount->add(10.24);
$myAccount->withdraw(4.45);

// Get the current balance
$accountBalance = $myAccount->getAccountBalance();
echo 'My Account Balance: $' . $accountBalance; // 505.79

// Our code forbids us from withdrawing more than we have
$myAccount->withdraw(600.00); // Exception Message: Cannot withdraw $600 from account as it contains $505.79
```
[Code Source](https://en.wikipedia.org/wiki/Encapsulation_%28computer_programming%29)
[Wiki Source](https://en.wikipedia.org/wiki/Encapsulation_%28computer_programming%29)