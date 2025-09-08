from InquirerPy import inquirer
from os.path import isfile
from quotesDB import QuotesDB
from random import choice
from rich import box
from rich import print
from rich.align import Align
from rich.console import Console
from rich.console import Group
from rich.layout import Layout
from rich.markdown import Markdown
from rich.panel import Panel
from rich.syntax import Syntax
from time import sleep
import json
import os
import sys
import shutil

# Globals
TERMSIZE = shutil.get_terminal_size()
WIDTH = int(TERMSIZE.columns * 0.75)
HEIGHT = int(TERMSIZE.lines * 0.5)
CONSOLE = Console()
COLORS = [
    "#FF5733",  # Hot Orange
    "#FFC300",  # Bright Yellow
    "#DAF7A6",  # Light Lime
    "#33FF57",  # Neon Green
    "#00FFFF",  # Aqua Blue
    "#33C1FF",  # Electric Sky Blue
    "#335BFF",  # Vivid Blue
    "#9D33FF",  # Vivid Purple
    "#FF33F6",  # Magenta Pink
    "#FF3380",  # Candy Pink
    "#FF6F33",  # Sunset Orange
    "#FFEB33",  # Banana Yellow
]
db = QuotesDB("../../Resources/06-Data/quotes/quotes_all.json")


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


def mainPanel(sub_menu):
    global CONSOLE

    # Outer container for the full menu
    both_panels = Panel(
        Align.center(sub_menu, vertical="middle"),
        border_style="green",
        title="[bold yellow]Main Menu System[/bold yellow]",
        subtitle=None,
        box=box.DOUBLE,
        width=WIDTH,
        height=HEIGHT,
    )
    return both_panels


def showSubmenu(title: str, subtitle: str, options: list[str], buffer: int = 10):

    # Menu content (numbered list)
    menu_choices = "\n".join(
        f"[bold cyan]{i+1}.[/bold cyan] {opt}" for i, opt in enumerate(options)
    )

    sub_panel = Panel(
        Align.center(Group(menu_choices), vertical="middle"),
        title=title,
        subtitle=subtitle,
        border_style="bright_magenta",
        style="on black",
        box=box.ROUNDED,
        width=WIDTH - buffer,
    )

    clear_screen()
    CONSOLE.print(mainPanel(sub_panel))
    input = CONSOLE.input("→ ")


def main_menu():
    # db = candyDB(filename)
    global db

    while True:
        os.system("clear")
        choice = inquirer.select(
            message="CRUD Menu:",
            choices=["Create", "Search", "Update", "Delete", "Exit"],
        ).execute()

        if choice == "Create":
            showSubmenu(
                title="Insert Menu",
                subtitle=None,
                options=["Enter Values", "Back"],
            )
        elif choice == "Search":
            showSubmenu(
                title="Search Menu",
                subtitle=None,
                options=["Enter Row Id", "Search by Keyword", "Back"],
            )
        elif choice == "Update":
            showSubmenu(
                title="Update Menu",
                subtitle=None,
                options=["Enter Row Id followed by ...", "Back"],
            )
        elif choice == "Delete":
            showSubmenu(
                title="Delete Menu",
                subtitle=None,
                options=["Enter Row Id", "Back", "Wipe All Records"],
            )
        elif choice == "Exit":
            print("[bold red]Goodbye![/bold red]")
            break


if __name__ == "__main__":
    main_menu()
