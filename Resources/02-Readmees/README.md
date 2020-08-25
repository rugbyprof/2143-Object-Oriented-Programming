## README - How You Should Format Them
#### Due: None

Every single folder on your repo should contain a `README.md`. This is because when I or someone else looks at your repo, and clicks on a folder, they will see not just a directory listing, but an explanation and description of what that folder contains. I'm not making you create README's to be an ass ... I promise. It simply adds credibility to your repo, and makes you look like you know what your doing (and care and visitors to your site). I understand that a lot (if not most) probably don't want anyone looking at your repo, but you should still put your best foot forward. When I browse repos on Github, I not only rely on the README files for information, but find myself judging the software or library based on how organized and descriptive the README's are. And after talking to other developers, I found that I'm not the only one.

## README's For Assignments

We will use the README's that you will create in every assignment folder to do the following:

- Top of the README:
  - Project Title
  - Your name
  - Project Description (It needs to be "descriptive". You can take text straight from the assignment / requirements. I don't care.)
- After description:
  - List all the files and or folders in that current project in a tabular format with a small description of each file.
  - The filename in that table should link to the actual code file or folder.
- After table:
  - Instructions
    - Any and all information needed to run your code.
    - These instructions will be used for others in the class to run your project on their machine. I PROMISE: you will learn very fast how not to assume things just work. Because they DON'T. When your code doesn't run on anyone elses system and you get a zero, I bet you start to let "assumptions" go out the window.

### Common Errors

- Common Errors / Reasons for projects not to run (we can grow a similar list as the class goes on to help everyone get past common pitfalls):
  - Local libraries that you installed and not everyone else did the same.
  - Accessing files or fonts using local paths that will not be the same on someone elses machine (this one is annoying).
    - Example:
      - Your path: `C:\my_documents\pythonProjects\PyCharm\P01\Helvetica.ttf`
      - My Path: `/User/griffin/Projects/P01/Helvetica.ttf`
      - We both have P01 folders looking for `Helvetica.ttf`, but the whole path is different. We will also discuss this in class.
  - Hard-coding names of external resources that you do not provide:
    - Example: You called your data file **"data.txt"** and use: `open("data.txt")` I called my file **"data.dat"** and now your program crashes.
    - Solution: Read in the filename when the user runs your program, so you get the proper local name ( I will discuss in class argv or command line params)


## Example Assignment README

```
## P02 - Bouncy Balls
### Sally Smith
### Description:

Bacon ipsum dolor amet pork loin kielbasa pork, drumstick leberkas shankle strip steak fatback beef ribs ham hock.
Pork short ribs doner andouille cupim pastrami picanha landjaeger pig. Salami swine capicola spare ribs boudin
leberkas. Capicola ground round pork meatloaf, ham jowl swine prosciutto bacon alcatra pancetta burgdoggen pig
spare ribs leberkas. Shankle fatback ground round, porchetta frankfurter cupim venison strip steak pig meatball
biltong filet mignon. Shoulder chislic ground round pork burgdoggen hamburger.

### Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | Main.py         | Main driver of my project that launches game.      |
|   2   | HelperClass.py  | Helper class that holds movement functions         |
|   3   | TextureClass.py | Helper class that assists with textures and images |

### Instructions

- Make sure you install library `blahblah.py`
- My program expects two parameters to be placed on the command line when you run the program.
- Parameters `<input file> <number of players>`
- The input file should be formatted with a players name and age on a seperate line:

+------------+
| name1 age1 |
| name2 age2 |
| etc...     |
+------------+

- Example Command:
    - `python <code> <input file> <num players>`
    - `python main.py input.txt 3`

```

The above markdown will produce a README that looks like:

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/assignmet_readme_example_2020.png" width="600">
