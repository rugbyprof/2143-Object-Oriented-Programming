#!/usr/bin/env python3
import os
import re

def get_directories(path='.'):
    """Returns a list of directories in the given path."""
    return [d for d in os.listdir(path) if os.path.isdir(os.path.join(path, d))]

def remove_numeric_prefix(folder_name):
    """
    Removes a numeric prefix (and following hyphen) from the folder name.
    For example: "01-Array_Based_Stack" -> "Array_Based_Stack"
    """
    return re.sub(r'^\d+-', '', folder_name)

def rename_folders(path='.'):
    folders = sorted(get_directories(path))
    # Optional: filter out hidden directories if needed
    folders = [f for f in folders if not f.startswith('.')]
    
    for index, folder in enumerate(folders):
        # New prefix increments by 3 for each folder
        new_prefix = index * 3
        # Remove any existing numeric prefix from the folder name
        clean_name = remove_numeric_prefix(folder)
        new_name = f"{new_prefix:03d}-{clean_name}"
        
        old_path = os.path.join(path, folder)
        new_path = os.path.join(path, new_name)
        
        # Print the renaming action (for safety, comment out os.rename if needed)
        print(f"Renaming '{folder}' -> '{new_name}'")
        #os.rename(old_path, new_path)

if __name__ == '__main__':
    # Run the renaming in the current directory
    rename_folders()