class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, amount):
        self.health = max(0, self.health - amount)
        return self.health

    def attack(self):
        return f"{self.name} strikes", 5

    def __str__(self):
        return f"Name:\t{self.name}\nHealth:\t{self.health}\n"


class Knight(Fighter):
    def __init__(self, name, health, armor):
        super().__init__(name, health)
        self.armor = armor

    def take_damage(self, amount):
        blocked = min(self.armor, amount)
        remaining = amount - blocked
        return super().take_damage(remaining)

    def attack(self):
        return f"{self.name} swings a sword", 8

    def __str__(self):
        pstr = super().__str__()
        return f"{pstr}Armor:\t{self.armor}\n"


class Wizard(Fighter):
    def __init__(self, name, health, mana):
        super().__init__(name, health)
        self.mana = mana

    def attack(self):
        if self.mana >= 5:
            self.mana -= 5
            return f"{self.name} casts a fire bolt", 10
        return f"{self.name} uses a staff", 3

    def __str__(self):
        pstr = super().__str__()
        return f"{pstr}Mana:\t{self.mana}\n"


def run_round(attacker, defender):
    message, damage = attacker.attack()
    defender.take_damage(damage)
    print(message)
    print(f"{defender.name} has {defender.health} health left.")


aria = Knight("Aria", 40, armor=3)
milo = Wizard("Milo", 30, mana=10)

run_round(milo, aria)
run_round(aria, milo)


# for i in range(5, 9):
#     with open(f"Lesson_0{i}.py", "w", encoding="utf-8") as f:
#         f.close()
