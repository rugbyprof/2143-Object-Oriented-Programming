## Assignment 2 - 1 Way Communication (you to me)
#### Due: 08-27-2020 (Wednesday @ 9:30 a.m.)

The 1 way communication is you communicating with me and others with the descriptions and instructions you push to your Github repo. This file provides the instructions that will help you format each assignments README file so they are consistent and informative. I discuss README's below.  Remember this file as a reference for turning in all of your assignments.

## Github

<img src="http://cs.mwsu.edu/~griffin/zcloud/zcloud-files/Github.svg" width="150">

If you have had me before, and this seems **TL;DR** make sure you:

- Scroll past the Git intro and view:
  - Make sure you create your repo correctly with the proper `README.md`
  - Remember how to use [Markdown](https://guides.Github.com/features/mastering-markdown/)
  - Rules for organizing your repo (pretty much the same)
  - README files in general
  - General expectations for all assignments turned in

---

In addition to our team chat and code editor, we will be using `version control` software to organize all of our code. WHAT?!?! **Version Control**?? Please trust me when I say you will be better for using some kind of version control. In this case we will use `git` (the version control software) in conjunction with `Github` a web site that makes your programs publicly viewable. There is a bit of a learning curve, but you will thank me for it.

#### What is Git?

Don't let the following definitions scare you. We will use `git` and `Github` at a very basic (simple) level.

However lets define it:

>`Git` is a distributed revision control and source code management (SCM) system with an emphasis on speed,data integrity,and support for distributed, non-linear workflows. Git was initially designed and developed by Linus Torvalds for Linux kernel development in 2005, and has since become the most widely adopted version control system for software development.<br><br>
As with most other distributed revision control systems, and unlike most client–server systems, every Git working directory is a full-fledged repository with complete history and full version-tracking capabilities, independent of network access or a central server. Like the Linux kernel, Git is free software distributed under the terms of the GNU General Public License  [[1]](http://en.wikipedia.org/wiki/Git_(software)).

So, `Git` is **distributed revision control system** (version control). This is just a fancy way of letting us manage our code. In fact, I really only want to use git so you can `push` our code to a repository that I can access so I can download and run your code. `Github` is such a place.

>`Github` is a social site that allows programmers to share code with other programmers. It's also a great place to discover projects to work on, discover code to use in your own projects, and a great place to start a portfolio. Whereas `Git` is simply the revision control system that can be installed anywhere, and only used locally if that's the users choice.

Remember though: `Git != Github`, Git does version control, but has commands built in to `push` your code to a repository on another computer. This other computer that we will use is `Github`.

#### Why Github for this course?

I use Github as a home-base for all assignments, lectures, and resources. It's basically our courses homepage. That is why I use it. When you push your code to Github, you are placing your code in a central location irregardless of what computer your working on. If you do some work in the lab, you can `push` your changes to Github. If you go home, you can `pull` your changes to your home machine and continue working. If you only work on a single machine, like a laptop, then Github can be your "backup" copy.

#### Create a Github account.

- You shouldn't need this tutorial, but just in case:
   - https://www.wikihow.com/Create-an-Account-on-Github

- When you create a Github account, you must choose a `username`.
- This is very important to remember, because you will update the class roster with this username so I know where to find all your assignments.
- Create a repository named:
    - `2143-OOP-yourlastname` 
    - replace the `yourlastname` with your last name to make it unique.
- Check the box that says: "Add a README.md file"

#### Edit the README.md

- A readme file is a file that gets displayed when you are viewing a folder on Github. So we place a README.md in the repo's folder so we can display information about the repo. Likewise, any README.md in a folder is used to display information about the folder it is in.
- Edit the readme file on Github and place your contact information inside along with a picture of YOU. NOT an avatar. NOT a thumbnail. But an easily identifiable picture of you.
- Your readme should include:
    - Your first and last name
    - Your email address
    - Your website (if you have one)
    - Your image
    - Slack / Github avatar


## Example README.md

If you're not familiar with `markdown` you can go [here](https://guides.Github.com/features/mastering-markdown/) to get an idea of what it can do for you. It's basically a simple syntax that you can use to format files. Use the template below to get your `README` started:

```md
## Albert Einstein
#### Repo: 5443 OOP
#### Email: albert.einstein@yahoo.com
#### Website: https://en.wikipedia.org/wiki/Albert_Einstein
#### Image:
![Albert Einstein](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/einstein.png)
#### Avatar:
![Avatar](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/einstein_avatar.png)
```

***will result in*** (avatar not included in example)

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/einstein_out.png" width="300">

## Organizing Your Repo

- Create an `Assignments` folder inside your Github repository
- In the `Assignments` folder, create a `README.md` file that has the following in it:

```md
##  Assignments Folder

|   #   | Folder Link | Assignment Description |
| :---: | ----------- | ---------------------- |
|       |             |                        |
```

- This will be a table in the root of your folder that will eventually hold a link to each assignment uploaded to Github.
- Your table will initially look very sad and empty like below:


<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/assignments_table_1_4443_2020.png" width="300">

---

But then it will improve as you add rows to the table which link to each project:


<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/assignments_table_2_4443_2020.png" width="300">

---

- Eventually you will create a directory structure that should look structurally similar to the example below (names will be different).
- But this is the structure that I expect your `Assignments` folder to follow. Any files outside of the `Assignments` folder are not any of my concern and you can organize as you see fit.

### Example Repo Directory Structure
```
.
└── 2143-OOP-YourName               (main repo folder)
    ├── Assignments                 (assignments folder)
    │   ├── A01                     (single assignment folder)
    │   │   ├── README.md           (assignment readme)
    │   │   ├── code_file_1.cpp     (assignment files)
    │   │   ├── code_file_2.cpp
    │   │   └── code_file_x.hpp
    │   ├── A02
    │   │   ├── README.md
    │   │   ├── code_file_1.cpp
    │   │   ├── code_file_2.h
    │   │   └── code_file_x.cpp
    │   ├── AXX
    │   │   ├── README.md
    │   │   ├── code_file_1.cpp
    │   │   ├── code_file_2.hpp
    │   │   └── code_file_x.cpp
    │   ├── P01
    │   │   ├── README.md
    │   │   ├── code_file_1.cpp
    │   │   ├── code_file_2.cpp
    │   │   └── code_file_x.cpp
    │   ├── P02
    │   │   ├── README.md
    │   │   ├── code_file_1.cpp
    │   │   ├── code_file_2.cpp
    │   │   └── code_file_x.cpp
    │   ├── PXX
    │   │   ├── README.md
    │   │   ├── code_file_1.cpp
    │   │   ├── code_file_2.cpp
    │   │   └── code_file_x.cpp
    |   └── README.md               (this is the assignments folder readme)
    └── README.md                   (this is your main repo readme)



```

## README's In General

Every single folder on your repo should contain a `README.md`. This is because when I or someone else looks at your repo, and clicks on a folder, they will see not just a directory listing, but an explanation and description of what that folder contains. I'm not making you create README's to be an ass ... I promise. It simply adds credibility to your repo, and makes you look like you know what your doing (and care and visitors to your site). I understand that a lot (if not most) probably don't want anyone looking at your repo, but you should still put your best foot forward. When I browse repos on Github, I not only rely on the README files for information, but find myself judging the software or library based on how organized and descriptive the README's are. And after talking to other developers, I found that I'm not the only one.

## README's For Assignments

More [HERE](../../Resources/02-Readmees/README.md)

We will use the README's that you will create in every assignment folder to do the following:

- Top of the README:
  - Project Title
  - Your name
  - Project Description (It needs to be "descriptive". You can take text straight from the assignment / requirements with a little additions here and there.)
- After description:
  - List all the files and or folders in that current project in a tabular format with a small description of each file.
  - The filename in that table should link to the actual code file or folder.
- After table:
  - Instructions
    - Any and all information needed to run your code.
    - These instructions will be used for others in the class to run your project on their machine. I PROMISE: you will learn very fast how not to assume things just work. Because they DON'T. When your code doesn't run on anyone else's system and you get a zero, I bet you start to let "assumptions" go out the window.

### Common Errors

- Common Errors / Reasons for projects not to run (we can grow a similar list as the class goes on to help everyone get past common pitfalls):
  - Local libraries that you installed and not everyone else did the same.
  - Accessing files or fonts using local paths that will not be the same on running on someone else's machine (this one is annoying).
    - Example:
      - Your path: `C:\my_documents\pythonProjects\PyCharm\P01\Helvetica.ttf`
      - My Path: `/User/griffin/Projects/P01/Helvetica.ttf`
      - We both have P01 folders looking for `Helvetica.ttf`, but the whole path is different. We will also discuss this in class (relative vs absolute paths).
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
|   1   | Main.cpp         | Main driver of my project that launches game.      |
|   2   | HelperClass.cpp  | Helper class that holds movement functions         |
|   3   | TextureClass.cpp | Helper class that assists with textures and images |

### Instructions

- Make sure you install library `blahblah.cpp`
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
    - `python main.cpp input.txt 3`

```

The above markdown will produce a README that looks like:

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/assignmet_readme_example_2020.png" width="600">


