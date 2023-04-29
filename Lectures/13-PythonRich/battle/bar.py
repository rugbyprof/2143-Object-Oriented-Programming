from rich.progress import Progress
import time

player_health = 100  # starting health
max_health = 100  # maximum health

def update_health_bar(health, max_health):
    with Progress() as progress:
        task_id = progress.add_task("[green]Health:", total=max_health, live=True)
        while health > 0:
            progress.update(task_id, completed=health)
            health -= 10
            time.sleep(0.5)

# initial health bar
update_health_bar(player_health, max_health)
