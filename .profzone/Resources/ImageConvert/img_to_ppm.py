from PIL import Image
import sys


def convert_to_uncompressed_ppm(input_path, output_path):
    # Open the JPG or PNG image
    with Image.open(input_path) as img:
        # Convert to RGB to ensure compatibility with PPM format
        rgb_img = img.convert("RGB")
        # Save as PPM. By default, Pillow saves PPM as uncompressed binary (P6)
        rgb_img.save(output_path, "PPM")
    print(f"Successfully converted {input_path} to {output_path}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("usage: img_to_ppm.py input.<png,jpg,bmp,gif> output.ppm")
        sys.exit(1)
    # Example Usage
    convert_to_uncompressed_ppm("input_image.jpg", "output_image.ppm")
