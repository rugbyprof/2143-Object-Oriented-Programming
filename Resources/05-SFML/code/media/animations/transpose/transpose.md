Certainly! FFmpeg’s transpose video filter allows you to rotate or flip images or video frames based on specific transpose codes. Here’s a detailed breakdown of the codes and their effects:

Transpose Codes

Code Operation Description
0 90° clockwise rotation Rotates the frame 90° clockwise.
1 90° counterclockwise rotation Rotates the frame 90° counterclockwise.
2 Vertical flip (mirror) Flips the frame vertically (upside down).
3 Horizontal flip (mirror) Flips the frame horizontally (left/right).

Example FFmpeg Commands

1. Rotate 90° Clockwise

ffmpeg -i input.png -vf "transpose=0" output_90_cw.png

2. Rotate 90° Counterclockwise

ffmpeg -i input.png -vf "transpose=1" output_90_ccw.png

3. Vertical Flip

ffmpeg -i input.png -vf "transpose=2" output_vflip.png

4. Horizontal Flip

ffmpeg -i input.png -vf "transpose=3" output_hflip.png

Combining Transpose Filters

You can chain multiple transpose operations for more complex transformations. For example:

180° Rotation (Vertical Flip + Horizontal Flip)

ffmpeg -i input.png -vf "hflip,vflip" output_180.png

270° Rotation (90° Counterclockwise)

ffmpeg -i input.png -vf "transpose=1,transpose=1,transpose=1" output_270.png

Incorporating This into Your Script

For your rotate_image function, you can directly pass the desired transpose code (0, 1, 2, or 3) to apply the corresponding transformation. For more complex operations like 180° rotation, use the appropriate chain of filters.

Updated Example for 90° Clockwise:

def rotate_image(input_image, output_image, transpose_code):
subprocess.run([
"ffmpeg", "-i", input_image, "-vf", f"transpose={transpose_code}", output_image
], check=True)

Advanced Tips

    1.	Preview the Output:

Before applying to a batch of images, preview the effect with a single image:

ffplay -i input.png -vf "transpose=0"

    2.	Batch Processing:

If you have multiple transformations, you can add conditional logic to loop through the transpose_code values in your script.

Let me know if you’d like further clarification or enhancements to your script! 🚀
