from rich.progress import Progress, BarColumn

progress = Progress(BarColumn(), "{task.completed}/{task.total}")

task = progress.add_task("Task", total=100, completed=1.0)

for i in range(101):
    progress.update(task, completed=i)