import os
import sys
import time
from tqdm import tqdm


def draw_vertical_bars(player1_health, player2_health, total_health):
    os.system("cls" if os.name == "nt" else "clear")  # Clear the terminal

    def get_color(health_percentage):
        if health_percentage > 60:
            return "\033[32m"  # Green
        elif health_percentage > 40:
            return "\033[33m"  # Yellow
        elif health_percentage > 20:
            return "\033[93m"  # Orange
        else:
            return "\033[31m"  # Red

    def draw_bar(health, total_health):
        filled = int(health * 20 / total_health)  # Scale health to 20 units for the bar
        color = get_color(health * 100 / total_health)
        return f"{color}{'█' * filled}{'░' * (20 - filled)}\033[0m"

    bar1 = draw_bar(player1_health, total_health)
    bar2 = draw_bar(player2_health, total_health)

    print("Player 1".center(20) + " " * 10 + "Player 2".center(20))
    for i in range(20, 0, -1):
        line = f"{bar1[i - 1]}".center(20) + " " * 10 + f"{bar2[i - 1]}".center(20)
        print(line)


# Example usage
total_health = 100
player1_health = 100
player2_health = 100

for i in range(100):
    time.sleep(0.1)
    player1_health -= 1
    player2_health -= 0.5
    draw_vertical_bars(player1_health, player2_health, total_health)
