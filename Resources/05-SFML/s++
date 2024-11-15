#!/bin/bash

# Default paths for SFML installation (edit these if needed)
SFML_INCLUDE="/opt/homebrew/Cellar/sfml/2.6.1/include/"
SFML_LIB="/opt/homebrew/lib/"

# Compiler and flags
CXX="g++"
CXXFLAGS="-std=c++17 -I${SFML_INCLUDE}"
LDFLAGS="-L${SFML_LIB} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network"

# Check if source files are provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <source_files> [-o <output_file>]"
    exit 1
fi

# Compile the program
OUTPUT="a.out" # Default output file name
SOURCE_FILES=()

while [[ "$#" -gt 0 ]]; do
    case "$1" in
        -o) # Output file flag
            shift
            OUTPUT="$1"
            ;;
        *) # Collect source files
            SOURCE_FILES+=("$1")
            ;;
    esac
    shift
done

# Run the compilation
echo "Compiling: ${SOURCE_FILES[@]}"
$CXX ${CXXFLAGS} "${SOURCE_FILES[@]}" -o "${OUTPUT}" ${LDFLAGS}

if [ $? -eq 0 ]; then
    echo "Compilation successful: ./${OUTPUT}"
else
    echo "Compilation failed."
fi