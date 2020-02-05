## Json Overview

### General 

- JSON is a lightweight data-interchange format.
- JSON stands for `JavaScript Object Notation`.
- Started out in JavaScript.
- It is: 
  - text-based and easily readable.
  - supported by **many** programming environments!
  - language and platform independent.
  - a lightweight alternative to XML.
- It was invented by Douglas Crockford.
- JSON is mainly used for storing and exchanging data. 
- The file extension for JSON is `.json`. 
- It's internet Media type is `application/json.`.

### Some Simple Rules

- `{}` curly braces imply **object**.
- An **object** is a collection of `key value pairs`.
- `[]` square brackets imply **array**.
- You can mix and match all of these constructs to create complex data structures.


### Examples:

---- 

- Here is a single object (curly braces with key:value pairs inside).
- This object contains a name,age,and secretIdentity of a super hero.
- `super` is the variable storing the object:
  
```json
    super = {
      "name": "Molecule Man",
      "age": 29,
      "secretIdentity": "Dan Jukes",
    }
```
----

- The traditional method to access a value is by using its key and an array syntax:
  
```cpp
    cout<<super["name"]<<", "<<super["age"]<<", "<<super["secretIdentity"]<<endl;
    // would print: Molecule Man, 29, Dan Jukes
```

----

- Lets add a list of `powers` possessed by this super hero. 
- The `powers` are accessed by the "key": `powers` and listed in an array:

```json
    super = {
      "name": "Molecule Man",
      "age": 29,
      "secretIdentity": "Dan Jukes",
      "powers":[
            "Radiation resistance",
            "Turning tiny",
            "Radiation blast"
      ]
    }
```

----

- To access each power, we could do the following: 
  
```cpp
    cout<<super["powers"][0]<<endl
    cout<<super["powers"][1]<<endl
    cout<<super["powers"][2]<<endl;
```

- Looping over the entire array could be done similar to:

```cpp
    for(int i=0;i<super["powers"].size();i++)
        cout<<super["powers"][0]<<endl;
```

---- 

- What about many super hero's and their powers?
- The entire collection is 1 object.
- Each super hero is in an array accessed by "members".
- Each member has its key value pair data + an array of powers.

```json
{
  "squadName": "Super hero squad",
  "homeTown": "Metro City",
  "formed": 2016,
  "secretBase": "Super tower",
  "active": true,
  "members": [
    {
      "name": "Molecule Man",
      "age": 29,
      "secretIdentity": "Dan Jukes",
      "powers": [
        "Radiation resistance",
        "Turning tiny",
        "Radiation blast"
      ]
    },
    {
      "name": "Madame Uppercut",
      "age": 39,
      "secretIdentity": "Jane Wilson",
      "powers": [
        "Million tonne punch",
        "Damage resistance",
        "Superhuman reflexes"
      ]
    },
    {
      "name": "Eternal Flame",
      "age": 1000000,
      "secretIdentity": "Unknown",
      "powers": [
        "Immortality",
        "Heat Immunity",
        "Inferno",
        "Teleportation",
        "Interdimensional travel"
      ]
    }
  ]
}
```

----

- To print out some of the above object:

```cpp
    for(int i=0;i<super["members"].size();i++){
        cout<<super["members"]["name"]<<endl;
        for(int j=0;j<super["members"][i].size();j++){
            cout<<super["members"][i]["powers"][j]<<endl;
        }   
    }

```