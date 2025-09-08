from InquirerPy import inquirer
from rich.console import Console
from rich.panel import Panel

console = Console()


def submenu_panel(title, subtitle):
    panel = Panel(
        "[bold green]Use arrow keys to select an option[/bold green]",
        title=title,
        subtitle=subtitle,
        border_style="bright_blue",
        expand=False,
    )
    console.print(panel)


def submenu_loop():
    while True:
        console.clear()
        submenu_panel("Delete Menu", "Select an Option")

        choice = inquirer.select(
            message="What do you want to do?",
            choices=["Enter Row ID", "Back"],
            qmark="👉",
            amark="✔️",
        ).execute()

        if choice == "Back":
            break

        console.print(
            Panel(
                f"[cyan]You chose: {choice}[/cyan]", title="Selection", justify="center"
            )
        )

        # simulate row input prompt
        row_id = console.input("[bold yellow]Enter Row ID to delete:[/bold yellow] ")
        if not row_id.isdigit():
            console.print("[red]Invalid row ID[/red]")
        else:
            console.print(f"[green]Row ID {row_id} deleted![/green]")

        console.input("\n[dim]Press enter to continue...[/dim]")


submenu_loop()
