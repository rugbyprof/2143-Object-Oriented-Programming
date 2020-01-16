Flow
====

### Overview
The purpose of flow free is to connect matching colors with a pipe and to create a flow. The goal is to pair all colors, and cover the entire board. This is the only way you to solve each puzzle.

I have created a heuristic of sorts to help solve a flow puzzle. This method works for most puzzles. The simple idea behind the heuristic is to connect the "flows" that are on the outside of the board and work your way in. After an "edge" color is connected, its "flow" becomes the new "edge" of the board, and other colors can now be connected using the edge of the board.   

|           |           |           |
|:---------:|:---------:|:---------:|
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/3y3h10272V3F3c012C35/IMG_2035.png) | ![](https://d3vv6lp55qjaqc.cloudfront.net/items/3V1G3y1R36011L1g0G2u/IMG_2036.png) | ![](https://d3vv6lp55qjaqc.cloudfront.net/items/3S0R3w3j1k3v0Y3W2R1K/IMG_2037.png) |
|![](https://d3vv6lp55qjaqc.cloudfront.net/items/2a0Y0d3j2X1g0l2A2E0I/IMG_2038.png) | ![](https://d3vv6lp55qjaqc.cloudfront.net/items/0D212i152s0d2l202j1D/IMG_2039.png) | ![](https://d3vv6lp55qjaqc.cloudfront.net/items/0a1i0i0l2S29362I0g02/IMG_2040.png) |




### Animations

- [Example 1](https://d3vv6lp55qjaqc.cloudfront.net/items/1e2b27241l3I103f423K/Screen%20Recording%202017-03-28%20at%2010.27%20AM.gif?X-CloudApp-Visitor-Id=1094421)
- [Example 2](https://d3vv6lp55qjaqc.cloudfront.net/items/0E1R212o3Z1s111u1r1Z/Screen%20Recording%202017-03-28%20at%2010.26%20AM.gif?X-CloudApp-Visitor-Id=1094421)
- [Example 3](https://d3vv6lp55qjaqc.cloudfront.net/items/3s3i2C0p0J202z2z2c0B/Screen%20Recording%202017-03-28%20at%2010.25%20AM.gif?X-CloudApp-Visitor-Id=1094421)
- [Example 4](https://d3vv6lp55qjaqc.cloudfront.net/items/3B3S3u083l30003i2Q0R/Screen%20Recording%202017-03-28%20at%2010.24%20AM.gif?X-CloudApp-Visitor-Id=1094421)
