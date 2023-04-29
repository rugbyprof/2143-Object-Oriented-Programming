import time
from rich.console import Console
from rich.panel import Panel
from rich.text import Text
from rich.progress import BarColumn

# Initialize console
console = Console()


# Function to get color based on health percentage
def get_bar_color(health_percentage):
    if health_percentage > 60:
        return "green"
    elif health_percentage > 40:
        return "yellow"
    elif health_percentage > 20:
        return "orange"
    else:
        return "red"


def draw_horizontal_bars(player1_health, player2_health, total_health):
    console.clear()  # Clear the console

    player1_percentage = player1_health * 100 / total_health
    player2_percentage = player2_health * 100 / total_health

    player1_bar_color = get_bar_color(player1_percentage)
    player2_bar_color = get_bar_color(player2_percentage)

    player1_bar = f"[{player1_bar_color}]" + "█" * int(player1_percentage / 5) + "[/]"
    player2_bar = f"[{player2_bar_color}]" + "█" * int(player2_percentage / 5) + "[/]"

    content = Text(f"Player 1: {player1_bar}\nPlayer 2: {player2_bar}")
    panel = Panel(content, title="Current Battle", border_style="blue")

    console.print(panel)


# Example usage
total_health = 100
player1_health = 100
player2_health = 100

for i in range(100):
    time.sleep(0.1)
    player1_health -= 1
    player2_health -= 0.5
    draw_horizontal_bars(player1_health, player2_health, total_health)
