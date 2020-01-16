# Program 1 - AsciiShop
Due on github by ***Thursday March 3<sup>rd</sup>*** by class time. 

### Requirements
- Working by yourself, or with a partner, create a class called `asciiShop` that will add additional functionality to the existing `asciiArtClass.py` we did in class. 
- Create a folder called `AsciiShop` for all your files.
- Rename `asciiArtClass.py` to  `asciiShop.py`.
- Additional methods to add:

```python
"""
@Name: flip
@Description:
    This method will flip an image horizontally, or vertically. 
    Vertically means all pixels in row 0 => row N, row 1 => row N-1, ... row N/2 => row N/2+1
    Horizontally means all pixels in col 0 => col N, col 1 => col N-1, ... col N/2 => col N/2+1
@Params: direction (string) - [horizontal,vertical] The direction to flip the cat.
@Returns: (string) - Flipped ascii image.

@Name: invert 
@Description:
    This method will take all the lightest pixels and make them the darkest, next lightest => next darkest, etc..
@Params: None
@Returns: (string) - Inverted ascii image.
"""
```


EXTRA CREDIT (Pick One):

```python
"""
@Name: crop
@Description:
    This will crop an image from a starting x,y coordinate to an ending x,y coordinate. For example:
    crop((col,row),(col,row))
    crop((1,1),(8,4)) (all the zeros are cropped from the image)
    **********          0000000000
    **********          0*******00
    **********   =>     0*******00    
    **********          0*******00
    **********          0*******00
@Params: 
  start (tuple) - (x,y)
  end (tuple) - (x,y)
@Returns: (string) - Cropped ascii image.
"""
```
OR:

```python
"""
@Name: resize 
@Description:
    This method will resize the already converted ascii image. The problem with this is you can't just chop off pixels (thats cropping), 
    or you can't just add pixels on the edges, that wouldn't look right either (you would end up with a border). The most straight 
    forward approach to "resizing" is this:
    
Shrinking-
  Average groups of pixels (4x4 group => 1x1):
  11223344      
  11223344  =>  1234
  55667788      5678
  55667788      

Enlarging- 
  Expand in the opposite fashion. 
  (1x1 pixel => 4x4 group)
@Params: 
    factor (int) - A factor to enlarge or shrink by
    action (string) - [enlarge,shrink] - Which way to apply the factor.
@Example:
    resize(2,'shrink') would shrink the ascii image by a factor of 2 (or half)
    resize(2,'enlarge') would double the size of the ascii image.
@Returns: (string) - Inverted ascii image.
"""
```

- You should also make it so a user can pass in an image name to the class. 
- If an image name is passed in then there is no need to download a new one.
- This will help speed up testing.

## Starter Code:
Code can be found [here](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/blob/master/AsciiCat/asciiArtClass.py).

### Deliverables

- Upload everything to gitHub this means the folder and all it's contents named correctly.
- The file should execute with no errors.
- If you worked with a partner, both people should have the code in thier repo.
- Your name (or both names) should be in all documents.
- When I run your program, it should print out two small ascii images. The first is a small cat image converted to ascii, and the second is the same image inverted.
- Comment, Comment, Comment (Correctly) .... 

