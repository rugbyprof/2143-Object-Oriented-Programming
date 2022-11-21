from random import shuffle

c = 5

fighters = ['Warrior']*c + ['Wizard']*c + ['Archer']*c + ['Elf'] + ['DragonBorn']


horde = []
for i in range(100):
    horde.extend(fighters)

shuffle(horde)

with open("attackers.in","w") as f:
    for attacker in horde:
        f.write(attacker+"\n")
