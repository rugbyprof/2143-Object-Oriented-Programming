import os
import subprocess

# Directory containing your images
input_dir = "path/to/your/images"
output_dir = "path/to/output/images"

# Ensure the output directory exists
os.makedirs(output_dir, exist_ok=True)

# Function to rotate and save image with `ffmpeg`
def rotate_image(input_image, output_image, transpose_code):
    subprocess.run([
        "ffmpeg", "-i", input_image, "-vf", f"transpose={transpose_code}", output_image
    ], check=True)

# Loop over all images in the input directory with prefix "frame_"
for filename in os.listdir(input_dir):
    if filename.startswith("frame_") and filename.endswith(".png"):
        base_name = os.path.splitext(filename)[0]
        input_path = os.path.join(input_dir, filename)

        # Rotate 90 degrees (East)
        rotate_image(input_path, os.path.join(output_dir, f"{base_name}_E.png"), 1)

        # Rotate 180 degrees (South)
        rotate_image(input_path, os.path.join(output_dir, f"{base_name}_S.png"), "2,transpose=2")

        # Rotate 270 degrees (West)
        rotate_image(input_path, os.path.join(output_dir, f"{base_name}_W.png"), "2,transpose=1")

        # Copy original image (North)
        subprocess.run([
            "cp", input_path, os.path.join(output_dir, f"{base_name}_N.png")
        ], check=True)