# Observer Pattern


## Example 1

```python
class Observable:
    def __init__(self):
        self.__observers = []

    def register_observer(self, observer):
        self.__observers.append(observer)
    
    def notify_observers(self, *args, **kwargs):
        for observer in self.__observers:
            observer.notify(self, *args, **kwargs)
 
 
class Observer:
    def __init__(self, observable):
        observable.register_observer(self)

    def notify(self, observable, *args, **kwargs):
        print('Got', args, kwargs, 'From', observable)
 
 
subject = Observable()
observer = Observer(subject)
subject.notify_observers('test')
```

## Example 2

Let's say there is a TechForumon in which technical posts are published by different users. The users might subscribe to receive notifications when any of the other users publishes a new post. 

So we have: 

- A `TechForum` object
- Some list of objects that registered with `TechForum` object.

Any object registered with the `TechForum` object, is an **observer**, and will be notified of any new posts. Along with the new post notification, the title of the post is sent.

```python
"""Python snippet for a Technical Forum where technical posts 
   are published by different users. It uses the Observer pattern. 
   
   Wikipedia:
   The observer pattern (a subset of the publish/subscribe pattern) 
   is a software design pattern in which an object, called the subject, 
   maintains a list of its dependants, called observers, and notifies 
   them automatically of any state changes, usually by calling one of 
   their methods. It is mainly used to implement distributed event 
   handling systems.
"""

class Publisher:
  def __init__(self):
    #make it uninheritable
    pass
  def register(self):
    #OVERRIDE
    pass
  def unregister(self):
    #OVERRIDE
    pass
  def notifyAll(self):
    #OVERRIDE
    pass

class TechForum(Publisher):
  def __init__(self):
    self._listOfUsers = []
    self.postname = None

  def register(self, userObj):
    # Register objects that would receive notifications
    if userObj not in self._listOfUsers:
      self._listOfUsers.append(userObj)

  def unregister(self, userObj):
    # Unregister objects that wont receive further notification
      self._listOfUsers.remove(userObj)

  def notifyAll(self):
    # Notify changes that occur in the main object to the 
    # registered objects (Subscriber object) 
    # via registered object’s method (Notify method)

    for objects in self._listOfUsers:
      objects.notify(self.postname)
 
  def writeNewPost(self, postname):
    # User writes a post. Triggers a state change that 
    # leads the Publisher to call its notification method
   
    self.postname = postname
    # Post is published and notification is sent to all
    self.notifyAll()

class Subscriber:
  def __init__(self):
    #make it uninheritable
    pass
  def notify(self):
    #OVERRIDE
    pass

class User1(Subscriber):
  def notify(self,postname):
    # A method that is used by the Publisher Class
    # to notify the objects (Subscribers) registered 
    # with it of any change that occurs
    
    print 'User1 notfied of a new post: %s' % postname

class User2(Subscriber):
  def notify(self, postname):
    # A method that is used by the Publisher Class
    # to notify the objects (Subscribers) registered 
    # with it of any change that occurs
    
    print 'User2 notfied of a new post: %s' % postname

class SisterSites(Subscriber):
  def __init__(self):
    self._sisterWebsites = ["Webpage1","Webpage2","Webpage3"]
  def notify(self, postname):
    for site in self._sisterWebsites:
      # Send updates by any means
      print "Sent nofication to site: %s" % site

if __name__ == "__main__":
  techForum = TechForum()
  user1 = User1()
  user2 = User2()

  sites = SisterSites()

  techForum.register(user1)
  techForum.register(user2)
  techForum.register(sites)

  techForum.writeNewPost("Design patterns in python are awesome")

  techForum.unregister(user2)

  techForum.writeNewPost("This is an Observer pattern in python")
  ```
  
