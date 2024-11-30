import os
import subprocess
import glob


# Ensure the output directory exists
#os.makedirs(output_dir, exist_ok=True)

def zpad(number, length):
    return str(number).zfill(length)

# Function to rotate and save image with `ffmpeg`
def rotate_image(input_image, output_image, transpose_code):
    tpstr = ""
    for code in transpose_code:
        tpstr += f"transpose={code},"
        
    subprocess.run([
        "ffmpeg", "-i", input_image, "-vf", f"{tpstr}", output_image
    ], check=True)

    # ffmpeg -i input.png -vf "vflip" output_vflip.png
    # ffmpeg -i input.png -vf "hflip" output_hflip.png
    # ffmpeg -i input.png -vf "hflip,vflip" output_bothflip.png # 180 degrees

# Directory containing your images
input_dir = "../dice_roll"
output_dir = "../dice_roll_0"

os.makedirs(output_dir, exist_ok=True)

# Loop over all images in the input directory with prefix "frame_"
files = glob.glob(input_dir + "/*.png")
files = sorted(files)
i = 0
for filename in files:

    # Rotate 180 degrees
    rotate_image(filename, os.path.join(output_dir, f"frame_{zpad(i,3)}.png"), [0])

    # # Rotate 180 degrees (South)
    # rotate_image(input_path, os.path.join(output_dir, f"south/{base_name}.png"), "2,transpose=2")

    # # Rotate 270 degrees (West)
    # rotate_image(input_path, os.path.join(output_dir, f"west/{base_name}.png"), "2,transpose=1")

    # # Copy original image (North)
    # subprocess.run([
    #     "cp", input_path, os.path.join(output_dir, f"north/{base_name}.png")
    # ], check=True)
    i += 1