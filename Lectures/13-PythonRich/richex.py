import os
import time
from rich.console import Console
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


def draw_vertical_bars(player1_health, player2_health, total_health):
    os.system("cls" if os.name == "nt" else "clear")  # Clear the terminal

    # Render player names
    console.print("Player 1".center(20) + " " * 10 + "Player 2".center(20))

    # Render health bars
    for i in range(20, 0, -1):
        bar1_color = get_bar_color(player1_health * 100 / total_health)
        bar2_color = get_bar_color(player2_health * 100 / total_health)
        bar1_filled = "█" if player1_health * 20 / total_health >= i else "░"
        bar2_filled = "█" if player2_health * 20 / total_health >= i else "░"

        console.print(
            f"[{bar1_color}]{bar1_filled}[/]" * 10
            + " " * 10
            + f"[{bar2_color}]{bar2_filled}[/]" * 10
        )


# Example usage
total_health = 100
player1_health = 100
player2_health = 100

for i in range(100):
    time.sleep(0.1)
    player1_health -= 1
    player2_health -= 0.5
    draw_vertical_bars(player1_health, player2_health, total_health)
