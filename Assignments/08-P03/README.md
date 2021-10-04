## Program 3 - BolNiverse Fight Club
#### Due: Multiple

### Overview

You need to design a program with multiple classes that represents a set of characters to fight in the BolNiverse. This arena is not as one would normally envision. It is ... well its just a hallway. But it connects known space to the deep unknown.  It has one possible entrance for those brave enough to take a stand against the `freeParkers` faction. The entrance on our side of the BolNiverse is secretly known as "the loading dock!". In fact, the area between the outer containment door and inner door is known as "TheLounge". Its a highly coveted hot spot worth defending against the `freeParkers`.  You know ... its got snacks and couches and stuff. It's also larger on the inside as it is on the outside, kind of like the Tardis in Dr. Who. The bottom line is it's worth defending! The freeParkers control the only other entrance to the BolNiverse, and constantly attack then inner door trying to get into "TheLounge".

Let me set the stage for you: You are the leader of the BolNiverse defense forces, and your budget sucks. You have to use strategy to fight the `freeParkers` (those cheep asses). You have `1 to N` team members (characters) to help you defend the "TheLounge". Each character is "based" on the same `base character` design. You will have a limited set of parameters that you can use to "tailor" each character beyond the base design, turning them into a specific character type. We will keep it old school with basic character types and races:

| Character Classes    | Races           |
| :------------------ | :--------------- |
| Archer,             | Dwarf            |
| Warrior,            | Elf              |
| Wizard,             | Human            |
| Nerdist<sup>2</sup> | Geek<sup>3</sup> |


I don't have all the parameters to make up each character class right now, but we will definitely use a basic `health` value that terminates a character when a minimum threshold is reached. Each character has specified  `weapon(s)` or `spell(s)` for offensive `attacks`. These will be multiplied by `skill` (or similar) to determine `hitpoints` or damage. We should probably add some kind of `defense` mechanism as well, like a shield or spell to keep it simple. We need each character to have enough uniqueness to be effective against some, but not all opponents. And what does that mean anyway? Wait! Are we writing a game? We aren't writing a game ... ok maybe we are?!? 

>Reality check. Go look here: https://www.superherodb.com/powers/ There are 462 superpowers, all with detailed definitions and ultimately millions (or billions) of possibilities in the creation of a character. We aren't going the `super power` route, but it makes the point.  If we get too ambitious, we will fail miserably. We need to come up with **extremely simple battle rules** to make this project have any hope of success. 

### Crux Of the Project

Your program will run continuously swapping characters in and out of the hallway to face off with whatever `freeParker` is trying to get into the "TheLounge". This really means you will place your best character (based on the matchup with the opponents current character) at the front of our line (aka queue). She will then take turns attacking and defending against the enemy character (aka the character in front of the other queue). Causing an opponent to go below their health threshold (usually 0) by inflicting damage will ensure that character leaves the simulation (in a body bag KTF!<sup>1</sup>). First side to eliminate the other faction, wins.

### Getting Started

You will firstly create a class that randomly generates differing values at differing extremes, based on a set of input params, in order to "build" your characters.  Random in our case is really **pseudo** random. In fact it's even worse than pseudo random, it's a "controlled" `random`. You will be in full control of how values are generated for each character / race / trait. We will decide as a class what the limits are for each character and trait, and then write methods that ensure a fair and balanced character. We want to ensure that extreme minimums and extreme maximums will only occur occasionally, but also mix it up enough to make sure each character actually has strengths and weaknesses, and not just all middle of the road values. We will probably write the majority of this random value generator together in class.

```cpp

class Weapon{
    string name;
    double skillLevel;
    double powerLevel;
    double attack();        // generates attack value based on 
};

struct Character{
    string classification;       // type is a reserved word
    string race;
    vector<weapon> weapons;
    double health;

}


class CharacterGen{
    string randRace();                      // randomly returns a race
    string randClass();                      // randomly returns a classification
    string weapon(string classification);   // randomly assign a weapon based on character type
                                            // it could be a spell if the character is a wizard
};
```

### Runtime Polymorphism Battle Strategy

We saw in our Wednesday training briefing that we can use a single pointer of type `base character` to take control of any `child` or `sub` character that is a descendant of `base` (inherits from). To ensure each child character has all necessary skills, many of the methods in our base class will not only be `virtual`, but `abstract` as well! Remember, a virtual base method can be overridden during runtime by a sub class. Taking it one step further, we make one or more of our base methods `abstract` ensuring (forcing) each subclass to implement each abstract method for fear of `compilation death`. Let's take a look at a very simple character base class before we get into the specifics of "battle" (and I have time to think about what that really means).

```cpp
class BaseCharacter{
    string name;
    string race;        // Does a character inherit from race? Or are they composed of a race?
    string gender;      // Same for gender. Does race or gender offer any special properties that
                        //      could be inherited by a character?
    double health;      
    double stamina;
    double skill;
    //string weapon;    // Not sure if this belongs here or not. Do ALL characters carry a weapon?
    //double mana;      // This is a specialty for wizards! So, it doesn't belong here.

public:
    // constructors

    // pure virtual methods
    virtual double attack() = 0;
    virtual double defend() = 0;
}
```

Any unique methods defined in a sub class (based on character type) will be available to be summoned (depending on character type (and maybe race)). More importantly, there are methods in the base class that must be overridden in each child class! As long as we use pure virtual methods in the base character definition, we can ensure similar behavior in all of our `specialized` characters using their unique skills to assist the generic `attack` or `defend` methods which all characters must possess.



<sub>**[1]** If "kill" is offensive, please replace the double ll's with double ss's!</sub>
<sub>**[2]** Nerdist is a new powerful type that has every possible trait to some extent.</sub>
<sub>**[3]** Geek is also a powerful race that inherently boosts all attributes by some factor</sub>

