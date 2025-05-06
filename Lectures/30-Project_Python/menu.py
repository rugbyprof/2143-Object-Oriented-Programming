from InquirerPy import inquirer
from os.path import isfile
from quotesDB import QuotesDB
from random import choice
from rich import print
from rich import box
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

term_size = shutil.get_terminal_size()
width = int(term_size.columns * 0.75)
height = int(term_size.lines * 0.75)

console = Console()

colors = [
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


def panelize(
    content,
    *,
    title=None,
    subtitle=None,
    style="white on black",
    border_style="white",
    width=None,
    markdown=False,
    syntax=None,
    justify="left",
):
    """Prints a styled panel with text, markdown, or syntax-highlighted code.

    Args:
          content (str): The text to wrap.
          title (str): Optional panel title.
          subtitle (str): Optional bottom label.
          style (str): Style for panel text and fill.
          border_style (str): Style just for the border.
          width (int): Optional width constraint.
          markdown (bool): Interpret content as Markdown.
          syntax (str): Language name for syntax highlighting (e.g., "python").
    """
    if syntax:
        rendered = Syntax(content, syntax, line_numbers=False)
    elif markdown:
        rendered = Markdown(content)
    else:
        rendered = content

    panel = Panel(
        rendered,
        title=title,
        subtitle=subtitle,
        style=style,
        border_style=border_style,
        width=width,
    )
    console.print(panel, justify=justify)


def submenuCreate():
    global db
    tool = inquirer.select(
        message="Choose a tool to install:",
        choices=["gcc", "gdb", "valgrind", "Back"],
        default=None,
    ).execute()

    if tool == "Back":
        return
    print(f"[green]Installing {tool}... Done![/green]")
    submenuCreate(db)  # Re-enter submenu after action


def submenuSearch():
    global db
    searchType = inquirer.select(
        message="Search Type", choices=["Keyword", "Author", "Back"], default="keyword"
    ).execute()

    if searchType == "Keyword":
        keyword = Console.input("[blue]Enter the keyword to find: [/blue]")
        result = db.read(keyword=keyword)
        print(f"[green]Searching for {keyword}... Done![/green]")
        print(result)
    elif searchType == "Author":
        pass
    elif searchType == "Back":
        return

    print(f"[green]Find ... Done![/green]")
    submenuSearch()  # Re-enter submenu after action


def submenuDelete2():
    global db
    choice = inquirer.select(
        message="Delete Record:",
        choices=["Enter Row Id", "Back"],
    ).execute()

    if choice == "Back":
        return

    input = Console.input("[blue]Enter the row ID to delete: [/blue]")
    if not input.isdigit():
        print("[red]Invalid input. Please enter a valid row ID.[/red]")
        return
    row_id = int(input)
    db.delete(row_id)
    print(f"[blue]{choice} Deleted [/blue]")
    submenuDelete2()


def submenuDelete():
    global db  # Assuming db has a .delete(id) method

    os.system("clear")

    # Display menu inside a rich panel
    panel_title = "[bold cyan]Delete Menu[/bold cyan]"
    panel_body = "[green]Choose a delete option from below.[/green]"

    console.print(Panel(panel_body, title=panel_title, expand=False))

    choice = inquirer.select(
        message="Delete Record:",
        choices=["Enter Row Id", "Back"],
    ).execute()

    if choice == "Back":
        return

    # Display prompt inside a panel again (optional)
    os.system("clear")
    console.print(
        Panel("[blue]Enter the row ID to delete:[/blue]", title="Input", expand=False),
        end="",
    )
    row_input = console.input("→ ")

    if not row_input.isdigit():
        console.print("[red]Invalid input. Please enter a valid row ID.[/red]")
        return

    row_id = int(row_input)
    db.delete(row_id)

    console.print(
        Panel(
            f"[green]Row ID {row_id} successfully deleted.[/green]",
            title="Success",
            expand=False,
        )
    )

    # Recursive call for next operation
    submenuDelete()


from rich.console import Console, Group
from rich.panel import Panel
from rich.align import Align
from rich.layout import Layout


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


def mainPanel():
    global console

    # Outer container for the full menu
    outer_panel = Panel(
        Align.center(menu_panel, vertical="middle"),
        border_style="green",
        title="[bold yellow]Main Menu System[/bold yellow]",
        subtitle="Use arrow keys or numbers to navigate",
        box=box.DOUBLE,
        width=width,
        height=height,
    )
    return outer_panel


def show_submenu(title: str, subtitle: str, options: list[str], buffer: int = 10):
    console = Console()
    width = int(term_size.columns * 0.75)
    height = int(term_size.lines * 0.75)

    # Menu content (numbered list)
    menu_choices = "\n".join(
        f"[bold cyan]{i+1}.[/bold cyan] {opt}" for i, opt in enumerate(options)
    )

    menu_panel = Panel(
        Align.center(Group(menu_choices), vertical="middle"),
        title=title,
        subtitle=subtitle,
        border_style="bright_magenta",
        style="on black",
        box=box.ROUNDED,
        width=width - 10,
    )

    clear_screen()
    console.print(Align.center(outer_panel, vertical="middle"))


def main_menu():
    # db = candyDB(filename)
    global db

    # panel_content = Group(
    #     "[green]Choose a delete option[/green]",
    #     "[dim]Press [b]Enter[/b] to continue[/dim]",
    # )

    # console.print(Panel(panel_content, title="Delete Menu", expand=False))
    # row_input = console.input("[blue]Row ID → [/blue]")

    show_submenu(
        title="Delete Menu",
        subtitle="Choose an option below",
        options=["Enter Row Id", "Back", "Wipe All Records"],
    )
    row_input = console.input("→ ")

    while True:
        os.system("clear")
        choice = inquirer.select(
            message="CRUD Menu:",
            choices=["Create", "Search", "Update", "Delete", "Exit"],
        ).execute()

        if choice == "Create":
            submenuCreate()
        elif choice == "Search":
            submenuSearch()
        elif choice == "Update":
            print("[yellow]Update functionality is not implemented yet.[/yellow]")
        elif choice == "Delete":
            submenuDelete()
        elif choice == "Exit":
            print("[bold red]Goodbye![/bold red]")
            break


if __name__ == "__main__":
    main_menu()
