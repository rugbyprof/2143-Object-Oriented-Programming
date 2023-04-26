import random
from rich import print
from rich.console import Console
from rich.progress import Progress, BarColumn, TextColumn
from rich.live import Live
from rich.layout import Layout
from rich.panel import Panel
import json
from time import sleep

console = Console()


class RandomCharacters:
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


class Character:
    """Simple character that is not complex"""

    def __init__(self, name, max_health, attack_types):
        self.name = name
        self.max_health = max_health
        self.current_health = max_health
        self.attack_types = attack_types

    def is_dead(self):
        return self.current_health <= 0

    def attack(self, target):
        attack_type, damage = random.choice(self.attack_types)
        target.current_health -= damage
        target.current_health = max(target.current_health, 0)
        return attack_type, damage

    def __str__(self):
        return f"{self.name} {self.max_health}, {self.attack_types}"


class Team:
    """represents a simple list of characters
    This really is a glorified function
    """

    def __init__(self, size=100, maxAttacks=5, name="wtf pick a name"):
        self.team = []
        self.name = name

        rando = RandomCharacters()

        for i in range(size):
            name = rando.randName()
            attacks = []

            for i in range(maxAttacks):
                attacks.append(rando.randAttack())

            self.team.append(Character(name, random.randint(30, 70), attacks))

    def teamStatus(self):
        """Ratio of dead vs alive"""
        dead = 0
        for player in self.team():
            if player.is_dead():
                dead += 1

        return dead / len(self.team)

    def getNext(self):
        """Return a random player to fight. But not a dead one."""
        random.shuffle(self.team)
        while self.team[0].is_dead():
            random.shuffle(self.team)
        return self.team[0]

    def __str__(self):
        output = ""
        i = 1
        for player in self.team:
            output += f"{i}. {str(player)}\n"
            i += 1
        return output


# def battle_simulator(player1, player2):
#     progress = Progress(
#         "[bold]{task.fields[player_name]}",
#         BarColumn(bar_width=None),
#         "{task.percentage:.0f}%",
#         expand=True,
#     )

#     with Live(progress, refresh_per_second=1) as live:
#         player1_task = progress.add_task(
#             "player1", player_name=player1.name, total=player1.max_health
#         )
#         player2_task = progress.add_task(
#             "player2", player_name=player2.name, total=player2.max_health
#         )

#         while not (player1.is_dead() or player2.is_dead()):
#             attack_type, damage = player1.attack(player2)
#             console.print(
#                 f"{player1.name} attacks {player2.name} with {attack_type} dealing {damage} damage."
#             )
#             progress.update(player1_task, completed=player1.current_health)
#             progress.update(player2_task, completed=player2.current_health)

#             if player2.is_dead():
#                 break

#             attack_type, damage = player2.attack(player1)
#             console.print(
#                 f"{player2.name} attacks {player1.name} with {attack_type} dealing {damage} damage."
#             )
#             progress.update(player1_task, completed=player1.current_health)
#             progress.update(player2_task, completed=player2.current_health)

#             live.refresh()

#     winner = player1.name if not player1.is_dead() else player2.name
#     console.print(f"[bold green]The winner is {winner}!")


def battle_simulator(team1, team2):
    progress1 = Progress(
        "[bold]{team1.name}",
        BarColumn(bar_width=None),
        "{task.percentage:.0f}%",
        expand=True,
    )
    progress2 = Progress(
        "[bold]{team2.name}",
        BarColumn(bar_width=None),
        "{task.percentage:.0f}%",
        expand=True,
    )

    for n in progress1.track(range(100)):
        progress1.print(n)
        sleep(0.1)
    for n in progress2.track(range(100)):
        progress2.print(n)
        sleep(0.1)


# battle_simulator(player1, player2)

if __name__ == "__main__":
    layout = Layout()

    layout.split_column(
        Layout(name="header", size=8),
        Layout(name="body"),
        Layout(name="footer", size=3),
    )

    layout["body"].split_row(
        Layout(Panel("Cowboys", title="[red]Team One")),
        Layout(Panel("Indians", title="[green]Team Two")),
    )

    team1 = Team(size=100, maxAttacks=3)
    team2 = Team(size=100, maxAttacks=3)

    battle_simulator(team1, team2)

    print(layout)
