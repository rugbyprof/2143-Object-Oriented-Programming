## Assignment 1 - Setting up Develepment Environment
#### Due: Friday January 20th by 5:00pm

## ADE - Academic Development Environment

Typically a `development environment` is:
>A set of processes and programming tools used to create the program or software product. 

This usually consists of a local code editor, with the libraries / frameworks downloaded and installed for your particular type of coding. In addition a local server to run code on might be necessary. What is absolutely necessary is the initial code base that your going to be working with. This is usually kept in some type of repository managed with Git or Subversion (version control software).
Ultimately you will NOT work until your environment is set up! For us in class it's similar and no less important!  

### Intructors Note:
>As you read below (and no TL;DR excuses) it will seem like overkill for this level of programming. Some of the terminology and software components will be confusing, but only at first. After your initial setup (all of the components below are installed), there will be a repetative series of steps used to write, edit, and save (commit) your code. It will be so repetative that it will become second nature. I guarantee that you will learn to appreciate and probably start to prefer the power of the command line and gaining more control over your dev environment.
>
>This is an important step to getting your semester off on the right foot. **It's so important that:**
>- If you don't complete it, drop the course because you will fail.
>- If you complete it late, you will lose 1 letter grade off of your final grade.
>- If you complete it wrong, you will lose 1/2 of one letter grade off of your final grade.
>- Having said that, feel free to get help from me at anytime.
>- And no I will not penalize you if there are configuration problems or other issues that present themselves after each thing is installed. I only want you to get this done as soon as possible, so don't wait.
>


### Step 1: Team Chat
---

![](https://d17oy1vhnax1f7.cloudfront.net/items/1J3A0f36402p2r1K1u0L/slack-2014.hG65.png)

The first step in doing well in any of my courses is establishing a base of communication. Why? Not everything can be done while we are in class. 

Otherwise: 

1. I would lecture
2. give an assignment
3. you would complete said assignment
4. then you would go home
5. communication not necessary

That's so highschool. Assignments will (and should) be challenging. Therefore you will need help from me and your classmates. Since the labs are only open 9-5 with limited help, we need to alleviate that problem. So we will use a chat client built for developers called [Slack](https://slack.com)<sup>2</sup>. You should have gotten an invite already from me. Accept it. If you didn't, ask me for another invite. [Here](https://get.slack.help/hc/en-us/articles/218080037-Getting-started-for-new-users) is a getting started guide to help you use slack. 

#### Slack provides:

- Team chat (class members and myself).
- Code highlighting for snippets so we can share code and read it better.
- File sharing simply by dragging and dropping.
- Private channels so you can discuss things without everyone seeing (even I can't see).
- Polls so we can vote on things (mainly for me).

So, **NO email!** Unless I specifically ask. Slack is your communication conduit for this class.


Now that we have our communication client set up, we probably need to start getting the actual programming environment ready! We will be doing many things from the command line this semester. Windows is not know for it's 
command line prowess, so we need to give it some assistance.


### Step 2: Gitbash
---
![](https://d17oy1vhnax1f7.cloudfront.net/items/160M141x29360Y0f0T0l/gwindows_logo_72.hF1V.png)

From Gitbash's website:

>Git for Windows provides a BASH emulation used to run Git from the command line. *NIX users should feel right at home, as the BASH emulation behaves just like the "git" command in LINUX and UNIX environments.

This tells us two things: 

1. We're getting a command line (`bash`) emulator.
2. We will be using `Git`! ?? 

Don't worry about `Git` just yet. Simply install Git for windows. 

Download Gitbash from [here](https://git-for-windows.github.io/). This page also gives a little more information about what your installing. 


Finally! Lets install Python! If your running Mac Python comes installed. I'm pretty sure it's still Python 2 and we will be using Python 3 in class. Talk to me personally and I can show you how to add Python 3. If your using Windows, continue to next section.

### Step 3: Python
---
![](https://d17oy1vhnax1f7.cloudfront.net/items/2m0b283u1Q3l0m240V1U/python_logo_78.hGQa.png)

#### Installation Procedure:

Python comes installed with Mac OSX and most GNU/Linux systems, but it does not come with Windows. It is free software, however, and installation on Windows is quick and easy (hopefully)<sup>3</sup>.

1. Point your web browswer to the download page on the Python website [here](https://www.python.org/downloads/release/python-352/).
2. Select the latest Windows x86 MSI Installer (python-3.5.2.msi at the time of this writing) and click on the link to download the .msi installer.
3. Run the installer (note: IE 9 will offer you this option when you click on the link).
4. Select Install for all users (the default option) and click the Next > button.
5. Keep the default option (C:\Python32\) as the destination directory and click Next > button again.
6. Don't make any changes in the Customize Python 3.5.2 dialog, just click Next > again.
7. Click Yes if asked if this program should be allowed to install software on your system.
8. Click the Finish button when installation completes.

#### Running Python:

The installation process creates a Python 3.5 section under Start Menu -> All Programs. Click on this to expand it, then click IDLE (Python GUI) to launch the Python Integrated Development program (IDLE).

Now we have communications set up so we can communicate and ask questions, we also have Gitbash installed so we can perform tasks from the command line, and we have Python installed. I guess it's time to write some Python, and so we probably need an editor.

### Step 4: Visual Studio Code 
---

![](https://d17oy1vhnax1f7.cloudfront.net/items/0K2j0e0y0G0h1X2x0p1O/visual-studio-2015-update-1-icon.hFUc.png)

Our next step is to figure out what editor we want to use. This is largely based on the type of development we are going to do. I will say this, we won't be using visual studio professoinal! It's good, but too big for our needs. Were going to use Python as our development language, and even though Visual Studio Professional can run Python, I would like use something a little more light-weight that will still allow us to write code: [Visual Studio Code](https://code.visualstudio.com). 

Download for windows [here](https://go.microsoft.com/fwlink/?LinkID=623230)

This editor allows to install some helpful `extensions` as well. In fact we will need to install a few extensions to help us run code in Python. The first one will let us run python right in Visual Studio, the second one will help with syntax highlighting and autocompletion, and the third one will format our code in a industry standardized way.


- ![](https://d3vv6lp55qjaqc.cloudfront.net/items/0u2t3c1e113304240c3T/code_run.png?X-CloudApp-Visitor-Id=1094421)
- ![](https://d3vv6lp55qjaqc.cloudfront.net/items/3f3x0b0v2s052y0g2D3t/python_lint.png?X-CloudApp-Visitor-Id=1094421)
- ![](https://d3vv6lp55qjaqc.cloudfront.net/items/2S3D2g0X0o1n0D2w321z/pep8.png?X-CloudApp-Visitor-Id=1094421)

So now we are finally at a point where we can write some code, run our code, save our code. So lets do just that.

### Step 5: Revision Control
---

![](https://d17oy1vhnax1f7.cloudfront.net/items/1J3p2j221s2q2q1G100T/elmah.io.apps.github.hGP6.png)


In addition to our team chat, our code editor, and our new terminal environment we need a place where we can store / retreive our code base. A `code base` is a collection of source code that is used to build a particular software system. Where `software system` in the context of class is basically our programs. Github is where you will get all of your starter code (code base) for each of your assignments, and it's also where you will store all of your assignments when completed. 


#### What is Git?

>Git is a distributed revision control and source code management (SCM) system with an emphasis on speed,data integrity,and support for distributed, non-linear workflows. Git was initially designed and developed by Linus Torvalds for Linux kernel development in 2005, and has since become the most widely adopted version control system for software development.<br><br>
As with most other distributed revision control systems, and unlike most client–server systems, every Git working directory is a full-fledged repository with complete history and full version-tracking capabilities, independent of network access or a central server. Like the Linux kernel, Git is free software distributed under the terms of the GNU General Public License  [[1]](http://en.wikipedia.org/wiki/Git_(software)).

`Git != Github`

`Github` is a social site that allows programmers to share code with other programmers. It's also a great place to discover projects to work on, discover code to use in your own projects, and a great place to start a portfolio. Whereas `Git` is simply the revision control system that can be installed anywhere, and only used locally if that's the users choice. 

#### Why github for this course?

We will be using github this semester as a means of communicating, storing documents (assignments and programs), as well as 
a means to push your files to a central repository. So if your using a lab or personal machine, there's a centralized location that we both have access to.

---

#### Create a Github account. 
- When you create a Github account, you must choose a `username`. 
- This is very important to remember, because you will update the class roster with this username so I know where to find all your assignments.
- Create a repository named:
    - `2143-OOP-yourlastname`
    - replace the `yourlastname` with your last name to make it unique.
- Check the box that says: "Add a README.md file"

#### Edit the README.md 

- Edit the readme file on github and place your contact information inside along with a picture of YOU. NOT an avatar. NOT a thumbnail. But an easily identifiable picture of you.
- Your readme should include:
    - Your image
    - Your first and last name
    - Your email address
    - Your website (if you have one)

#### Make me a contributer:

- Go to your repo settings and add `rugbyprof` as a collaborater.
- Go to your repo settings and add `Cdbot100` (Scott Gordon) as a collaborater.
- You can do this in the settings of your repository. 
- This is vital as I need access to your files with edit permissions.

### Step 6: Class Roster
---

![](https://docs.google.com/spreadsheets/d/1GBNKqQUz9HOn7Y7rjm_l9eoPpBnZKxSiwTiIipeTgiQ/edit?usp=sharing)
#### Update the Class Roster:

- Here is a link to our class roster on google docs: https://docs.google.com/spreadsheets/d/1GBNKqQUz9HOn7Y7rjm_l9eoPpBnZKxSiwTiIipeTgiQ/edit?usp=sharing

- Update the roster by adding your information to it. 

Add:

1. Your name (last, first)
2. Your email
3. Your github username<sup>*</sup>
4. A link to your 2143-OOP repository<sup>*</sup>

*Your repository name and your github username are NOT the same thing.

---

#### Rules for emailing me:

Every email must have a minimum of two items included:

- The course number and title in the subject:
    - `2143 OOP`
- Your name

I can't promise an answer if you don't provide those two pieces of information.


Sources:
- <sub>[1] http://en.wikipedia.org/wiki/Git_(software)</sub>
- <sub>[2] https://slack.com</sub>
- <sub>[3] http://www.openbookproject.net/courses/webappdev/units/softwaredesign/resources/install_python_win7.html </sub>
- <sub>[4] https://code.visualstudio.com/</sub>
- <sub>[5] https://git-for-windows.github.io/</sub>
- <sub>[6] https://www.python.org/</sub>
