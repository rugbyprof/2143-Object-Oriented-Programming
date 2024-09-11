## WSL - Getting it Installed & Set Up

#### Due: 09-16-2024 (Monday the 16<sup>th</sup>)

### Overview

This assignment was insterted into the queue of assignments and bubbled up to be before program 01 because of its necessary for this and future programs (and the future of our planet and all life on earth). Your ability to use the shell cannot be underestimated. I'm not saying that understanding shell commands and running programs using the shell will save your life, or make you rich, but I'm pretty sure that everyone who started mining bit coin didn't use some "Mining Bitcoin for Beginners Gui". Just sayin...

<img src="https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExY3FrYjkyeTZ0d3gybGh6MGE1OTF1M2JxZGwwbmR1Mmk3Mm10b3B2cCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/vrJbsF0hf9bWMjOUvc/giphy.webp">

### Getting Started

Here are a list of tutorials that are all made by MicroSoft. So I am hoping that they are accurate and well written. My perusal of each site allowed me to glean facts supporting my hopes. Basically, they don't suck, and in fact they are pretty easy to follow and give good information. You don't have to read every word of every site listed below, but you should browse them enough so that you don't end up trying again and again because you kept missing some key step. I'll try and discuss a lot of this stuff during todays lecture.

|  #  | Link                                                                                     | Description                                           |
| :-: | :--------------------------------------------------------------------------------------- | :---------------------------------------------------- |
| 1.  | [Basic Install](https://learn.microsoft.com/en-us/windows/wsl/install)                   | Enabling & Installing WSL (almost the same as 2)      |
| 2.  | [Better Install](https://learn.microsoft.com/en-us/windows/wsl/setup/environment)        | You could start here and skip 1                       |
| 3.  | [WSL with VsCode](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-vscode)    | Using WSL with VsCode                                 |
| 4.  | [C++ with WSL & VsCode](https://code.visualstudio.com/docs/cpp/config-wsl)               | Compiling and Running c++ code with WSL and VsCode    |
| 5.  | [Git with WSL & VsCode](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git) | Conveniently add & upload files to github with VsCode |
| 6.  | [Linux Commands](https://learn.microsoft.com/en-us/windows/wsl/tutorials/linux)          | Shell command starter tutorial                        |

### Getting Assessed

I need to know that you are actually using WSL (or a bash shell that you will have consistent access to). Basically if you have linux installed on your own machine, or you use a MacBook, then WSL is not necessary. However, I still need to know that you have access to a shell to run your programs from. That's what the following mini sections is about. I will need you to choose two of the following to turn in showing me you have access to a bash shell (not gitbash, not powershell, replit can work, linux install would work, osx works). If you are looking at my explicit use of `bash` and are wondering if you can use another shell ... 1) You probably are pretty experienced using shell commands already so use whatever, 2) If your curious, look [HERE](./shells.md) to see a list of 10 shell languages.

I digress ... I need a way for you to show me that you've got WSL installed and you can use it. And if you happen to be a more advanced user, than this is kind of a moot point.

## Ways To Confirm

> **Note 1:** in the code blocks that show you commands to run, there is a dollar sign (`$`) on the far left showing that "this is a command to run from the command line". It's whats known as a "prompt", and the dollar sign is the generic prompt shown in most examples. So, don't run any of the commands with the dollar sign, because they won't run correct!

> **Note 2:** You are going to create a document, and place screen shots of your 1 or more commands that show the output of that command. Your screen shot should only grab the area thats necessary to get the point across.

> **Note 3:** Out of all the the items listed below, you only have to do 1 or 2 so show me that everything is installed or running, not ALL OF THEM. For example, look at the screen shot below. I grabbed enough screen to show the output of my command, and in Vscode on the left, you can see which terminal your running on the right.

|                              Screen Shot                              |
| :-------------------------------------------------------------------: |
| <img width=600 src="https://images2.imgbox.com/34/25/w94caqO6_o.png"> |

### 1. You can check `WSL` status from the command line:

- You would run the following command:

```bash
$ wsl -l -v
```

- This command shows that there is a linux distro (short for distribution) installed as a virtual machine on your windows computer.

```
  NAME                   STATE           VERSION
* Ubuntu                 Running         2
  Debian                 Stopped         1
```

Screen shot the output of the command. Your screenshot will be put into your assignment doc to turn in.

### 2. **Checking the WSL Distro**

After checking that we have a Linux distribution (e.g., Ubuntu) installed, we can run another command to show the details of that distro.

- Run the following command to verify the details of your distro:

```bash
$ lsb_release -a
```

Your output should resemble:

```bash
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 20.04.2 LTS
Release:        20.04
Codename:       focal
```

This shows that you are using a valid Linux environment within WSL. Again, take a screenshot of the output and place it into your assignment document.

### 3. **WSL Configuration File**

You can check for the presence of a WSL configuration file or view logs to demonstrate that WSL is running.

- Run the following command to verify the details of your distro:

```bash
$ ls -l /etc/wsl* && cat /etc/wsl.conf
```

- **`/etc/wsl.conf`**: This file controls WSL settings for more advanced usage. It's not required for basic WSL operation, but it’s a file that you can show as proof that you are interacting with the WSL environment.

### 4. **Using Bash in VSCode**

Set the integrated terminal to bash (WSL). You can make this happen by:

- Go to **View > Terminal** in VSCode.
- Click the dropdown beside the terminal and select **bash** (Ubuntu on WSL should be listed).

Take a screenshot of the terminal showing the bash prompt and place that in your document.

### 5. **Running a Simple Bash Command or Script**

Here's a simple bash script that checks if a user is running bash within a **WSL (Windows Subsystem for Linux)** environment:

```bash
#!/bin/bash

# Check if running in WSL
if grep -qi Microsoft /proc/version; then
    echo "You are using bash in a WSL environment."
else
    echo "This is not a WSL environment."
fi
```

### Explanation:

- **`/proc/version`**: This file contains information about the Linux kernel. In WSL environments, it typically includes the word "Microsoft" because WSL is developed by Microsoft.
- **`grep -qi Microsoft /proc/version`**: This command looks for the string "Microsoft" in `/proc/version` in a case-insensitive manner (`-i` flag). If found, it means the script is running inside WSL.

### How to Use:

1. Save the script as `check_wsl.sh`.
2. Make it executable:
   ```bash
   chmod +x check_wsl.sh
   ```
3. Run the script:
   ```bash
   ./check_wsl.sh
   ```

This script will print a message confirming whether you are running bash in a WSL environment or not.

### 6. Finally

Python can determine whether a WSL bash instance is running. You can do this by inspecting the content of the **`/proc/version`** file, similar to how it's done in bash.

Here's a Python script that checks if it’s running in a WSL environment:

```python
import platform
import os

def is_wsl():
    # Check if running in WSL
    if "microsoft" in platform.uname().release.lower():
        return True
    # Check the /proc/version file for WSL-specific mentions
    try:
        with open("/proc/version", "r") as f:
            version_info = f.read().lower()
            if "microsoft" in version_info:
                return True
    except FileNotFoundError:
        return False
    return False

def is_bash():
    # Check if the shell is bash
    return os.getenv('SHELL', '').endswith('bash')

if __name__ == "__main__":
    if is_wsl() and is_bash():
        print("You are using bash in a WSL environment.")
    elif is_wsl():
        print("You are in a WSL environment, but not using bash.")
    else:
        print("This is not a WSL environment.")
```

### Explanation:

- **`platform.uname().release`**: This checks the system’s release information for the word "microsoft", which is typically present in WSL environments.
- **`/proc/version`**: This file contains details about the Linux kernel, and for WSL environments, it usually contains the word "Microsoft".
- **`os.getenv('SHELL')`**: Checks the current shell environment variable to determine if the user is running bash.

### How to Use:

1. Save the Python script as `check_wsl.py`.
2. Run it using Python:
   ```bash
   python3 check_wsl.py
   ```

If you are running **bash** in **WSL**, the script will print:

```
You are using bash in a WSL environment.
```
