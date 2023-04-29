from rich.progress import Progress, BarColumn, TextColumn, ProgressColumn, TimeRemainingColumn
from rich.style import Style
from rich import Live


# Define custom styles for each range of values
green_style = Style(color="green")
yellow_style = Style(color="yellow")
orange_style = Style(color="dark_orange")
red_style = Style(color="red")

# Define a function to return the style for a given value
def get_style(value):
    if value >= 85:
        return green_style
    elif value >= 70:
        return yellow_style
    elif value >= 40:
        return orange_style
    else:
        return red_style

# Create a progress bar with custom style
progress=Progress(
    BarColumn(bar_width=None),
    TextColumn("[progress.description]{task.description}", justify="right"),
    TextColumn("[progress.percentage]{task.percentage:>3.0f}%", justify="right"),
    TimeRemainingColumn(),
    console=None,
    transient=True,
)

task = progress.add_task("[cyan]Downloading...", total=100)

with Live(progress, refresh_per_second=10):
    while not overall_progress.finished:
        sleep(0.1)
        for job in job_progress.tasks:
            if not job.finished:
                job_progress.advance(job.id)

        completed = sum(task.completed for task in job_progress.tasks)
        overall_progress.update(overall_task, completed=completed)


# Update the progress bar with values from 100 to 0
for value in range(100, -1, -1):
    # Get the style for the current value
    style = get_style(value)
  

    # Update the progress bar with the current value and style
    progress.update(task, advance=1, style=style, description=f"Value: {value}")
