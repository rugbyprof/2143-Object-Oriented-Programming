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

1. **Spellblade**: A mix of fighter and sorcerer that combines melee combat abilities with spell-casting.
2. **Shadowdancer**: A mix of rogue and bard that blends stealth and deception with performance and magic.
3. **Shapeshifter**: A mix of druid and monk that focuses on the ability to transform into animals and uses martial arts in combat.
4. **Holy Avenger**: A mix of paladin and ranger that combines divine magic and martial prowess with a focus on hunting evil creatures.
5. **Eldritch Assassin**: A mix of warlock and rogue that blends dark magic and stealthy attacks with a sinister edge.
6. **Battle Mage**: A mix of wizard and fighter that combines magical knowledge and combat skill with a focus on manipulating the battlefield to gain advantage.
7. **Fury Fist**: Warriors who have combined the brutal strength of the barbarian with the disciplined combat techniques of the monk.

## Special Attacks

**Spellblade**: The `Spellblade` is a fighter who has learned to infuse their weapons with arcane energy, allowing them to deal extra damage with each strike. They can also cast spells that enhance their weapons or protect themselves from harm. One possible unique attack for the `Spellblade` is `Arcane Strike`, which allows them to add `2d6` force damage to their weapon attacks for a limited time. Another possible unique attack is `Chaos Bolt`, which is a spell that deals `4d8` damage of a `random type (acid, cold, fire, lightning, poison, or thunder)` to a single target.

**Shadowdancer**: The `Shadowdancer` is a rogue who has learned to harness the power of shadow to move stealthily and strike their enemies from unexpected angles. They can also cast spells that manipulate light and darkness to obscure their movements or hinder their foes. One possible unique attack for the `Shadowdancer` is `Shadow Strike`, which allows them to deal extra damage with their sneak attacks while also teleporting behind their target. Another possible unique attack is `Blinding Shadow`, which is a spell that `blinds all creatures in a 20-foot radius for 1 minute`.

**Shapeshifter**: The Shapeshifter is a druid who has learned to combine their druidic magic with their martial arts training, allowing them to shift into animal forms and strike their enemies with deadly force. They can also cast spells that enhance their physical abilities or control the elements. One possible unique attack for the Shapeshifter is `Savage Bite`, which allows them to `deal extra damage with their natural attacks` while in animal form. Another possible unique attack is `Whirlwind Strike`, which is a spell that allows them to make a `flurry of melee attacks against all enemies within 10 feet`.

**Holy Avenger**: The Holy Avenger is a paladin who has teamed up with a ranger to become a powerful force for good. They use their divine and martial powers to protect the innocent and vanquish evil wherever it may be found. They can also cast spells that heal their allies or deal extra damage to undead or fiends. One possible unique attack for the Holy Avenger is `Divine Smite`, which allows them to `deal extra radiant damage with their weapon attacks`. Another possible unique attack is `Hunter's Mark`, which is a spell that allows them to `deal extra damage to a single target for a limited time`.

**Eldritch Assassin**: The Eldritch Assassin is a rogue who has made a pact with a warlock to gain access to powerful eldritch magic. They can use their spells to augment their stealth and mobility, as well as to inflict curses on their enemies. One possible unique attack for the Eldritch Assassin is `Shadow Blade`, which allows them to create a `blade of solidified darkness that deals extra damage` and can be thrown at a target. Another possible unique attack is `Hex`, which is a spell `that inflicts a curse on a target`, reducing their abilities and making them vulnerable to extra damage.

**Battle Mage**: The Battle Mage is a wizard who has trained in martial combat to become a formidable warrior-mage. They can use their spells to enhance their physical abilities or deal devastating damage to their foes. One possible unique attack for the Battle Mage is `Elemental Strike`, which allows them to imbue their weapon with elemental energy to `deal extra damage of that type`. Another possible unique attack is `Meteor Swarm`, which is a spell that rains down fiery meteors on a 40-foot radius, `dealing massive damage to all creatures in the area`.

**Fury Fist**: The Fury Fist is a barbarian and monk combination that focuses on unarmed combat and tapping into their rage to deal devastating damage. They can also use their ki to enhance their attacks and movements. One possible unique attack for Fury Fist is `Fury of the Elements`, which allows them to channel the power of the elements into their fists, `dealing extra damage of a random type (acid, cold, fire, lightning, or thunder)` with each strike. Another possible unique attack is `Raging Thunderclap`, which is a spell that creates a deafening thunderclap around the Fury Fist, `dealing thunder damage and stunning all creatures within 10 feet`.

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

### Attacks (weapons really)

Fighters in Dungeons and Dragons are typically proficient in a variety of weapons, allowing them to choose the best weapon for a particular situation. Here are some typical weapons for a fighter, along with their associated strengths:

- **Longsword**: A versatile weapon that deals slashing or piercing damage. Strengths include versatility, balanced damage output, and the ability to use with a shield. Deals `1d8` slashing or piercing damage.
- **Greatsword**: A two-handed weapon that deals heavy slashing damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `2d6` slashing damage.
- **Warhammer**: A blunt weapon that deals bludgeoning damage. Strengths include the ability to bypass certain types of armor and shields. Deals `1d8` bludgeoning damage.
- **Greataxe**: A two-handed weapon that deals heavy slashing damage and has a chance to critically hit. Strengths include high damage output and the chance to deal even more damage on a critical hit. Deals `1d12` slashing damage.
- **Spear**: A versatile weapon that deals piercing damage and can be used for melee or thrown attacks. Strengths include reach and versatility. Deals `1d6` piercing damage.
- **Crossbow**: A ranged weapon that can be used for ranged attacks. Strengths include range and the ability to deal consistent damage from a distance. Deals `1d8` piercing damage.
- **Bow**: A ranged weapon that can be used for ranged attacks. Strengths include range and the ability to deal consistent damage from a distance. Deals `1d8` piercing damage.
- **Halberd**: A two-handed weapon that combines the functions of an axe and a spear. Deals slashing or piercing damage. Strengths include reach and the ability to deal damage from a distance. Deals `1d10` slashing or piercing damage.

### Magic (if any)

In Dungeons and Dragons, warriors are typically not proficient in magic, and their attacks tend to rely on physical strength and melee weapons. However, some subclasses or special circumstances may allow for magical attacks. Here are a few examples:

- **Eldritch Knight subclass**: A warrior subclass that can cast spells and use magical attacks, such as the cantrip "Booming Blade" which deals 1d8 thunder damage plus additional damage if the target moves.

- **Magic weapons**: Warriors can wield magic weapons that may have enchanted properties, such as dealing extra damage to certain types of enemies or having elemental damage (e.g. a sword that deals extra fire damage).

- **Potions**: Warriors can consume potions that grant magical effects, such as increased strength or temporary resistance to damage.

The strength and damage of these magical attacks can vary based on the specific circumstances and the level of the character, but generally, they would follow the same damage and die roll rules as other spells and magical effects in the game.

## Wizard

### Attacks (magical)

Here are some typical attacks for a wizard along with their associated strengths, damage, and die to roll for damage:

- **Fireball**: A spell that explodes in a fiery burst, dealing fire damage to all creatures within its area of effect. Strengths include high damage output and the ability to hit multiple enemies at once. Deals `8d6` fire damage (DEX save for half damage).
- **Magic Missile:** A spell that launches magical missiles that strike their targets unerringly. Strengths include guaranteed hit and the ability to bypass certain defenses. Deals `1d4+1`force damage per missile (each missile hits a separate target).
- **Lightning Bolt**: A spell that releases a bolt of lightning, dealing lightning damage to all creatures in its path. Strengths include high damage output and the ability to hit multiple enemies at once. Deals `8d6` lightning damage (DEX save for half damage).
- **Cone of Cold**: A spell that releases a cone of freezing air, dealing cold damage to all creatures within its area of effect. Strengths include high damage output and the ability to hit multiple enemies at once. Deals `8d8` cold damage (CON save for half damage).
- **Acid Splash**: A spell that throws a glob of acid, dealing acid damage to one or two creatures within range. Strengths include the ability to hit multiple enemies at once and the ability to bypass certain defenses. Deals `1d6` acid damage.
- **Ray of Frost**: A spell that releases a freezing ray, dealing cold damage to one creature within range. Strengths include the ability to slow down the target's movement speed. Deals `1d8` cold damage.
- **Magic Weapon**: A spell that enchants a weapon, giving it a bonus to attack and damage rolls. Strengths include the ability to enhance a fighter's damage output. Adds `+1` to attack and damage rolls.
- **Shield**: A spell that creates a magical shield around the caster, increasing their armor class and making them harder to hit. Strengths include increased defense and survivability. Adds `+5` to the caster's armor class.

### Weapons (limited amount)

Wizards generally rely on spells for combat, so they typically do not use weapons as their primary form of attack. However, there are some weapons that a wizard may use for self-defense or as a backup option. Here are some examples:

- **Dagger**: A small, versatile weapon that can be used for melee or ranged attacks. Strengths include versatility and ease of concealment. Deals `1d4` piercing damage.
- **Staff**: A long, two-handed weapon that can be used for melee attacks. Strengths include reach and the ability to channel magic through the staff. Deals `1d6` bludgeoning damage.
- **Quarterstaff**: A shorter, two-handed weapon that can be used for melee attacks. Strengths include reach and the ability to channel magic through the staff. Deals `1d6` bludgeoning damage.
- **Sling**: A ranged weapon that fires small rocks or other projectiles. Strengths include the ability to make ranged attacks and the ability to use with ammunition found in the environment. Deals `1d4` bludgeoning damage.
- **Light Crossbow**: A ranged weapon that fires bolts. Strengths include the ability to make ranged attacks and the ability to deal higher damage than a sling. Deals `1d8` piercing damage.
- **Heavy Crossbow:** A larger and more powerful version of the light crossbow. Strengths include the ability to make ranged attacks and the ability to deal even higher damage than the light crossbow. Deals `1d10` piercing damage.

## Rogue

Here are some typical attacks for a rogue in Dungeons and Dragons along with their associated strengths, damage, and die to roll for damage:

### Attacks

- **Sneak Attack**: A melee or ranged attack that deals extra damage if the target is caught off-guard or unaware. Strengths include high damage output and the ability to target vulnerable areas. Deals `1d6`, `2d6`, `3d6`, `4d6`, or `5d6` extra damage (depending on the rogue's level).
- **Throwing Dagger**: A ranged attack with a thrown dagger, dealing piercing damage to one target within range. Strengths include the ability to make ranged attacks and the ability to use stealth to gain an advantage. Deals `1d4` piercing damage.
- **Shortsword**: A melee attack with a shortsword, dealing piercing damage to one target within range. Strengths include the ability to make quick, precise attacks and the ability to use a shield for extra defense. Deals `1d6` piercing damage.
- **Sneak Attack with Poison**: A melee or ranged attack with a poisoned weapon, dealing extra damage and causing the target to become poisoned. Strengths include the ability to deal extra damage and disable the target. Deals `1d6`, `2d6`, `3d6`, `4d6`, or `5d6` extra damage (depending on the rogue's level) and causes the target to become poisoned.
- **Sneak Attack with Crossbow**: A ranged attack with a crossbow, dealing extra damage if the target is caught off-guard or unaware. Strengths include the ability to make ranged attacks and the ability to deal extra damage. Deals `1d6`, `2d6`, `3d6`, `4d6`, or `5d6` extra damage (depending on the rogue's level).
- **Thieves' Tools**: A set of tools used to pick locks, disable traps, and perform other stealthy actions. Strengths include the ability to bypass obstacles and gain an advantage in combat.
- **Dash and Disengage**: A maneuver that allows the rogue to move quickly and avoid opportunity attacks from enemies. Strengths include increased mobility and survivability in combat.

### Weapons

- **Shortsword**: A versatile weapon that can be used for melee attacks. Strengths include versatility and ease of concealment. Deals `1d6` piercing damage.
- **Dagger**: A small, versatile weapon that can be used for melee or ranged attacks. Strengths include versatility and ease of concealment. Deals `1d4` piercing damage.
- **Rapier**: A slender, thrusting sword that deals piercing damage. Strengths include high accuracy and the ability to bypass some armor. Deals `1d8` piercing damage.
  Hand Crossbow: A ranged weapon that can be concealed and fired quickly. Strengths include the ability to make ranged attacks and the ability to use with a shield. Deals `1d6` piercing damage.
- **Shortbow**: A ranged weapon that can be used for quick, precise attacks. Strengths include the ability to make ranged attacks and the ability to use with ammunition found in the environment. Deals `1d6` piercing damage.
- **Longbow**: A larger and more powerful version of the shortbow. Strengths include the ability to make ranged attacks and the ability to deal even higher damage than the shortbow. Deals `1d8` piercing damage.

## Cleric

### Attacks

Here are some typical attacks for a cleric in Dungeons and Dragons along with their associated strengths, damage, and die to roll for damage:

- **Sacred Flame**: A spell that releases radiant flames, dealing radiant damage to one target within range. Strengths include the ability to target undead and fiendish creatures, and bypass some resistances. Deals `1d8` radiant damage (DEX save for half damage).
- **Spiritual Weapon**: A spell that creates a magical weapon that attacks one target within range. Strengths include the ability to make ranged attacks and the ability to deal consistent damage. Deals `1d8`+`spellcasting` ability modifier force damage.
- **Guiding Bolt**: A spell that releases a beam of light, dealing radiant damage to one target within range. Strengths include the ability to deal high damage and the ability to give allies advantage on their attacks. Deals `4d6` radiant damage (spell attack roll to hit).
- **Turn Undead**: A spell that forces undead creatures to flee or be destroyed. Strengths include the ability to disable undead creatures and the ability to protect allies. Effect varies by creature type and CR.
- **Healing Word**: A spell that heals one creature within range. Strengths include the ability to heal allies quickly and the ability to be used as a bonus action. Heals `1d4`+`spellCasting` ability modifier hit points.
- **Inflict Wounds**: A spell that causes necrotic damage to one target within range. Strengths include the ability to deal high damage and the ability to bypass some resistances. Deals `3d10` necrotic damage (spell attack roll to hit).
- **Shield of Faith**: A spell that creates a magical shield around one creature, increasing their armor class and making them harder to hit. Strengths include increased defense and survivability. Adds `+2` to the target's armor class.
- **Bless**: A spell that gives allies within range a bonus to their attack rolls and saving throws. Strengths include the ability to support allies and increase their effectiveness in combat. Adds `1d4` to attack rolls and saving throws.

### Weapons

- **Mace**: A blunt weapon that deals bludgeoning damage. Strengths include the ability to bypass certain types of armor and shields. Deals `1d6` bludgeoning damage.
- **WarHammer**: A two-handed weapon that deals heavy bludgeoning damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `1d10` bludgeoning damage.
- **Morningstar**: A spiked weapon that deals piercing and bludgeoning damage. Strengths include the ability to bypass some defenses and deal damage to multiple targets. Deals `1d8` piercing or bludgeoning damage (cleric's choice).
- **Flail**: A weapon with a spiked ball on a chain, dealing bludgeoning and piercing damage. Strengths include the ability to bypass some defenses and deal damage to multiple targets. Deals `1d8` bludgeoning or piercing damage (cleric's choice).
- **Spear**: A versatile weapon that can be used for melee or ranged attacks. Strengths include reach and versatility. Deals `1d6` piercing damage.
- **GreatSword**: A two-handed weapon that deals heavy slashing damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `2d6` slashing damage.
- **LongSword**: A versatile weapon that deals slashing or piercing damage. Strengths include versatility, balanced damage output, and the ability to use with a shield. Deals `1d8` slashing or piercing damage.
- **War Pick**: A weapon with a pointed head that deals piercing damage and can penetrate armor. Strengths include the ability to bypass certain types of armor and shields. Deals `1d8` piercing damage.

## Paladin

### Attacks

Here are some typical attacks for a paladin in Dungeons and Dragons along with their associated strengths, damage, and die to roll for damage:

- **Divine Smite**: A melee attack that deals extra radiant damage if the paladin expends a spell slot. Strengths include high damage output and the ability to bypass some resistances. Deals `2d8`, `3d8`, `4d8`, or `5d8` radiant damage (depending on the level of the expended spell slot).
- **Lay on Hands**: A healing ability that allows the paladin to restore hit points to one creature within range. Strengths include the ability to heal allies and the ability to be used in combat. Can restore up to `5 x` paladin's level in hit points.
- **Smite Evil**: A melee attack that deals extra damage to evil creatures. Strengths include the ability to deal extra damage to certain creatures and the ability to bypass some resistances. Deals extra damage depending on the paladin's level and the target's CR.
- **Aura of Protection**: A passive ability that gives the paladin and nearby allies a bonus to their saving throws. Strengths include increased defense and survivability. Adds the paladin's charisma modifier to the saving throws of allies within range.
- **Divine Favor**: A spell that enhances the paladin's attacks, giving them extra radiant damage. Strengths include increased damage output and the ability to bypass some resistances. Adds `1d4` radiant damage to each attack.
- **Branding Smite**: A spell that causes radiant damage and makes the target easier to hit. Strengths include increased damage output and the ability to debuff the target. Deals `2d6` radiant damage and makes the target easier to hit for the next minute.
- **Thunderous Smite**: A spell that causes thunder damage and knocks the target prone. Strengths include the ability to deal damage and control the battlefield. Deals `2d6` thunder damage and knocks the target prone.
- **Crusader's Mantle**: A spell that creates an aura of radiant energy, giving nearby allies bonus damage on their attacks. Strengths include the ability to support allies and increase their effectiveness in combat. Adds `1d4` radiant damage to each attack made by allies within range.

### Weapons

Here are some typical weapons a paladin would use in Dungeons and Dragons along with their associated strengths, damage, and die to roll for damage:

- **Longsword**: A versatile weapon that deals slashing or piercing damage. Strengths include versatility, balanced damage output, and the ability to use with a shield. Deals `1d8` slashing or piercing damage.
- **Greatsword**: A two-handed weapon that deals heavy slashing damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `2d6` slashing damage.
- Mace: A blunt weapon that deals bludgeoning damage. Strengths include the ability to bypass certain types of armor and shields. Deals `1d6` bludgeoning damage.
- **Warhammer**: A two-handed weapon that deals heavy bludgeoning damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `1d10` bludgeoning damage.
- **Lance**: A versatile weapon that deals piercing damage and can be used while mounted. Strengths include reach and versatility. Deals `1d12` piercing damage (if used while mounted, deals double damage on a charge).
- **Shield**: A defensive weapon that can be used to block attacks and bash enemies. Strengths include increased defense and the ability to use in combination with other weapons. Deals `1d4` bludgeoning damage.
- **Flail**: A weapon with a spiked ball on a chain, dealing bludgeoning and piercing damage. Strengths include the ability to bypass some defenses and deal damage to multiple targets. Deals `1d8` bludgeoning or piercing damage (paladin's choice).
- **War Pick**: A weapon with a pointed head that deals piercing damage and can penetrate armor. Strengths include the ability to bypass certain types of armor and shields. Deals `1d8` piercing damage.

## Elf

### Weapons

**Elves** in Dungeons and Dragons are known for their agility and dexterity, so they tend to excel at ranged combat and finesse attacks. Here are some typical attacks for an elf along with their associated strengths, damage, and die to roll for damage:

- **Longbow**: A ranged weapon that can be used for precise attacks from a distance. Strengths include high accuracy and the ability to deal damage from a safe distance. Deals `1d8` piercing damage.
- **Shortbow**: A smaller version of the longbow that can be used for quick, precise attacks. Strengths include the ability to make ranged attacks and the ability to use with ammunition found in the environment. Deals `1d6` piercing damage.
- **Arrow**: Ammunition for bows, typically made of wood with a pointed metal or stone tip. Strengths include the ability to deal damage from a distance and the ability to use with a variety of bows. Deals piercing damage, the amount depending on the bow used.
- **Rapier**: A slender, thrusting sword that deals piercing damage. Strengths include high accuracy and the ability to bypass some armor. Deals `1d8` piercing damage.
- **Shortsword**: A versatile weapon that can be used for melee attacks. Strengths include versatility and ease of concealment. Deals `1d6` piercing damage.
- **Scimitar**: A curved sword that deals slashing damage. Strengths include versatility and the ability to make quick, agile attacks. Deals `1d6` slashing damage.
- **Dagger**: A small, versatile weapon that can be used for melee or ranged attacks. Strengths include versatility and ease of concealment. Deals `1d4` piercing damage.

#### Magic

**Elves** in Dungeons and Dragons have access to a variety of magical attacks depending on their class and abilities. Here are some examples of magical attacks for an elf along with their associated strengths, damage, and die to roll for damage:

- **Magic Missile**: A spell that fires multiple magical projectiles at a target. Strengths include guaranteed hits and the ability to deal force damage. Deals `1d4+` force damage per missile.
- **Fire Bolt**: A spell that fires a bolt of fire at a target. Strengths include the ability to deal fire damage and the ability to ignite objects. Deals `1d10` fire damage.
- **Ice Knife**: A spell that creates a shard of ice and hurls it at a target. Strengths include the ability to deal cold damage and the ability to explode and deal damage to nearby targets. Deals 1d10 piercing damage plus `2d6` cold damage (on explosion).
- **Moonbeam**: A spell that creates a beam of moonlight that damages targets in its area. Strengths include the ability to deal radiant damage and the ability to affect multiple targets. Deals `2d10` radiant damage per turn.
- **Faerie Fire**: A spell that illuminates targets in a magical light, making them easier to hit. Strengths include the ability to reveal invisible targets and the ability to grant advantage on attacks against affected targets. No damage is dealt.
- **Entangle**: A spell that causes plants in an area to grow and entangle targets, restricting their movement. Strengths include the ability to control the battlefield and restrict enemy movement. No damage is dealt.

## Dwarve

### Weapons

**Dwarves** in Dungeons and Dragons are known for their resilience, strength, and skill at crafting weapons and armor. Here are some typical attacks for a dwarf along with their associated strengths, damage, and die to roll for damage:

**Dwarves** in Dungeons and Dragons are known for their resilience, strength, and skill at crafting weapons and armor. Here are some typical attacks for a dwarf along with their associated strengths, damage, and die to roll for damage:

- **Warhammer**: A two-handed weapon that deals heavy bludgeoning damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `1d10` bludgeoning damage.
- **Battleaxe**: A versatile weapon that can be used for melee attacks. Strengths include versatility and the ability to deal slashing damage. Deals 1d8 slashing damage.
- **Handaxe**: A small, versatile weapon that can be used for melee or ranged attacks. Strengths include versatility and ease of use. Deals `1d6` slashing damage.
- **War Pick:** A weapon with a pointed head that deals piercing damage and can penetrate armor. Strengths include the ability to bypass certain types of armor and shields. Deals `1d8` piercing damage.
- **Greatsword**: A two-handed weapon that deals heavy slashing damage. Strengths include high damage output and the ability to cleave through groups of weaker enemies. Deals `2d6` slashing damage.
- **Crossbow**: A ranged weapon that fires bolts. Strengths include the ability to make ranged attacks and the ability to deal higher damage than a bow. Deals `1d8` piercing damage.
- **Hammer**: A one-handed weapon that deals bludgeoning damage. Strengths include the ability to deal damage to objects and structures. Deals `1d4` bludgeoning damage.

### Magic

**Dwarves** in Dungeons and Dragons have access to a variety of magical attacks depending on their class and abilities. Here are some examples of magical attacks for a dwarf along with their associated strengths, damage, and die to roll for damage:

- **Thunderwave**: A spell that creates a wave of thunderous force, damaging and pushing back targets in its area. Strengths include the ability to deal thunder damage and the ability to push back enemies. Deals `2d8` thunder damage.
- **Heat Metal:** A spell that causes metal objects to become red-hot, damaging those who wear or wield them. Strengths include the ability to bypass armor and the ability to deal fire damage. Deals `2d8` fire damage.
- **Earthquake**: A spell that creates a seismic disturbance, damaging and knocking prone targets in its area. Strengths include the ability to deal bludgeoning damage and the ability to knock down enemies. Deals `1d6` bludgeoning damage per turn.
- **Enlarge/Reduce:** A spell that can enlarge or reduce the size of a target, affecting their damage output and other abilities. Strengths include the ability to increase a target's strength and damage output. Damage dealt depends on the target's abilities and weapons.
- **Stone Shape**: A spell that allows the caster to shape stone and earth, creating barriers or damaging targets. Strengths include the ability to control the battlefield and the ability to deal bludgeoning or piercing damage. Deals `2d6` bludgeoning or piercing damage.
- **Wall of Stone**: A spell that creates a wall of stone, blocking off areas or damaging targets that pass through it. Strengths include the ability to control the battlefield and the ability to deal bludgeoning damage. Deals `10d10` bludgeoning damage if the wall is collapsed.

## Druids

### Attacks

**Druids** in Dungeons and Dragons are known for their connection to nature and ability to use spells that harness natural elements. Here are some examples of magical attacks for a druid along with their associated strengths, damage, and die to roll for damage:

- Call Lightning: A spell that calls down a bolt of lightning to strike a target. Strengths include the ability to deal lightning damage and the ability to hit multiple targets. Deals `3d10` lightning **damage**.
- **Entangle**: A spell that causes plants to grow and entangle targets in an area. Strengths include the ability to restrain targets and the ability to control the battlefield. Deals no damage.
- **Flame Blade**: A spell that creates a sword made of fire. Strengths include the ability to deal fire damage and the ability to function as a melee weapon. Deals `3d6` fire damage.
- **Moonbeam**: A spell that creates a beam of light that damages creatures that pass through it. Strengths include the ability to deal radiant damage and the ability to persist over multiple turns. Deals `2d10` radiant damage.
- **Thunderwave**: A spell that creates a wave of thunderous force, damaging and pushing back targets in its area. Strengths include the ability to deal thunder damage and the ability to push back enemies. Deals `2d8` thunder damage.
- **Ice Storm**: A spell that creates a storm of ice and hail, damaging targets in its area. Strengths include the ability to deal cold damage and the ability to hit multiple targets. Deals 2d8 bludgeoning damage and `4d6` cold damage.

### Weapons

**Druids** in Dungeons and Dragons are known for their connection to nature, and as such they typically prefer to use weapons made from natural materials like wood or stone. Here are some examples of typical weapons for a druid along with their associated strengths and damage:

- **Quarterstaff**: A long, sturdy wooden staff that can be used for both melee and ranged combat. Strengths include its versatility and the ability to be used with two hands for increased damage. Typically deals `1d6` bludgeoning damage.
- **Sickle**: A curved blade attached to a short wooden handle. Strengths include its light weight and the ability to be used for both slashing and piercing attacks. Typically deals `1d4` slashing damage.
- **Club**: A simple wooden or stone club that can be used for bludgeoning attacks. Strengths include its availability and the ability to deal non-lethal damage. Typically deals `1d4` bludgeoning damage.
- **Dart**: A small, lightweight throwing weapon made from wood or bone. Strengths include its range and the ability to be used in stealthy attacks. Typically deals `1d4` piercing damage.
- **Scimitar**: A curved sword with a single-edged blade. Strengths include its versatility and the ability to deal slashing damage. Typically deals `1d6` slashing damage.
- **Javelin**: A lightweight spear that can be thrown at enemies. Strengths include its range and the ability to be used for both ranged and melee attacks. Typically deals `1d6` piercing damage.

## Monsters

Dungeons and Dragons features a wide variety of monsters, each with its own unique strengths and weaknesses. Here are some examples of common monsters in Dungeons and Dragons along with their strengths, weaknesses, and typical attacks:

- **Orc**: A humanoid monster known for its strength and savagery. Orcs often attack in groups, using crude weapons like `greataxes` and javelins. Strengths include high strength and the ability to attack in groups. Weaknesses include low intelligence and susceptibility to magic. Typical attack: `greataxe` (`2d12` slashing damage).

- **Goblin**: A small, mischievous humanoid that often attacks in groups. Goblins use weapons like `shortbows` and `scimitars`, and may employ traps or ambushes. Strengths include speed and the ability to work together. Weaknesses include low strength and susceptibility to fire. Typical attack: `shortbow` (`1d6` piercing damage).

- **Troll**: A large, regenerating monster known for its strength and durability. Trolls can heal quickly from most injuries, but are vulnerable to fire and acid. They often attack with their fists or large weapons like clubs. Strengths include high strength and regeneration. Weaknesses include vulnerability to fire and acid. Typical attack: claw (`2d6` slashing damage).

- **Giant Spider**: A large, poisonous spider that can crawl on walls and ceilings. Giant spiders can attack with their mandibles or poisonous fangs, and can spin webs to trap their prey. Strengths include mobility and the ability to poison their enemies. Weaknesses include vulnerability to fire and cold. Typical attack: bite (`1d8` piercing damage plus poison).

- **Dragon**: A powerful, intelligent monster known for its size and magical abilities. Dragons can breathe fire, ice, acid, or lightning, and can attack with claws, bites, and their powerful tails. They are typically immune to their own element and have high intelligence and perception. Strengths include high strength and magical abilities. Weaknesses depend on the dragon's type, but typically include vulnerability to opposite elements. Typical attack: bite (`2d10` piercing damage) or breath weapon (varies by dragon type).

- **Skeleton**: An undead monster animated by magic or necromancy. Skeletons can be armed with swords, bows, or other weapons, and are often weak to radiant damage. Strengths include resistance to some forms of damage and the ability to reassemble themselves. Weaknesses include vulnerability to radiant damage and difficulty in maneuvering over difficult terrain. Typical attack: short sword (`1d6` piercing damage).

## Character Generation

In Dungeons and Dragons, the initial character generation process involves rolling dice to determine the character's attributes, which represent their physical and mental abilities. Here are the typical characters in Dungeons and Dragons and the associated attribute values, along with the minimum and maximum values and the average values:

- **Fighter**: Fighters typically have high physical attributes like Strength and Constitution. The minimum value for an attribute is 3, while the maximum value is 18. The average value for each attribute is around 10-11, with the possibility for higher values due to rolling for attribute scores.

- **Wizard**: Wizards typically have high mental attributes like Intelligence and Wisdom. The minimum value for an attribute is 3, while the maximum value is 18. The average value for each attribute is around 10-11, with the possibility for higher values due to rolling for attribute scores.

- **Rogue**: Rogues typically have high Dexterity and decent mental attributes like Intelligence and Wisdom. The minimum value for an attribute is 3, while the maximum value is 18. The average value for each attribute is around 10-11, with the possibility for higher values due to rolling for attribute scores.

- **Cleric**: Clerics typically have high mental attributes like Wisdom and Charisma, and a decent Strength or Constitution attribute. The minimum value for an attribute is 3, while the maximum value is 18. The average value for each attribute is around 10-11, with the possibility for higher values due to rolling for attribute scores.

- **Paladin**: Paladins typically have high physical attributes like Strength and Constitution, and a decent mental attribute like Charisma. The minimum value for an attribute is 3, while the maximum value is 18. The average value for each attribute is around 10-11, with the possibility for higher values due to rolling for attribute scores.

- **Druid**: Druids typically have high Wisdom and Constitution attributes. The minimum value for an attribute is 3, while the maximum value is 18. The average value for each attribute is around 10-11, with the possibility for higher values due to rolling for attribute scores.

During character creation, players typically roll `4 six-sided dice` and discard the lowest roll for each attribute. This generates a score between `3` and `18`, which is then assigned to an attribute. This process is repeated until all six attributes are assigned scores. Some players may use a point-buy system instead, which allows them to purchase attribute scores with a set number of points. The average attribute score for a character using the `4d6` method is around `12-13`.

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

The min's and max's are the same for each class (in our case anyway).

| Attribute    | Min | Max |
| :----------- | :-: | :-: |
| Strength     |  3  | 18  |
| Dexterity    |  3  | 18  |
| Constitution |  3  | 18  |
| Intelligence |  3  | 18  |
| Wisdom       |  3  | 18  |
| Charisma     |  3  | 18  |

### Druid

For a druid, their primary attributes are **Wisdom** and **Constitution**. Here are the average, minimum, and maximum attribute values for a druid character:

| Attribute    | Average |
| :----------- | :-----: |
| Strength     |  10-11  |
| Dexterity    |  10-11  |
| Constitution |  12-13  |
| Intelligence |  10-11  |
| Wisdom       |  12-13  |
| Charisma     |  10-11  |

### Warrior

For a warrior, their primary attributes are Strength, Dexterity, and Constitution. Here are the average, minimum, and maximum attribute values for a warrior character:

| Attribute    | Average |
| :----------- | :-----: |
| Strength     |  12-13  |
| Dexterity    |  10-11  |
| Constitution |  12-13  |
| Intelligence |  10-11  |
| Wisdom       |  10-11  |
| Charisma     |  10-11  |

### Wizard

For a wizard, their primary attribute is Intelligence, and they typically have lower physical attributes. Here are the average, minimum, and maximum attribute values for a wizard character:

| Attribute    | Average |
| :----------- | :-----: |
| Strength     |  10-11  |
| Dexterity    |  10-11  |
| Constitution |  10-11  |
| Intelligence |  12-13  |
| Wisdom       |  10-11  |
| Charisma     |  10-11  |

### Cleric

For a cleric, their primary attributes are Wisdom and Charisma, and they also typically have a decent Strength or Constitution attribute. Here are the average, minimum, and maximum attribute values for a cleric character:

| Attribute    | Average |
| :----------- | :-----: |
| Strength     |  10-11  |
| Dexterity    |  10-11  |
| Constitution |  10-11  |
| Intelligence |  10-11  |
| Wisdom       |  12-13  |
| Charisma     |  12-13  |

### Paladin

For a paladin, their primary attributes are Strength and Charisma, and they also typically have a decent Constitution or Wisdom attribute. Here are the average, minimum, and maximum attribute values for a paladin character:

| Attribute    | Average |
| :----------- | :-----: |
| Strength     |  12-13  |
| Dexterity    |  10-11  |
| Constitution |  12-13  |
| Intelligence |  10-11  |
| Wisdom       |  10-11  |
| Charisma     |  12-13  |

### Rogue

For a rogue, their primary attributes are Dexterity and Charisma, and they also typically have a decent Intelligence attribute. Here are the average, minimum, and maximum attribute values for a rogue character:

| Attribute    | Average |
| :----------- | :-----: |
| Strength     |  10-11  |
| Dexterity    |  12-13  |
| Constitution |  10-11  |
| Intelligence |  12-13  |
| Wisdom       |  10-11  |
| Charisma     |  12-13  |

```json
{
  "Warrior": {
    "Strength": 18,
    "Dexterity": 14,
    "Constitution": 16,
    "Intelligence": 10,
    "Wisdom": 12,
    "Charisma": 8
  },
  "Wizard": {
    "Strength": 8,
    "Dexterity": 12,
    "Constitution": 10,
    "Intelligence": 18,
    "Wisdom": 14,
    "Charisma": 10
  },
  "Rogue": {
    "Strength": 12,
    "Dexterity": 18,
    "Constitution": 14,
    "Intelligence": 12,
    "Wisdom": 10,
    "Charisma": 14
  },
  "Cleric": {
    "Strength": 14,
    "Dexterity": 10,
    "Constitution": 16,
    "Intelligence": 12,
    "Wisdom": 18,
    "Charisma": 10
  },
  "Paladin": {
    "Strength": 18,
    "Dexterity": 12,
    "Constitution": 16,
    "Intelligence": 10,
    "Wisdom": 14,
    "Charisma": 16
  },
  "Druid": {
    "Strength": 14,
    "Dexterity": 14,
    "Constitution": 16,
    "Intelligence": 12,
    "Wisdom": 18,
    "Charisma": 10
  },
  "Dwarf": {
    "Strength": 16,
    "Dexterity": 10,
    "Constitution": 18,
    "Intelligence": 12,
    "Wisdom": 14,
    "Charisma": 8
  },
  "Elf": {
    "Strength": 10,
    "Dexterity": 18,
    "Constitution": 12,
    "Intelligence": 16,
    "Wisdom": 14,
    "Charisma": 12
  }
}
```

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
