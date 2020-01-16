## Image Processing Filters
<sup>source: http://www.cs.umb.edu/~jreyes/csit114-fall-2007/project4/filters.html#warhol</sup>


### Links to help you
<sup>Note: You cannot used any built in image processing functions to apply any of the filters below. You must alter each pixel yourself. In other words, loop over all pixels and apply changes programmatically. You can however use PIL to grayscale your image if necessary.</sup>

http://effbot.org/imagingbook/introduction.htm

### Description of Algorithms

Most of the filters described below can be done using [convolution](https://en.wikipedia.org/wiki/Kernel_(image_processing)) which is a technique of traversing over image data and applying special functions to alter pixel values. 

Each example will be using the original image viewed below:

| original image |
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/052f2r2i1G0X391c3v1C/yellow_purple_640.jpg?X-CloudApp-Visitor-Id=1094421)|

### Glass Filter

To create a filter that mimics the effect of viewing the image through antique glass. Here is the general strategy to apply the filter to a particular patch of an image:

```
Choose a DISTANCE value.

For each pixel in the image: 
	Let XPOS = current x-coordinate
	Let YPOS = current y-coordinate

	Randomly select another pixel NEIGHBOR where:  
		x-coordinate is between: XPOS − DISTANCE and XPOS + DISTANCE
		y-coordinate is between: YPOS − DISTANCE and YPOS + DISTANCE

	Set the color of the CURRENT to the color of the NEIGHBOR.
```
Don't forget that dealing with pixels near the border of the image could result in a pixel that is "off" the image itself where:

> (`value < 0 or value > image_size`). 

Pythons `random.choice` function could help with this problem. Here is an example where we don't allow any choices to be below 0:

```python
# assume i is some number between 0 and width of your image.
nums = [x for x in range(i - distance, i + distance) if x >= 0]

choice = random.choice(nums)
```
You could alter the above snippet to ensure that all random choices are ON the current image by changing the `if` statement in the list comprehension.

| Lilies through glass DISTANCE = 5  |
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/3p2N0H1d2Q0U3K0v333j/glass.jpg?X-CloudApp-Visitor-Id=1094421)|

### Vertical Flip

The vertical flip has the same effect viewing the image from mirror placed at the image's bottom (or top, depending on how you look at it.) 

```
# if flipping horizontal

define opposite:
   opposite = image_height - current_row
Example:
   image_size = (100,200)
   i = 0 , opposite = (image_size[1] - 0) # or 200
   i = 27, opposite = (image_size[1] - 27) # or 173 

start at top of image (y == 0)

loop through entire image one row at a time:
    exchange current row with opposite row 
   
# flipping vertical

Hmmmm. You've got this.

```

| Lilies flipped Vertically|
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/0M34353D2e1101452z2g/yellow_purple_640_flipped.jpeg?X-CloudApp-Visitor-Id=1094421)|

### Posterize

Posterization is the result of reducing the number of colors present in an image. The effect therefore resembles a graphic poster. Kind of like turning an image into a cartoon version. Remember most images have thousands or millions of colors. Posterizing reduces that number to hundreds or dozens.

In the algorithm below, we will split up each of the color channels into ranges. Essentially grouping somewhat like colors into bins, and all values within that bin will get transformed to a specified color assigned to that bin. For example, all values between 0 and 64 might get mapped to 32. However, what these values are is entirely up to you. Then all values between 64 and 128 to 96, etc. 

```
Decide how many colors you want to posterize with,create a list of those colors.

For each pixel CURRENT in the image:
	CURRENT.red <- SnappedColor
	CURRENT.blue <- SnappedColor
	CURRENT.green <- SnappedColor
```
Here is a method that "snaps" values to a particular interval. Another way to look at it is to "round" a value to the 10's or 20's or 30's etc..  We can use a snap-to method to reduce colors by basically rounding an integer value to a "bin". 

```python
def __snap_color__(self,color,snap_val):
    color = int(color)
    m = color % snap_val
    if m < (snap_val // 2):
        color -= m
    else:
        color += (snap_val - m)

    return int(color)
```

| Posterized lilies. Colors reduced mod 64 |
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/0846470J2X3k3f0Y4539/tandr.jpg?X-CloudApp-Visitor-Id=1094421)|

### Blur

There are many ways to smooth or blur an image. The approach taken here is sometimes called mean filtering because we are "filtering" the image by averaging each pixel with it's neighbor and thereby "blurring" the image.

```
Choose how big your kernel will be.

For each pixel CURRENT in the image:
    Move your kernel along the image, averaging the center pixel with all the other pixels within the kernel.
```

As in the glass filter, you will need to deal with the boundary pixels. As far as I'm concerned, you can ignore the edges and start a few pixels in to make things easier. 

| Blurry lilies. Kernel size 5 |
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/2U2W471g2a3v3s1I0l20/blur_5.jpg?X-CloudApp-Visitor-Id=1094421)|

### Solarize

Solarization is an effect from chemical photography caused by vast amounts of over-exposure to film. It results in the reversal of some tones in a photograph; that is, it is a partial negation of the image. The same effect can be achieved in digital image processing by negating those pixels whose intensity lies above or below a certain threshold. You may want your implementation to take a parameter that allows you to experiment more easily.

```
Let THRESHOLD be a fixed number.

For each pixel CURRENT in the image:
	If the intensity of CURRENT is less than (greater than) THRESHOLD,
		then negate CURRENT.
```

You may want to apply some technique other than negate in your method to achieve another effect instead. How does choosing a smaller (larger) value change the result of solarization?


Over-exposed lilies. Solarized with threshold set for those pixels with intensity less than 100.

| Solarized (Overexposure)|
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/1L1w2E0r2P1l0U2u3h0v/solarize.jpg?X-CloudApp-Visitor-Id=1094421)|



### Warhol effect

Andy Warhol was an American artist. He began his career as a commercial illustrator and then became a famous painter. His style combined techniques from commercial illustration popular at the time. We will combine filters described above and in class to mimic his work.

```
Choose a rectangular region RECTANGLE in the image.
Apply grayscale RECTANGLE.
Apply posterize to RECTANGLE.

Split the values [0, 255] into N distinct intervals I1, I2, ..., IN.
For each interval Ik, assign a fixed color COLORk.

For each pixel CURRENT in RECTANGLE:
	Let INTENSITY be the intensity of CURRENT.
	If INTENSITY∈Ik, then set the color of CURRENT to COLORk.
```

Several strategies that we've already seen are present here, most notably thresholding and code reuse. You may want to review if-then-else statements. Also review the conditional operators AND (&&) and OR (||). They are extremely helpful for this filter.

In your analysis, detail the design process. How did you choose the number of intervals, their ranges, and associated colors?


| Warhol effect|
|:---:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/0N412s0r1K252a2H1R40/warhol_16.jpg?X-CloudApp-Visitor-Id=1094421)|

Waterlilies à la Warhol. Intervals were taken in multiples of 32.
The colors used were blue, magenta, orange, yellow, and pink.


