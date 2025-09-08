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

    # panel_content = Group(
    #     "[green]Choose a delete option[/green]",
    #     "[dim]Press [b]Enter[/b] to continue[/dim]",
    # )

    # console.print(Panel(panel_content, title="Delete Menu", expand=False))
    # row_input = console.input("[blue]Row ID → [/blue]")