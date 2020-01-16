# Program 2
***Due: 28 Mar by Classtime***

### Overview

- ***Use Python 2 for this assignment.***
- Given the [grid.py](./grid.py) file in this directory, turn this "module style" collection of functions into a class called ***Grid***.
- There are many "global" variables defined in the file, we will discuss the use of globals in this file in class so you can determine which should stay "global" and which should become class members.   
- Additionally, Their is a  "color_wheel" provided by this module and it has 18 unique colors. We are going to increase this by a lot.
- HTML has a ton of "named" colors. Here is a file: [colors.json](./colors.json) that has 148 of them. 
- Using more colors isn't always the better choice, but I think the 18 provided by the original file could be increased significantly.
- To read the exisiting [colors.json](./colors.json) file in, use the following snippet:
```
with open("colors.json") as file: 
   colors = file.read()

colors = json.loads(colors)

for color in colors:
    print(color)
```

- This will print out:

```
...
{u'rgb': [46, 139, 87], u'html': u'#2e8b57', u'name': u'seagreen'}
{u'rgb': [255, 250, 250], u'html': u'#fffafa', u'name': u'snow'}
{u'rgb': [0, 0, 205], u'html': u'#0000cd', u'name': u'mediumblue'}
{u'rgb': [25, 25, 112], u'html': u'#191970', u'name': u'midnightblue'}
{u'rgb': [175, 238, 238], u'html': u'#afeeee', u'name': u'paleturquoise'}
{u'rgb': [238, 232, 170], u'html': u'#eee8aa', u'name': u'palegoldenrod'}
...
```

- Use the information provided from the `json` file to add to the "color wheel" of your class.

## Deliverables
- Create a folder called ***`program-2`*** in your Assignments folder. If I haven't asked you to create an `Assignments` folder, do so and copy all assignments into this folder.
- Your new class definition will remain in `grid.py` within the ***`program-2`*** folder.
- Running your `grid.py`:
   - The new `if__name__=='__main__'` testing block should do the following:
       - Ask the user for how many colors (or use argv)
           - (argv example: `python grid.py 9`)
       - Check the input number to ensure it can be displayed in a square grid. For example:
           - 9 = ***`3 x 3`*** (rows,cols)
           - 16 = ***`4 x 4`*** (rows,cols)
           - 25 = ***`5 x 5`*** (rows,cols)
           - 7 = Not So Much
           - 23 = Not So Much
       - After we OK the number of colors ***N***, create a grid that is ***N x N***. 
       - We want to display each color in its own mini grid.
       - For example: a ***9 x 9*** grid, each color will be in a mini ***3 x 3*** grid:
    
    ![](https://d3vv6lp55qjaqc.cloudfront.net/items/3x0n3t300n1V1C0X2b3u/table9x9_colors.png?X-CloudApp-Visitor-Id=1094421)
