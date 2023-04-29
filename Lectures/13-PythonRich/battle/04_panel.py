import random
import time

from rich.live import Live
from rich.table import Table
from rich import box
from rich.panel import Panel

import json

class RandomData:
    """Needed to create cool character names with simple attacks. So I did."""

    def __init__(self):
        with open("attacks.json") as f:
            self.attacks = json.load(f)
        with open("names.json") as f:
            self.names = json.load(f)

        self.first = []
        self.last = []
        for name in self.names:
            f, l = name.split()
            if not f in self.first:
                self.first.append(f)
            if not l in self.last:
                self.last.append(l)

    def randName(self):
        """Get a random name + surname"""
        random.shuffle(self.first)
        random.shuffle(self.last)
        return self.first[0] + " " + self.last[0]

    def randAttack(self):
        """get a random attack (name of attack, value)"""
        random.shuffle(self.attacks)
        return self.attacks[0]


class Player:
    """Simple character that is not complex"""

    def __init__(self, name, max_health, attack_types):
        self.name = name
        self.max_health = max_health
        self.current_health = max_health
        self.attack_types = attack_types

    def is_dead(self):
        return self.current_health <= 0

    def attack(self, target=None):
        print(target)
        attack_type, damage, emoji = random.choice(self.attack_types)
        
        success = target.defend()
        
        if target and not success:
            target.current_health -= damage
            #target.current_health = max(target.current_health, 0)
        return attack_type, damage, emoji, success
    
    def defend(self):
        """This could be some fancy formula based on the attacker's attack 
        type and the defender's defense type plus player stats, but its just
        random.
        """
        if random.random() > 0.5:
            return False
        return True

    # def __str__(self):
    #     return f"{self.name} {self.max_health}, {self.attack_types}"
    def __str__(self):
        return f"{self.name} {self.current_health}/{self.max_health}"


class LiveData:
    def __init__(self):
        self.players = []
        
        self.rando = RandomData()

        name,attacks = self.generate_player_info()
        self.player1 = Player(name,100,attacks)
        
        name,attacks = self.generate_player_info()
        self.player2 = Player(name,100,attacks)    
        
    def generate_player_info(self,num_attacks = 5):
        attacks = []
        name = self.rando.randName()
        for i in range(num_attacks):
            attacks.append(self.rando.randAttack())
            
        return name,attacks
            
        
    def generate_table(self) -> Table:
        """Make a new table."""
        self.table = Table()
        self.table.add_column("Player 1",justify="center", style="red")
        self.table.add_column("Stuff",justify="left", style="yellow")
        self.table.add_column("Player 2",justify="center", style="green")
        
        
        attacker, defender = (self.player1, self.player2) if random.random() < 0.5 else (self.player2, self.player1)
        
        attack,value,emoji,success = attacker.attack(defender)
        
        panel1 = Panel(f"{str(self.player1)}")
        panel2 = Panel(f"{str(self.player2)}")
        panel3 = Panel(f"Attack: {attack} {emoji}\nValue: {value}\nSuccess: {success}")
        
        
        
        self.table.add_row(
            panel1,
            panel3,
            panel2,
        )

        return self.table
        


if __name__ == "__main__":
    ld = LiveData()
    with Live(ld.generate_table(), refresh_per_second=4) as live:
        for _ in range(40):
            time.sleep(0.4)
            live.update(ld.generate_table())