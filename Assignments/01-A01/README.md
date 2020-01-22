## Assignment 1 - Getting Started
#### Due: 01-23-2020 (Thursday @ 11:00 a.m.)

## Getting Setup

All of these are important! So do them with expedience.

If you have had me before, and this seems **TL;DR** make sure you:

1. Are on my slack channel: https://griffin-courses.slack.com
2. Create your repo for this class
3. Add yourself to the class roster
4. Make sure your image is on your github repo and changed in your slack profile.

### Team Chat

---

<img src="http://cs.mwsu.edu/~griffin/zcloud/zcloud-files/slack_icon.png" width="175">


The first step in doing well in any of my courses is establishing a base of communication. Why? Not everything can be done while we are in class. 

Assignments will (and should) be challenging. Therefore, you will need help from me and your classmates. Using [Slack](https://slack.com)<sup>2</sup> (a chat client) provides a communication portal after class and regardless of where you are. I realize that most work gets done in the evening and off campus. By using Slack,you don't have to wait until the lab is open, or until I have office hours.

You can ask questions multiple ways on Slack. Either on our public class channel, or privately between users. If you post a question on the public channel, your fellow students can help with an answer. This is good, because most questions revolve around interpretation of an assignment: "What did Griffin mean when he asked __________?" These questions help everyone interpret an assignment correctly, and I can jump in to give a definitive answer. You can also privately ask me a question on a direct channel. I will do my best to answer in an expedient amount of time. Some days I may answer immediately, and some days I may not answer at all. I try my best, but I will also not be a slave to slack :) I mostly will answer quickly, even late at night.

You should have gotten an invite already from me. Accept it. If you didn't, ask me for another invite. [Here](https://get.slack.help/hc/en-us/articles/218080037-Getting-started-for-new-users) is a getting started guide to help you use slack. Slack is an app. It can be installed OR viewed via a web browser using a URL. 

#### Slack provides

- Team chat (class members and myself).
- Code highlighting for snippets so we can share code and read it better.
- File sharing simply by dragging and dropping.
- Private channels so you can discuss things without everyone seeing (even I can't see).
- Polls so we can vote on things (mainly for me).

So, **NO email!** Unless I specifically ask. Slack is your communication conduit for this class.

#### Slack Recommendation

1. I **highly** recommend installing slack on your mobile device as well as your own computer. I often upload help, or code suggestions on Slack in the evening or on weekends. Having slack on your mobile device will give you the best chance of getting the `alert` or notification that something was done.
2. **The students that monitor our slack channel and participate in discussions almost alway do better. I've used slack since it was established almost 10 years ago and I can say with a high level of confidence that students who participate on Slack to better in the course.**
3. **YOU WILL** update your profile so your avatar in chats shows either an image of you, or an avatar that ends up on your github repo's main page.

Now that we have our communication client set up, we probably need to start getting the actual programming environment ready! We will be doing many things from the command line this semester. Windows is not known for it's command line prowess, so we need to give it some assistance. 

### VsCode (NOT Visual Studio)
---

<img src="http://cs.mwsu.edu/~griffin/zcloud/zcloud-files/vscode.svg.png" width="175">

Vscode is a lightweight editor that will also let us compile and run C++ programs. I like it much more than Visual Studio because we do not need all of what Visual Studio offers. VsCode is a more straight forward way to running C++ programs, and I think you will benefit from using it. VsCode is NOT a compiler. What does this mean? When you use Visual Studio you are using an IDE (Integrated Development Environment). The `integrated` means that many components are "integrated" within the "environment": editor, compiler, linker, library managament, debugger, team support, version control and much more. It's the kitchen sink of writing programs, but we really only need an editor and compiler (with a couple of helper tools).  Vscode has debug capabilities which I will touch on during the semester.

To instal VsCode, go here:
- https://code.visualstudio.com/

To add C++ support go here (don't worry about `Remote Development`)
- https://code.visualstudio.com/docs/languages/cpp

### Your Own Code Repository

---

<img src="http://cs.mwsu.edu/~griffin/zcloud/zcloud-files/github.svg" width="175">

In addition to our team chat and code editor, we will be using `version control` software to organize all of our code. WHAT?!?! **Version Control**?? Please trust me when I say you will be better for using some kind of version control. In this case we will use `git` (the version control sofwtare) in conjunction with `github` a web site that makes your programs publicly viewable. There is a bit of a learning curve, but you will thank me for it. 

#### What is Git?

Don't let the following definitions scare you. We will use `git` and `github` at a very basic (simple) level. 

However lets define it: 

>`Git` is a distributed revision control and source code management (SCM) system with an emphasis on speed,data integrity,and support for distributed, non-linear workflows. Git was initially designed and developed by Linus Torvalds for Linux kernel development in 2005, and has since become the most widely adopted version control system for software development.<br><br>
As with most other distributed revision control systems, and unlike most client–server systems, every Git working directory is a full-fledged repository with complete history and full version-tracking capabilities, independent of network access or a central server. Like the Linux kernel, Git is free software distributed under the terms of the GNU General Public License  [[1]](http://en.wikipedia.org/wiki/Git_(software)).

So, `Git` is **distributed revision control system** (version control). This is just a fancy way of letting us manage our code. In fact, I really only want to use git so you can `push` our code to a repository that I can access so I can download and run your code. `Github` is such a place. 

>`Github` is a social site that allows programmers to share code with other programmers. It's also a great place to discover projects to work on, discover code to use in your own projects, and a great place to start a portfolio. Whereas `Git` is simply the revision control system that can be installed anywhere, and only used locally if that's the users choice. 

Remember though: `Git != Github`, Git does version control, but has commands built in to `push` your code to a repository on another computer. This other computer that we will use is `Github`. 

#### Why github for this course?

I use github as a homebase for all assignments, lectures, and resources. It's basically our courses homepage. That is why I use it. When you push your code to github, you are placing your code in a central location irregardless of what computer your working on. If you do some work in the lab, you can `push` your changes to github. If you go home, you can `pull` your changes to your home machine and continue working. If you only work on a single machine, like a laptop, then github can be your "backup" copy. 

#### Create a Github account.

- You won't need this tutorial, but just in case:
   - https://www.wikihow.com/Create-an-Account-on-GitHub

- When you create a Github account, you must choose a `username`.
- This is very important to remember, because you will update the class roster with this username so I know where to find all your assignments.
- Create a repository named:
    - `2143-OOP-yourlastname`
    - replace the `yourlastname` with your last name to make it unique.
- Check the box that says: "Add a README.md file"

#### Edit the README.md 

- Edit the readme file on github and place your contact information inside along with a picture of YOU. NOT an avatar. NOT a thumbnail. But an easily identifiable picture of you.
- Your readme should include:
    - Your first and last name
    - Your email address
    - Your website (if you have one)
    - Your image
    - Slack / Github avatar

***Example README.md***

If you're not familiar with `markdown` you can go [here](https://guides.github.com/features/mastering-markdown/) to get an idea of what it can do for you. It's basically a simple syntax that you can use to format files. Use the template below to get your `README` started:

```md
## Albert Einstein
#### Repo: 2143 Object Oriented Repo
#### Email: albert.einstein@yahoo.com
#### Website: https://en.wikipedia.org/wiki/Albert_Einstein
#### Image:
![Albert Einstein](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/einstein.png)
#### Avatar:
![Avatar](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/einstein_avatar.png)
```

***will result in*** (avatar not included in example)

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/einstein_out.png" width="300">

### Assignments Folder

- Create an `Assignments` folder inside your github repository
- In the `Assignments` folder, create a `README.md` file that has the following in it:

```md
## Assignments

| Number | Folder | Description |
| :----: | ------ | ----------- |
|        |        |             |
```

- This will be a table in the root of your folder that will eventually hold a link to each assignment uploaded to github.

### Class Roster
---

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/google-sheets.png" width="150"> 

#### Update the Class Roster:

- Here is a link to our class roster on google docs: ![](https://d3vv6lp55qjaqc.cloudfront.net/items/220B0V0H3c041K2p251Z/google-sheets-16.png?X-CloudApp-Visitor-Id=1094421) [Class Roster](https://docs.google.com/spreadsheets/d/18bmuAJBjV5Yw5tzzXht_Dz1gcwoYvydZgtCaR_nECOw/edit?usp=sharing)

- Update the roster by adding your information to it. 

Add:

1. If your first and last name are not present, add them along with an email address.
2. If your email on my roster is incorrect, or you use a different one, then change it.
3. Add your github username<sup>*</sup>
4. Add a link to your 2143-OOP repository<sup>*</sup>

*Your repository name and your github username are NOT the same thing.
*I should be able to click your repo link, and your github repository (along with your README file ... images and all ... should proudly be displayed).

### Rules for emailing me:
---

1) Open your email client.
2) Create a new email.
3) Put an appropriate subject in the email subject box.
4) Type a clear message that contains:
    - first name, 
    - last name,
    - course number
    - Link to any assignment that your asking about
5) Now ***CLOSE YOUR EMAIL CLIENT AND MESSAGE ME ON SLACK***.

Sources:
- <sub>[1] http://en.wikipedia.org/wiki/Git_(software)</sub>
- <sub>[2] https://slack.com</sub>
- <sub>[4] https://code.visualstudio.com/</sub>
- <sub>[5] https://git-for-windows.github.io/</sub>