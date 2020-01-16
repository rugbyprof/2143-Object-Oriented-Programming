| Command	      | Meaning                                       |
|---------------|------------------------------------------------|
| `ls	`          | list files and directories                    |
| `ls -l`	        | do a long listing showing permissions and file sizes |
| `ls -la`	        | same as above + show hidden files and directories    |
| `ls -lah`	        | same as above + make file sizes human readable |
| `ls -a`	        | list all files and directories                |
| `mkdir dirname`	| make a directory called `dirname`              |
| `cd directory`	| change to  `directory`                    |
| `cd`	          | change to home-directory                      |
| `cd ~	`        | change to home-directory                      |
| `cd ..`	        | change to parent directory                    | 
| `pwd`	          | display the path of the current directory     |


| Command               | Meaning                                  |
|-----------------------|------------------------------------------|
| `cp file1 file2`      |  make a copy file1 and call it file2 |
| `cp ..\..\fileA .`    | copy `fileA` from two directories back to `here` |
| `mv file1 file2`      | move or rename file1 to file2 |
| `mv file1 ..`         | move `file1` back one directory |
| `rm file`             | remove a file |
| `rmdir directory`     | remove a directory |
| `rm -rf directory`    | remove a directory (typical way)|
| `cat file`            | display a file |
| `less file`           | display a file a page at a time |
| `head file`           | display the first few lines of a file |
| `tail file`           | display the last few lines of a file |
| `grep 'keyword' file` | search a file for keywords |
| `wc file`             | count number of lines/words/characters in file |
| `chmod xxx filename`  | change modify permission  on filename | 
| `chmod +x filename`  | add `execute` to file name |


| Command                    | Meaning |
|----------------------------|---------|
| `command > file`           | redirect standard output to a file |
| `command >> file`          | append standard output to a file |
| `command < file`           | redirect standard input from a file |
| `command1 | command2`      | pipe the output of command1 to the input of command2 |
| `cat file1 file2 > file0`  | concatenate file1 and file2 to file0 |
| `sort`                     | sort data |
| `who`                      | list users currently logged in |

| Command            | Meaning |
|---------------------|---------|
| `history`           | show a history of all your commands |
| `!x`                | this loads command `x` from your history so you can run it again |