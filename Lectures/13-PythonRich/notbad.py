import random
from rich.console import Console
from rich.progress import Progress, BarColumn
from rich.live import Live

console = Console()


class Character:
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


def battle_simulator(player1, player2):
    progress = Progress(
        "[bold]{task.fields[player_name]}",
        BarColumn(bar_width=None),
        "{task.percentage:.0f}%",
        expand=True,
    )

    with Live(progress, refresh_per_second=1) as live:
        player1_task = progress.add_task(
            "player1", player_name=player1.name, total=player1.max_health
        )
        player2_task = progress.add_task(
            "player2", player_name=player2.name, total=player2.max_health
        )

        while not (player1.is_dead() or player2.is_dead()):
            attack_type, damage = player1.attack(player2)
            console.print(
                f"{player1.name} attacks {player2.name} with {attack_type} dealing {damage} damage."
            )
            progress.update(player1_task, completed=player1.current_health)
            progress.update(player2_task, completed=player2.current_health)

            if player2.is_dead():
                break

            attack_type, damage = player2.attack(player1)
            console.print(
                f"{player2.name} attacks {player1.name} with {attack_type} dealing {damage} damage."
            )
            progress.update(player1_task, completed=player1.current_health)
            progress.update(player2_task, completed=player2.current_health)

            live.refresh()

    winner = player1.name if not player1.is_dead() else player2.name
    console.print(f"[bold green]The winner is {winner}!")


player1_attacks = [("Fireball", 8), ("Sword Slash", 6), ("Magic Missile", 4)]
player2_attacks = [("Ice Shard", 7), ("Arrow Shot", 5), ("Lightning Bolt", 9)]

player1 = Character("Alice", 50, player1_attacks)
player2 = Character("Bob", 50, player2_attacks)

battle_simulator(player1, player2)
