# D&D Game - Don't Get Excited ... This is Hard!

## Basic Characters

For each basic character, you should represent the following attributes:

| Attribute    | Description                                               | Min | Max |
| :----------- | :-------------------------------------------------------- | :-: | :-: |
| Strength     | measure of physical power and melee combat effectiveness. |  3  | 18  |
| Dexterity    | measure of agility and ranged combat effectiveness.       |  3  | 18  |
| Constitution | measure of health and resilience.                         |  3  | 18  |
| Intelligence | measure of knowledge and spell-casting ability.           |  3  | 18  |
| Wisdom       | measure of intuition and perception.                      |  3  | 18  |
| Charisma     | measure of personality and leadership.                    |  3  | 18  |

A basic character should also have 1 or more attributes that can be either be turned on or off, or set to some value which will either increase basic powers like a boost, or reduce powers like if they were blinded. Not sure what to call them. So we can discuss in class.

### Generating Characters

The standard method for generating attribute values for a new character is to roll `four six-sided dice` (`4d6`) and sum the three highest rolls, discarding the lowest roll. This is done six times, once for each attribute (`Strength`, `Dexterity`, `Constitution`, `Intelligence`, `Wisdom`, and `Charisma`), resulting in a set of six values that are used to determine the character's abilities.

The average value for a single `4d6` roll is `12.244`, and the average value for the sum of the three highest rolls is `12.244 * 3 = 36.732`. This means that the average starting value for a randomly generated attribute using the standard method is around `10-11` (which is the sum of the three highest rolls divided by 3).

However, it's important to note that these are just averages and the actual values can vary widely based on luck and chance. It's also common for Dungeon Masters to allow for alternative methods of generating attribute values, such as point-buy systems or fixed values, to provide more control and balance over character creation.

### Character Classes

Here are the characters that we will generate. They will extend a basic character class and are pretty basic:

```json
(character_emojis = {
  "Barbarian": "🪓",
  "Bard": "🎶",
  "Cleric": "✝️",
  "Druid": "🐾",
  "Fighter": "⚔️",
  "Monk": "👊",
  "Paladin": "🛡️",
  "Ranger": "🏹",
  "Rogue": "🗡️",
  "Sorcerer": "🔮",
  "Warlock": "💀",
  "Wizard": "🧙"
})
```

1. **Barbarian**: A primal warrior who relies on physical strength and raw fury to overpower their foes.
2. **Bard**: A performer with magical abilities who uses music and storytelling to inspire allies and hinder enemies.
3. **Cleric**: A divine spellcaster who channels the power of their deity to heal allies, smite enemies, and perform miracles.
4. **Druid**: A nature-based spellcaster who draws on the power of the natural world to cast spells, transform into animals, and commune with plants and animals.
5. **Fighter**: A skilled combatant who is highly trained in weapons and armor, and can use a variety of tactics to excel in combat.
6. **Monk**: A disciplined warrior who uses martial arts and a monk's traditional weapons to fight with both physical and mental prowess.
7. **Paladin**: A holy knight who combines martial prowess with divine magic to serve a cause or deity.
8. **Ranger**: A skilled outdoorsman who is highly attuned to nature and uses their expertise to track, hunt, and survive in the wilderness.
9. **Rogue**: A sneaky thief who excels at stealth, deception, and picking locks, and can use their cunning to gain an advantage in combat.
10. **Sorcerer**: A spellcaster who has innate magical abilities and can cast spells without relying on external sources of power.
11. **Warlock**: A spellcaster who has made a pact with a powerful being, granting them magical abilities and otherworldly powers.
12. **Wizard**: A scholarly spellcaster who learns magic through study and can cast spells from a wide range of schools and disciplines.

### Combined Character Classes

1. **Spellblade**: A mix of `fighter` and `sorcerer` that combines melee combat abilities with spell-casting.
2. **Shadowdancer**: A mix of `rogue` and `bard` that blends stealth and deception with performance and magic.
3. **Shapeshifter**: A mix of `druid` and `monk` that focuses on the ability to transform into animals and uses martial arts in combat.
4. **Holy Avenger**: A mix of `paladin` and `ranger` that combines divine magic and martial prowess with a focus on hunting evil creatures.
5. **Eldritch Assassin**: A mix of `warlock` and `rogue` that blends dark magic and stealthy attacks with a sinister edge.
6. **Battle Mage**: A mix of `wizard` and `fighter` that combines magical knowledge and combat skill with a focus on manipulating the battlefield to gain advantage.
7. **Fury Fist**: `Fighter` who additionally has the combined the brutal strength of the `barbarian` with the disciplined combat techniques of the `monk`.

## Special Attacks

**Spellblade**: The `Spellblade` is a fighter who has learned to infuse their weapons with arcane energy, allowing them to deal extra damage with each strike. They can also cast spells that enhance their weapons or protect themselves from harm. One possible unique attack for the `Spellblade` is `Arcane Strike`, which allows them to add `2d6` force damage to their weapon attacks for a limited time. Another possible unique attack is `Chaos Bolt`, which is a spell that deals `4d8` damage of a `random type (acid, cold, fire, lightning, poison, or thunder)` to a single target.

**Shadowdancer**: The `Shadowdancer` is a rogue who has learned to harness the power of shadow to move stealthily and strike their enemies from unexpected angles. They can also cast spells that manipulate light and darkness to obscure their movements or hinder their foes. One possible unique attack for the `Shadowdancer` is `Shadow Strike`, which allows them to deal extra damage with their sneak attacks while also teleporting behind their target. Another possible unique attack is `Blinding Shadow`, which is a spell that `blinds all creatures in a 20-foot radius for 1 minute`.

**Shapeshifter**: The Shapeshifter is a druid who has learned to combine their druidic magic with their martial arts training, allowing them to shift into animal forms and strike their enemies with deadly force. They can also cast spells that enhance their physical abilities or control the elements. One possible unique attack for the Shapeshifter is `Savage Bite`, which allows them to `deal extra damage with their natural attacks` while in animal form. Another possible unique attack is `Whirlwind Strike`, which is a spell that allows them to make a `flurry of melee attacks against all enemies within 10 feet`.

**Holy Avenger**: The Holy Avenger is a paladin who has teamed up with a ranger to become a powerful force for good. They use their divine and martial powers to protect the innocent and vanquish evil wherever it may be found. They can also cast spells that heal their allies or deal extra damage to undead or fiends. One possible unique attack for the Holy Avenger is `Divine Smite`, which allows them to `deal extra radiant damage with their weapon attacks`. Another possible unique attack is `Hunter's Mark`, which is a spell that allows them to `deal extra damage to a single target for a limited time`.

**Eldritch Assassin**: The Eldritch Assassin is a rogue who has made a pact with a warlock to gain access to powerful eldritch magic. They can use their spells to augment their stealth and mobility, as well as to inflict curses on their enemies. One possible unique attack for the Eldritch Assassin is `Shadow Blade`, which allows them to create a `blade of solidified darkness that deals extra damage` and can be thrown at a target. Another possible unique attack is `Hex`, which is a spell `that inflicts a curse on a target`, reducing their abilities and making them vulnerable to extra damage.

**Battle Mage**: The Battle Mage is a wizard who has trained in martial combat to become a formidable warrior-mage. They can use their spells to enhance their physical abilities or deal devastating damage to their foes. One possible unique attack for the Battle Mage is `Elemental Strike`, which allows them to imbue their weapon with elemental energy to `deal extra damage of that type`. Another possible unique attack is `Meteor Swarm`, which is a spell that rains down fiery meteors on a 40-foot radius, `dealing massive damage to all creatures in the area`.

**Fury Fist**: The Fury Fist is a barbarian and monk combination that focuses on unarmed combat and tapping into their rage to deal devastating damage. They can also use their skill to enhance their attacks and movements. One possible unique attack for `Fury Fist` is `Fury of the Elements`, which allows them to channel the power of the elements into their fists, `dealing extra damage of a random type (acid, cold, fire, lightning, or thunder)` with each strike. Another possible unique attack is `Raging Thunderclap`, which is a spell that creates a deafening thunderclap around the Fury Fist, `dealing thunder damage and stunning all creatures within 10 feet`.

Here are the associated damage types and die rolls for each of the unique attacks:

**Arcane Strike**: Force damage, `2d6` extra damage
**Chaos Bolt**: Random type (acid, cold, fire, lightning, poison, or thunder) damage, `4d8` damage
**Shadow Strike**: Piercing or slashing damage (depending on weapon used) plus sneak attack damage, teleportation behind target
**Blinding Shadow**: No damage, blinds all creatures in a 20-foot radius for 1 minute
**Savage Bite**: Bludgeoning, piercing, or slashing damage (depending on the natural attack used), extra damage based on character level and proficiency bonus
**Whirlwind Strike**: Bludgeoning, piercing, or slashing damage (depending on the weapon used), multiple attacks against all enemies within 10 feet
**Divine Smite**: Radiant damage, extra damage based on spell slot level used
**Hunter's Mark**: Extra damage (usually piercing or slashing), lasts for a limited time
**Shadow Blade**: Piercing or slashing damage (depending on the weapon created), can be thrown at a target for extra damage
**Hex**: Necrotic damage, inflicts a curse on the target that reduces their abilities and makes them vulnerable to extra damage
**Elemental Strike**: Elemental damage (acid, cold, fire, lightning, or thunder), extra damage based on spell slot level used
**Meteor Swarm**: Fire damage, `20d6` damage in a 40-foot radius
**Fury of the Elements**: Random type (acid, cold, fire, lightning, or thunder) damage, extra damage based on character level and proficiency bonus
**Raging Thunderclap**: Thunder damage, stuns all creatures within 10 feet for 1 round.

## Attacking Monsters

In Dungeons and Dragons, characters damage monsters by rolling dice to determine the amount of damage dealt by their attacks. The specific die used depends on the character's weapon or attack, as well as any bonuses or modifiers that apply.

There should probably be an attack class which represents a specific attack, and its associated damages.

```cpp
class Attack{
protected:
    string category;
public:
};
```

## Walkthrough Character Generation

### Generic Steps

Each of these steps are applied to every character:

1. Roll 4 six-sided dice for each of the six attributes
   - Strength
   - Dexterity
   - Constitution
   - Intelligence
   - Wisdom
   - Charisma
2. Discard the lowest roll for each attribute.
3. Add up the remaining three dice rolls to get the attribute score.
4. Repeat steps 1-3 until all six attributes have been generated.



## Random Character Generation

```cpp
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random number between min and max
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Array of character names
    string characters[] = {"Warrior", "Wizard", "Rogue", "Cleric", "Paladin", "Druid", "Dwarf", "Elf"};

    // Loop through each character
    for (int i = 0; i < 8; i++) {
        string character = characters[i];

        // Generate random stats for the character
        int strength = random(8, 18);
        int dexterity = random(8, 18);
        int constitution = random(8, 18);
        int intelligence = random(8, 18);
        int wisdom = random(8, 18);
        int charisma = random(8, 18);

        // Output the stats for the character
        cout << character << ":" << endl;
        cout << "Strength: " << strength << endl;
        cout << "Dexterity: " << dexterity << endl;
        cout << "Constitution: " << constitution << endl;
        cout << "Intelligence: " << intelligence << endl;
        cout << "Wisdom: " << wisdom << endl;
        cout << "Charisma: " << charisma << endl;
        cout << endl;
    }

    return 0;
}
```

## Random Die Rolling

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Die {
public:
    Die(int num_sides) {
        sides = num_sides;
        srand(time(NULL));
    }

    int roll() {
        return rand() % sides + 1;
    }

private:
    int sides;
};

int main() {
    // Create a Die object for each die type
    Die d20(20);
    Die d12(12);
    Die d10(10);
    Die d8(8);
    Die d6(6);
    Die d4(4);

    // Roll each die type 5 times and output the results
    cout << "D20 rolls:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << d20.roll() << endl;
    }
    cout << endl;

    cout << "D12 rolls:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << d12.roll() << endl;
    }
    cout << endl;

    cout << "D10 rolls:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << d10.roll() << endl;
    }
    cout << endl;

    cout << "D8 rolls:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << d8.roll() << endl;
    }
    cout << endl;

    cout << "D6 rolls:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << d6.roll() << endl;
    }
    cout << endl;

    cout << "D4 rolls:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << d4.roll() << endl;
    }
    cout << endl;

    return 0;
}
```

## Multiple Inheritance

Simple Example of multiple inheritance for a warrior class. Thanks Ghat GPT, not sure what plagiarism is involved, but I still find errors in your code!

In this example, we have a base class Character that defines the basic properties and methods of a character, such as `attack()`, `defend()`, and `getHealth()`. We also have a `Warrior` class that inherits from `Character` and adds a `charge()` method, as well as a `Weapons` class that defines the basic properties and methods of a weapon, such as `attack()`. Finally, we have a `WarriorWithWeapon` class that inherits from both `Warrior` and `Weapons`, allowing it to use both the `charge()` method from Warrior and the `attack()` method from `Weapons`. It also adds a `specialAttack()` method that is unique to `WarriorWithWeapon`.

In the `main()` function, we create a `WarriorWithWeapon` object warrior with a name of "Conan", a health of 100, and a weapon of "Sword". We then call the `charge()`, `attack()`, `specialAttack()`, and `defend()` methods of warrior to demonstrate its abilities. We also update its health and output the new health value to show the use of the `setHealth()` and `getHealth()` methods from Character.

```cpp
#include <iostream>
using namespace std;

class Character {
public:
    Character(string name, int health) {
        this->name = name;
        this->health = health;
    }

    void attack() {
        cout << name << " attacks!" << endl;
    }

    void defend() {
        cout << name << " defends!" << endl;
    }

    void setHealth(int health) {
        this->health = health;
    }

    int getHealth() {
        return health;
    }

protected:
    string name;
    int health;
};

class Warrior : public Character {
public:
    Warrior(string name, int health, string weapon) : Character(name, health) {
        this->weapon = weapon;
    }

    void charge() {
        cout << name << " charges into battle with " << weapon << "!" << endl;
    }

private:
    string weapon;
};

class Weapons {
public:
    Weapons(string weapon) {
        this->weapon = weapon;
    }

    void attack() {
        cout << "Attacking with " << weapon << "!" << endl;
    }

private:
    string weapon;
};

class WarriorWithWeapon : public Warrior, public Weapons {
public:
    WarriorWithWeapon(string name, int health, string weapon) : Warrior(name, health, weapon), Weapons(weapon) {}

    void specialAttack() {
        cout << name << " uses a special attack with " << weapon << "!" << endl;
    }
};

int main() {
    WarriorWithWeapon warrior("Conan", 100, "Sword");

    warrior.charge();
    warrior.attack();
    warrior.specialAttack();
    warrior.defend();

    warrior.setHealth(warrior.getHealth() - 10);
    cout << warrior.getHealth() << " health remaining." << endl;

    return 0;
}
```
