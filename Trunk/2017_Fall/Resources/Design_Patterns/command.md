# Command Pattern

### Overview

In object-oriented programming, the command pattern is a behavioral design pattern in which an object is used to encapsulate all information needed to perform an action or trigger an event at a later time. This information includes the method name, the object that owns the method and values for the method parameters.

Four terms always associated with the command pattern are ***command***, ***receiver***, ***invoker*** and ***client***. 

- A ***command*** object knows about ***receiver*** and invokes a method of the ***receiver***. 
- Values for parameters of the ***receiver*** method are stored in the ***command***. 
- The ***receiver*** then does the work. 
- An ***invoker*** object knows how to execute a ***command***, and optionally does bookkeeping about the ***command*** execution. 
- The ***invoker*** does not know anything about a ***concrete command***, it knows only about ***command interface***. 
- Both an ***invoker object*** and several ***command objects*** are held by a ***client object***. 
- The ***client*** decides which commands to execute at which points. To execute a ***command***, it passes the ***command object*** to the ***invoker object***. <sup>Source: [[1]]</sup>



|             Command Pattern        | 
|:------------------------------:|
| ![](https://d3vv6lp55qjaqc.cloudfront.net/items/2w1P1524472V341D3l0X/CommandDiagram.png?X-CloudApp-Visitor-Id=1094421) | 


## Definitions
1. ***Client, Source, Invoker***: the button, toolbar button, or menu item clicked, the shortcut key pressed by the user.
2. ***Command Object, Routed Command Object, Action Object***: a singleton object (e.g. there is only one CopyCommand object), which knows about shortcut keys, button images, command text, etc. related to the command. A source/invoker object calls the Command/Action object's execute/performAction method. The Command/Action object notifies the appropriate source/invoker objects when the availability of a command/action has changed. This allows buttons and menu items to become inactive (grayed out) when a command/action cannot be executed/performed.
3. ***Receiver, Target Object***: the object that is about to be copied, pasted, moved, etc. The receiver object owns the method that is called by the command's execute method. The receiver is typically also the target object. For example, if the receiver object is a cursor and the method is called moveUp, then one would expect that the cursor is the target of the moveUp action. On the other hand, if the code is defined by the command object itself, the target object will be a different object entirely.
4. ***Command Object, routed event args, event object***: the object that is passed from the source to the Command/Action object, to the Target object to the code that does the work. Each button click or shortcut key results in a new command/event object. Some implementations add more information to the command/event object as it is being passed from one object (e.g. CopyCommand) to another (e.g. document section). Other implementations put command/event objects in other event objects (like a box inside a bigger box) as they move along the line, to avoid naming conflicts. (See also chain of responsibility pattern).
5. ***Handler, ExecutedRoutedEventHandler, method, function***: the actual code that does the copying, pasting, moving, etc. In some implementations the handler code is part of the command/action object. In other implementations the code is part of the Receiver/Target Object, and in yet other implementations the handler code is kept separate from the other objects.
6. ***Command Manager, Undo Manager, Scheduler, Queue, Dispatcher, Invoker***: an object that puts command/event objects on an undo stack or redo stack, or that holds on to command/event objects until other objects are ready to act on them, or that routes the command/event objects to the appropriate receiver/target object or handler code.

<sup>Source: [[1]]</sup>
## Code Example  

```python
class Switch(object):
    """The INVOKER class"""
    def __init__(self):
        self._history = ()

    @property
    def history(self):
        return self._history

    def execute(self, command):
        self._history = self._history + (command,)
        command.execute()

class Command(object):
    """The COMMAND interface"""
    def __init__(self, obj):
        self._obj = obj

    def execute(self):
        raise NotImplementedError

class TurnOnCommand(Command):
    """The COMMAND for turning on the light"""
    def execute(self):
        self._obj.turn_on()

class TurnOffCommand(Command):
    """The COMMAND for turning off the light"""
    def execute(self):
        self._obj.turn_off()

class Light(object):
    """The RECEIVER class"""
    def turn_on(self):
        print("The light is on")

    def turn_off(self):
        print("The light is off")

class LightSwitchClient(object):
    """The CLIENT class"""
    def __init__(self):
        self._lamp = Light()
        self._switch = Switch()

    @property
    def switch(self):
        return self._switch

    def press(self, cmd):
        cmd = cmd.strip().upper()
        if cmd == "ON":
            self._switch.execute(TurnOnCommand(self._lamp))
        elif cmd == "OFF":
            self._switch.execute(TurnOffCommand(self._lamp))
        else:
            print("Argument 'ON' or 'OFF' is required.")

# Execute if this file is run as a script and not imported as a module
if __name__ == "__main__":
    light_switch = LightSwitchClient()
    print("Switch ON test.")
    light_switch.press("ON")
    print("Switch OFF test.")
    light_switch.press("OFF")
    print("Invalid Command test.")
    light_switch.press("****")

    print("Command history:")
    print(light_switch.switch.history)
```
<sup>Source: [[3]]</sup>

#### Sources:
- <sup>1. https://en.wikipedia.org/wiki/Command_pattern</sup>

[1]: https://en.wikipedia.org/wiki/Command_pattern


