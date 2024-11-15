import os
import subprocess


# Directory containing your images
input_dir = "."
output_dir = "./rotated"

# Ensure the output directory exists
os.makedirs(output_dir, exist_ok=True)

# Function to rotate and save image with `ffmpeg`
def rotate_image(input_image, output_image, transpose_code):
    subprocess.run([
        "ffmpeg", "-i", input_image, "-vf", f"transpose={transpose_code}", output_image
    ], check=True)

    # ffmpeg -i input.png -vf "vflip" output_vflip.png
    # ffmpeg -i input.png -vf "hflip" output_hflip.png
    # ffmpeg -i input.png -vf "hflip,vflip" output_bothflip.png # 180 degrees

# Loop over all images in the input directory with prefix "frame_"
for filename in os.listdir(input_dir):
    if filename.startswith("frame_") and filename.endswith(".png"):
        base_name = os.path.splitext(filename)[0]
        input_path = os.path.join(input_dir, filename)

        # Rotate 90 degrees (East)
        rotate_image(input_path, os.path.join(output_dir, f"east/{base_name}.png"), 1)

        # Rotate 180 degrees (South)
        rotate_image(input_path, os.path.join(output_dir, f"south/{base_name}.png"), "2,transpose=2")

        # Rotate 270 degrees (West)
        rotate_image(input_path, os.path.join(output_dir, f"west/{base_name}.png"), "2,transpose=1")

        # Copy original image (North)
        subprocess.run([
            "cp", input_path, os.path.join(output_dir, f"north/{base_name}.png")
        ], check=True)