"""

Demonstrates the use of multiple Progress instances in a single Live display.    

"""

from time import sleep

from rich.live import Live
from rich.panel import Panel
from rich.progress import Progress, SpinnerColumn, BarColumn, TextColumn
from rich.table import Table
import random


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


team_progress = Progress(
    "{task.description}",
    SpinnerColumn(),
    BarColumn(),
    TextColumn("[progress.percentage]{task.percentage:>3.0f}%"),
)

team1 = Team(size=100, maxAttacks=3)
team2 = Team(size=100, maxAttacks=3)


team1 = team_progress.add_task("[green]Team One", total=len(team1.team))
team2 = team_progress.add_task("[magenta]Team Two", total=len(team2.team))


total = sum(task.total for task in team_progress.tasks)
overall_progress = Progress()
overall_task = overall_progress.add_task("All Teams", total=int(total))

progress_table = Table.grid()
progress_table.add_row(
    Panel.fit(
        overall_progress, title="Overall Progress", border_style="green", padding=(2, 2)
    ),
    Panel.fit(team_progress, title="[b]Jobs", border_style="red", padding=(1, 2)),
)

with Live(progress_table, refresh_per_second=10):
    while not overall_progress.finished:
        sleep(0.1)
        for job in team_progress.tasks:
            if not job.finished:
                team_progress.advance(job.id)

        completed = sum(task.completed for task in team_progress.tasks)
        overall_progress.update(overall_task, completed=completed)
