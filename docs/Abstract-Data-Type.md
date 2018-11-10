# Abstract Data Types #

![ADTPic](http://itdoc.hitachi.co.jp/manuals/3020/3020635100e/FIGURE/ZU030270.GIF)

In computer science, an abstract data type (ADT) is a mathematical model for data types where a data type is defined by its behavior (semantics) from the point of view of a user of the data, specifically in terms of possible values, possible operations on data of this type, and the behavior of these operations[1].





##Advantages#
#### Encapsulation#

Abstraction provides a promise that any implementation of the ADT has certain properties and abilities; knowing these is all that is required to make use of an ADT object. The user does not need any technical knowledge of how the implementation works to use the ADT. In this way, the implementation may be complex but will be encapsulated in a simple interface when it is actually used[2].

#### Localization of Change#

Code that uses an ADT object will not need to be edited if the implementation of the ADT is changed. Since any changes to the implementation must still comply with the interface, and since code using an ADT object may only refer to properties and abilities specified in the interface, changes may be made to the implementation without requiring any changes in code where the ADT is used[3].

#### Flexibility#

Different implementations of the ADT, having all the same properties and abilities, are equivalent and may be used somewhat interchangeably in code that uses the ADT. This gives a great deal of flexibility when using ADT objects in different situations. For example, different implementations of the ADT may be more efficient in different situations; it is possible to use each in the situation where they are preferable, thus increasing overall efficiency[4].


#cited sources#
[1],[2],[3],[4]https://en.wikipedia.org/wiki/Abstract_data_type