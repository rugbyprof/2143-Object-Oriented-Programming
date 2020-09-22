## Difference between Abstraction and Encapsulation

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/abs_vs_enc_2143_2020.jpg">

### Definition of Abstraction

Abstraction is an OOP concept that focuses only on relevant data of an object. It hides the
background details and emphasizes the essential data points for reducing the complexity and increase
efficiency. It generally retains only information which is most relevant for that specific process.
Abstraction method mainly focusses on the idea instead of actual functioning.

### Definition of Encapsulation

Encapsulation is a method of making a complex system easier to handle for end users. The user need
not worry about internal details and complexities of the system. Encapsulation is a process of
wrapping the data and the code, that operate on the data into a single entity. You can assume it as
a protective wrapper that stops random access of code defined outside that wrapper.


### Why you need Abstraction?

Here, are the main reasons why abstraction is needed for Object-Oriented Programming:

  - Helps you to simplify the representation of the [domain models](https://en.wikipedia.org/wiki/Domain_model).
  - Abstraction hides the irrelevant details found in the code.
  - Abstraction helps you to partition the program into many independent concepts.
  - Offers the greatest flexibility when using ADT(Abstract Data Type) objects in different
    situations

### Why you need Encapsulation?

The main advantages of encapsulation are

  - It improves the maintainability of an application.
  - Offers flexibility to the user to use the system very easily
  - Helps the developers to organize the code better
  - Makes the overall coding process easier, as you are only concerned with what another class does,
    not how it does it
  - This method helps the developers to be more 'objective' and result oriented.
  - Encapsulated Code is quite flexible and easy to change with new requirements.
  - Encapsulation makes unit testing easy.
  - It allows you to reduce coupling of modules and increases cohesion inside a module as all piece
    of one thing are encapsulated in one place.
  - Encapsulation helps you to change a part of code without affecting other parts of the code.
  - Improves the code readability of the Application
  - Enhanced security and makes maintenance of application easier
  - The encapsulation interface only allows for well-defined interaction.

### Example of Abstraction

Suppose you want to create a banking application and you are asked to collect all the information
about your customer. There are chances that you will come up with the following information about
the customer.

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/abstraction_in_oops_112.png" width="300">

But, not all of the above information is required to create a banking application.



So, you need to select only the useful information for your banking application from that pool. Data
like name, address, tax information, etc. make sense for a banking application.

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/abstraction_in_oops_2.png" width="200">


Since we have fetched/removed/selected the customer information from a larger pool, the process is
referred to as Abstraction.

However, the same information once extracted can be used for a wide range of applications. For
instance, you can use the same data for hospital application, job portal application, a Government
database, etc. with little or no modification. Hence, it becomes your Master Data. This is an
advantage of Abstraction.

### Example of Encapsulation

Let's take an example of mobile device. With the help of mobile devices, you can perform various
functions like taking a picture, sending a message, recording video/ audio, access the web and much
more.

The features mentioned above are functionalities of most of the smartphone. However, you don't need
to understand the internal functioning details of those features before using this program. Example,
you don't need to know how your camera calculates gamma correction or identifies a human face in an
image. You just need to learn the software interface. This is encapsulation.

### Abstraction Vs. Encapsulation

[![](/images/1/032219_1030_Differenceb4.png)](/images/1/032219_1030_Differenceb4.png)

|                |                                                                                   |                                                                                                                   |
| :------------- | :-------------------------------------------------------------------------------- | :---------------------------------------------------------------------------------------------------------------- |
| **Parameter**  | **Abstraction**                                                                   | **Encapsulation**                                                                                                 |
| Use for        | Abstraction solves the problem and issues that arise at the design stage.         | Encapsulation solves the problem and issue that arise at the implementation stage.                                |
| Focus          | Abstraction allows you to focus on what the object does instead of how it does it | Encapsulation enables you to hide the code and data into a single unit to secure the data from the outside world. |
| Implementation | You can use abstraction using Interface and Abstract Class.                       | You can implement encapsulation using Access Modifiers (Public, Protected & Private.)                             |
| Focuses        | Focus mainly on what should be done.                                              | Focus primarily on how it should be done.                                                                         |
| Application    | During design level.                                                              | During the Implementation level.                                                                                  |



## KEY DIFFERENCE

  - Abstraction shows only useful data by providing the most necessary details whereas Encapsulation
    wraps code and data for necessary information.
  - Abstraction is focused mainly on what should be done while Encapsulation is focused on how it
    should be done.
  - Abstraction hides complexity by giving you a more abstract picture while Encapsulation hides
    internal working so that you can change it later.
  - Abstraction helps you to partition the program into many independent portions whereas
    Encapsulation is easy to change with new requirements.
  - Abstraction solves problem at design level while Encapsulation solves problem at implementation
    level.
  - Abstraction hides the irrelevant details found in the code whereas Encapsulation helps
    developers to organize the entire code easily.

