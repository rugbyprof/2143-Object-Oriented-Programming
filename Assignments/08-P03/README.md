## Program 3 - MSUniverse Dynamic Fighting
#### Due: 10-11-2021 (Monday @ 12:00 p.m.)

### Overview

You need to design a program with multiple classes that represents a set of characters to fight in the MSUniverse. This universe is not as one would normally envision. It is infinitely long, but only the width and height of the hallway in Bolin science hall. It has one possible entrance for those brave enough to take a stand against `unWrthyMajors` ... "the loading dock!". In fact, the area between the outer airlock and inner door is a kind of a "lounge" for our waiting character fighters. You know ... its got snacks and couches and stuff. It's also larger on the inside as it is on the outside, kind of like the Tardis in Dr. Who. The bottom line is it's worth defending.

Let me set the stage for you: You have 1 - N team members (characters) to help you defend the "lounge". Each character are  "based" on the same `base character` design. You will have a limited set of parameters that you can use to "tailor" each character beyond the base design, turning them into a specific character type. We will keep it old school with basic characters like `Archer`, `Warrior`, `Wizard`, and the notorious: `SiliNerd`. If possible we may incorporate gender and / or race: `Dwarf`, `Elf`, `Human`, and the powerful `Geek` race. 

I don't have all the parameters to make up each character class right now, but we will definitely use a basic `health` value that terminates a character when a minimum threshhold is reached. We will allow each character a choice of `weapons` or `spells` for `attacks`. These will be multiplied by `skill` (or similar) to determine `hitpoints` or damage. We should probably add some kind of `defense` mechanism as well, like a shield or spell to keep it simple. We need each character to have enough uniqueness to be effective against some, but not all opponents. And what does that mean anyway? NO! We aren't writing a game ... ok maybe we are.

### Crux Of the Project

Your program will run continuously swapping characters in and out of the hallway to face off with whatever `unWrthyMajor` is trying to get into the "lounge". This really means you will place your best character (based on the matchup with the opponents current character) at the front of our line (aka data structure). She will then take turns attacking and defending against the enemy character (aka the character at the front of the other data structure). What qualifies as winning the entire simulation is yet to be determined, however causing an opponent to go below their health threshhold (usually 0) by inflicting damage will ensure that character leaves the simulation (in a body bag KTF!).

### Getting Started

You will firstly create a class that randomly generates differing values at differing extremes, based on a set of input params, in order to "build" your characters.  Random in our case is really **pseudo** random. In fact it's even worse than pseudo random, it's a "controlled" `random`. You will be in full control of how values are generated for each character / race / trait. We will decide as a class what the limits are for each character and trait, and then write methods that ensure a fair and balanced character. We want to ensure that extreme minimums and extreme maximums will only occur occasionally, but also mix it up enough to make sure each character actually has strengths and weaknesses, and not just all middle of the road values. We will probably write the majority of this random value generator together in class.



You need to dynamically adjust who's fighting in the MsuNiverse (hallway) based on the current `unWrthyMajor` trying to enter the lounge!! KTF!!

WHAT!?! We're writing a game!?! Kind of. We will be writing a simulation, with zero graphics, that will choose characters from your team to fight a near endless number of `unWrthyMajors` attempting to get into our lounge from the MSUniverse (aka hallway). 

Reports say that most of these `unWrthyMajors` are coming from deep, uncharted space (where uncharted = free parking). **We will send them back!** (to where they .... park ... for ... free). Whatever, were gonna go all KTF on their butts! (Kill Them First)<sup>1</sup>. 

>Reality check ... https://www.superherodb.com/powers/ 462 superpowers ... millions of possibilities ... not gonna happen. We really do need to come up with simple battle rules to make this project successful. Probably not clear at this point what I mean, but hopefully it starts to make sense below. 

### Runtime Polymorphism Battle Strategy

We saw in our Wednesday training briefing that we can use a single pointer of type `base` character to take control of any `child` or `sub` character that is a descendant of `base`. To ensure each child character has all necessary skills, many of the methods in our base class will not only be `virtual`, but `abstract` as well! Remember, a virtual base method can be overridden during runtime by a sub class. Taking it one step further, we make one or more of our base methods `abstract` ensuring (forcing) each subclass to implement each abstract method for fear of `compilation death`. Let's take a look at a very simple character base class before we get into the specifics of "battle" (and I have time to think about what that really means).

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
}
```




Any unique methods defined in a sub class (based on character type) will be available to be summoned (depending on character type (and maybe race)).More importantly, there are methods in the base class that will be overridden in each child class

As long as we use virtual methods in the base character definition, we can invoke any `specialized` skills of each different sub class at will! And, you will need to! 

<sub>**[1]** If "kill" is offensive, please replace all the double ll's with double ss's!</sub>



