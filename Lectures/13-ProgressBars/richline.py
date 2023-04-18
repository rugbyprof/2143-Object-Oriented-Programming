from rich.console import Console
from rich.table import Table
from rich.text import Text
from rich.live import Live
import time
import random

# Initialize console
console = Console()


def coloredLine(length, color, max_width):
    line = str("─" * length)
    spaces = str(" " * (max_width - length))
    return Text(line, style=f"bold {color}") + Text(spaces)


def makeRow(name, length, padding, color):
    line = str("─" * length)
    spaces = str(" " * padding)
    return Text(name) + Text(line, style=f"bold {color}") + Text(spaces)


def create_table(
    team1_name,
    team_length1,
    teamcolor1,
    team2_name,
    team_length2,
    teamcolor2,
    player1_name,
    length1,
    color1,
    player2_name,
    length2,
    color2,
    max_width,
):
    table = Table(show_header=True, header_style="bold blue", border_style="blue")

    # Add four columns with fixed width
    table.add_column("Team")
    table.add_column("Progress")
    table.add_column("Player")
    table.add_column("Progress")

    # Create colored lines of specified lengths

    # Add a row to the table
    table.add_row(
        Text(team1_name),
        coloredLine(team_length1, teamcolor1, max_width),
        Text(player1_name),
        coloredLine(length1, color1, max_width),
    )
    table.add_row(
        Text(team2_name),
        coloredLine(team_length2, teamcolor2, max_width),
        Text(player2_name),
        coloredLine(length2, color2, max_width),
    )

    return table


def get_bar_color(progress):
    if progress > 0.6:
        return "green"
    elif progress > 0.4:
        return "yellow"
    elif progress > 0.2:
        return "orange"
    else:
        return "red"


# Example usage
team1_name = "Team 1"
team2_name = "Team 2"
player1_name = "Player 1"
player2_name = "Player 2"
initial_length = 50
max_width = 50
lengthp1 = 50
lengthp2 = 50
lengtht1 = 50
lengtht2 = 50


with Live(console=console, auto_refresh=False) as live:
    for i in range(initial_length + 1):
        lengthp1 += random.randint(-3, 0)
        lengthp2 += random.randint(-3, 0)
        lengtht1 += random.randint(-2, 1)
        lengtht2 += random.randint(-2, 1)
        color1 = get_bar_color(lengthp1 / initial_length)
        color2 = get_bar_color(lengthp2 / initial_length)
        teamcolor1 = get_bar_color(lengtht1 / initial_length)
        teamcolor2 = get_bar_color(lengtht2 / initial_length)

        table = create_table(
            team1_name,
            lengtht1,
            teamcolor1,
            team2_name,
            lengtht2,
            teamcolor2,
            player1_name,
            lengthp1,
            color1,
            player2_name,
            lengthp2,
            color2,
            max_width,
        )

        live.update(table)
        live.refresh()
        time.sleep(0.1)
