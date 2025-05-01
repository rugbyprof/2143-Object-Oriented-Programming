from InquirerPy import inquirer
from rich import print
from quotesDB import QuotesDB
from rich.console import Console

db = QuotesDB("../../Resources/06-Data/quotes/quotes_all.json")


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


def submenuDelete():
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
    submenuDelete()


def main_menu():
    # db = candyDB(filename)
    global db
    while True:
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
