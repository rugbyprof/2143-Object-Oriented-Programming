#!/bin/zsh

# Get the current directory
SOURCE_DIR="$PWD"

# Get today's date in YYYY-MM-DD format
TODAY=$(date "+%Y-%m-%d")

# Create the destination folder inside the same directory
DEST_DIR="${SOURCE_DIR}/${TODAY}"
mkdir -p "$DEST_DIR"

# Loop through all files and copy those modified today
for file in **/*(.); do
  if [[ $(stat -f "%Sm" -t "%Y-%m-%d" "$file") == "$TODAY" ]]; then
    cp -v "$file" "$DEST_DIR/"
  fi
done

echo "All files modified today have been copied to: $DEST_DIR"