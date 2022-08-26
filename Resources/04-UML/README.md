## UML - Unified Modeling Language
#### Due: None

### What are UML Diagrams?
UML Diagrams stands for Unified Modeling Language. It is a standard which is mainly used for creating object-oriented, meaningful documentation models for any software system present in the real world. It provides us a way to develop rich models that describe the working of any software/hardware systems.

UML serves a great way of creating professional documentation which is a necessary part of any project development. UML is an essential part of creating an object-oriented design of systems. It provides you means for creating powerful models and designs for rational systems which can be understood without much difficulties.

### Characteristics of UML
1. It is a generalized modeling language.
2. It is different from software programming languages such as Python, C, C++, etc.
3. It is a pictorial language which can be used to generate powerful modeling elements.
4. It is related to object-oriented designs and analysis.
5. It has unlimited applications even outside the software industry. It can be used to visualize the workflow of a factory.

### Building Blocks

UML is an abstract view of how (in our case) objects relate together. It is a  **conceptual model** that helps us understand:

- What the objects are
- How object interact

You have to understand the entities and relationships between them before you can actually modeling a system using the components given to us by UML. However, you are familiar with most of them because they fit with the OOP way of looking at things:

- **Object**: It is a real-world entity. There are multiple objects available within a single system. It is a fundamental building block of UML.
- **Class**: A class is nothing but a container where objects and their relationships are maintained.
- **Abstraction**: It is a mechanism of representing an entity without showing the implementation details. It is used to visualize the behavior of an object.
- **Inheritance**: It is a mechanism of extending an existing class to create a new class.
- **Polymorphism**: It is a mechanism of representing an object having multiple forms which are used for different purposes.
- **Encapsulation**: It is a method of binding the object and the data together as a single unit. It ensures tight coupling between the object and the data. 

We can use these building blocks to generate UML diagrams that model our projects and let us design before actually coding them.

### What is UML Diagram?

UML Diagrams are the output of the Unified Modeling Language. It is a pictorial representation of classes, objects, and relationships between them. It is used to give a visual depiction of the functionality or a design of a system. A diagram must be clear and concise so that the viewer will readily understand it.

UML diagrams are divided into three different categories such as,

- Structural diagram
- Behavioral diagram
- Interaction diagram
  
#### Structural diagrams
Structural diagrams are used to represent a static view of a system. It represents a part of a system that makes up the structure of a system. A structural diagram shows various objects within the system.

Following are the various structural diagrams in UML:

- Class diagram
- Object diagram
- Package diagram
- Component diagram
- Deployment diagram


#### Behavioral diagrams
Any real-world system can be represented in either a static form or a dynamic form. A system is said to be complete if it is expressed in both the static and dynamic ways. The behavioral diagram represents the functioning of a system.

UML diagrams that deals with the static part of a system are called structural diagrams. UML diagrams that deals with the moving or dynamic parts of the system are called behavioral diagrams.

Following are the various behavioral diagrams in UML:

- Activity diagram
- Use case diagram
- State machine diagram

#### Interaction diagrams
Interaction diagram is nothing but a subset of behavioral diagrams. It is used to visualize the flow between various use case elements of a system. Interaction diagrams are used to show an interaction between two entities and how data flows within them.

Following are the various interaction diagrams in UML:

- Timing diagram
- Sequence diagram
- Collaboration diagram


### UML Building Blocks

These are building blocks at a higher level than the previously mentioned ones. These building blocks are the things required to develop one full UML model diagram.  Following are the basic UML building blocks:

- Things
- Relationships
- Diagrams
  
## Things
A thing can be described as any real-world entity or an object. Things are divided into various categories in UML as follows,

- Structural things
- Behavioral things
- Grouping things
- Annotational things


### Structural things
A structural thing is used to describe the static part of a model. It is used to represent the things that are visible to human eyes. Structural things are all about the physical part of a system. It is the noun of a UML model, such as a class, object, interface, collaboration, use case, component, and a node.

Structural things consist of:

#### Class:

A class is used to represent various objects. It is used to define the properties and operations of an object. In UML, we can also represent an abstract class. A class whose functionalities are not defined is called an abstract class. Any UML class notation is generally expressed as follows,

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_class_ex.png" width="200"> |
| UML Class Symbol |

#### Object:

An object is an entity which is used to describe the behavior and functions of a system. The class and object have the same notations. The only difference is that an object name is always underlined in UML.

The notation of any object in UML is given below.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_object_ex.png" width="200"> |
| UML Object Symbol |

#### Interface:

An interface is similar to a template without implementation details. A circle notation represents it. When a class implements an interface, its functionality is also implemented.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_interface_ex.png" width="100"> |
| UML Collaboration Symbol |

#### Collaboration:

It is represented by a dotted ellipse with a name written inside it.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_collaboration_ex.png" width="250"> |
| UML Interface Symbol |


#### Use-case:

Use-cases are one of the core concepts of object-oriented modeling. They are used to represent high-level functionalities and how the user will handle the system.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_use_case_ex.png" width="200"> |
| UML Use Case|



#### Actor:

It is used inside use case diagrams. The actor is an entity that interacts with the system. A user is the best example of an actor. The actor notation in UML is given below.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_actor_ex.png" width="100"> |
| UML Actor|

#### Component:

A component notation is used to represent a part of the system. It is denoted in UML like given below,

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_component_ex.png" width="200"> |
| UML Component|

#### Node:

A node is used to describe the physical part of a system. A node can be used to represent a network, server, routers, etc. Its notation is given below.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_node_ex.png" width="200"> |
| UML Node|


#### Deployment diagram:

It represents the physical hardware on which system is installed. A deployment diagram represents the physical view of a system. It denotes the communication and interaction between various parts of the system.

A deployment diagram consists of the following notations:

1. A node
2. A component
3. An artifact
4. An interface

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_deployment_dia_ex.png" width="400"> |
| Deployment Diagram|

### Behavioral things
They are the verbs of a UML model, such as interactions, activities and state machines. Behavioral things are used to represent the behavior of a system.

Behavioral things consist of:

#### State machine:

It used to describe various states of a single component throughout the software development life cycle. It is used to capture different states of a system component.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_state_mach_ex.png" width="150"> |
| State Machine|

#### Activity diagram:

An activity diagram is used to represent various activities carried out by different components of a system. It is denoted the same as that of the state machine diagram.

Activity diagram mainly contains initial state, final state, a decision box, and an action notation.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_activity_dia_ex.png" width="150"> |
| Activity Diagram|

#### Interaction diagram:

Interaction diagrams are used to visualize the message flow between various components of a system.

Sequence diagram: A sequence diagram shows interactions between one or more lifelines within real time.
The notation of a sequence diagram is given below,

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_interaction_dia_ex.png" width="250"> |
| Interaction Diagram|


### Grouping things
It is the package which is used to group semantically related modeling elements into a single cohesive unit. The package is the only grouping thing available in the UML.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_grouping_ex.png" width="200"> |
| Group|

### Annotational things
It is like a note, which may be written to the model to capture some vital information. It is similar to the yellow sticky note.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_annoational_ex.png" width="200"> |
| Annotation |


### Relationships
The relationship allows you to show on a model how two or more things relate to each other. The relationship in UML will enable you to capture meaningful connections between things. It shows how each element is associated with each other and how this association describes the functionality of an application.

Relationships in UML are categorized as follows,

- Association relationship
- Dependency relationship
- Generalization relationship
- Realization relationship

#### Association relationship
  
It is a set of links that connect elements of the UML model. It also defines how many objects are taking part in that relation. It illustrates how many elements are participating in a particular interaction.

It is denoted as a dotted line with arrowheads on both sides. Both the sides contain an element which describes the relationship. A new term multiplicity is introduced that tells us how many objects of a particular element are associated.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_association_relationship_ex.png" width="200"> |
| Association Relationship |

#### Dependency relationship

In this kind of a relationship, the source element is dependent upon the target element and may be affected by changes to it. It is one of the most important notations of UML. It defines the direction of a dependency from one object to another.

It is denoted by a dotted line with an arrow at one side.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_dependancy_rel_ex.png" width="200"> |
| Dependency Relationship |

#### Generalization relationship

It is also called as a parent-child relationship. It is a relationship between a general thing and a more specific kind of a thing. This type of relationship is used to represent the inheritance concept.

It is denoted by a straight line with a hollow arrowhead at one side.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_generalization_rel_ex.png" width="200"> |
| Generalization Relationship |


#### Realization relationship
In this, one element describes some responsibility which is not implemented and the other elements implement the functionality mentioned by the first element. Realization relationship is widely used while denoting interfaces.

It is denoted as a dotted line with a hollow arrowhead at one end.

|      |
|:-----:|
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_realization_rel_ex.png" width="200"> |
| Realization Relationship |


### Diagrams
UML diagrams are divided into three different categories such as,

1. Structural diagram
2. Behavioral diagram
3. Interaction diagram
   
### Structural Diagrams

Structural diagrams are used to represent a static view of a system. It represents a part of a system that makes up the structure of a system. A structural diagram shows various objects within the system.

Following are the various structural diagrams in UML:

- Class diagram
- Object diagram
- Package diagram
- Component diagram
- Deployment diagram


### Behavioral diagrams
Any real-world system can be represented in either a static form or a dynamic form. A system is said to be complete if it is expressed in both the static and dynamic ways. The behavioral diagram represents the functioning of a system.

UML diagrams that deals with the static part of a system are called structural diagrams. UML diagrams that deals with the moving or dynamic parts of the system are called behavioral diagrams.

Following are the various behavioral diagrams in UML:

- Activity diagram
- Use case diagram
- State machine diagram


### Interaction diagrams
Interaction diagram is nothing but a subset of behavioral diagrams. It is used to visualize the flow between various use case elements of a system. Interaction diagrams are used to show an interaction between two entities and how data flows within them.

Following are the various interaction diagrams in UML:

- Timing diagram
- Sequence diagram
- Collaboration diagram


Summary
A model is said to be an abstraction of a system that hides the implementation details.
It provides blueprint and structure of a system.
It helps us to define the structural and behavioral aspects of a system.
Things, relationships and diagrams are three building blocks of UML.
Thing is nothing but any real-world entity.
Relationships are used to describe the connection between one or more things.
Various UML diagrams are used to describe different aspects of a single system.

<sup>source: https://www.guru99.com/uml-diagrams.html</sup>