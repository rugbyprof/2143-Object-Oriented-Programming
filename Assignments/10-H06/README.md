## Overloading  - Pokemon Class
#### Due:  03-13-2020 (Friday @ 12:30 p.m.) 

## Overview

So, I wanted to do something that wasn't "fractions" or "shapes" (points, lines, polygons) or anything that is super typical of an OOP class. So I thought we would design a class for a PokeMon. Ok. Have you stopped laughing yet? Check out all the data I have [here](../../Resources/99-Data/README.md) 

We won't use it all (not even close). And I'm going to make up my own rules, so if your a Pokemon tyrant, your gonna have to let some stuff go. In fact, this assignment is all about creating the classes for our pokemon. You won't even have to load data into them (until later). 

Lets start off with this information:

A basic pokemon has these values (these will be your base class data members).
```txt
    "HP": 78            (hit points)
    "Attack": 84,
    "Defense": 78,
    "Sp. Attack": 109,  (special attack)
    "Sp. Defense": 85,  (special defense)
    "Speed": 100
```

A specific pokemon has an id (pokeindex), a name and a type or types. The kind
of pokemon you
```txt
    "id":               integer
    "name":             string like "Charizard"
    "type":             array["Fire","Flying"]
    "weight":           some random int or float value
    "height":           some random int or float value
    "gender":           male or female
    "evoLevel":         evolutionLevel;
    "finalEvolution":   boolean;
```

The pokemon types are:
```py
['bug', 'dragon', 'electric', 'fighting', 'fire', 'flying', 'ghost', 'grass', 'ground', 'ice', 'normal', 'poison', 'psychic', 'rock', 'water']
```
But thats way too many! So I'm picking 5 at random (seriously see [code](../../Resources/99-Data/filter_data.py)). If you run the script, it may be different since its random. But here are the 5 types:

```py
['fighting', 'dragon', 'poison', 'ground', 'normal']
```

But I want you to design and then overload a set of classes to do the following:

- Represent a base Pokemon (maybe call it `PokemonBase`)
- Create on class for each type (['fighting', 'dragon', 'poison', 'ground', 'normal']) (maybe call them `FightingClass`,`DragonClass`,etc.)
- We also need a Pokemon Class, guess what you can call it? 
- Remember some pokemon are more than one type, but in c++ can inherit from more than one class, so thats ok.


