## Shorten Compile Command

Creating a script to simplify the compilation process for SFML is a great idea, and it will make things much more approachable for your students. Below is a simple Bash script that can be customized by each student based on their local setup.

### Bash Script: sfml_build.sh

Create a script named sfml_build.sh and include the following content:

```bash
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
```

### How to Use the Script

1. Save the Script:

- Save the file as sfml_build.sh in a directory accessible to students.

2. Make the Script Executable:

```bash
chmod +x sfml_build.sh
```

3. Run the Script:

- To compile a single file:

```bash
./sfml_build.sh main.cpp
```

- To compile multiple files:

```bash
./sfml_build.sh main.cpp another_file.cpp
```

- To specify an output file name:

```bash
./sfml_build.sh main.cpp -o my_program
```

### Customizing the Script

Each student can edit the SFML_INCLUDE and SFML_LIB paths in the script to match their local setup. These paths depend on where SFML was installed on their system.

For example:

- macOS with Homebrew:
- Include path: /opt/homebrew/Cellar/sfml/2.6.1/include/
- Library path: /opt/homebrew/lib/
- Linux:
- Include path: /usr/include/
- Library path: /usr/lib/
- Windows with WSL (if installed via package manager):
- Include path: /usr/include/
- Library path: /usr/lib/

Advantages

- Shortened Command: Students only need to run ./sfml_build.sh <source_files>.
- Customizable: Each student can update the script to reflect their local paths without modifying their compile command every time.
- Simplified Options: The script handles common flags (-std=c++17, -lsfml-graphics, etc.) automatically.

### Advanced: Environment Variables

To avoid modifying the script for every setup, you could use environment variables. Update the script to check for SFML_INCLUDE and SFML_LIB environment variables, falling back to defaults if they’re not set.

```bash
SFML_INCLUDE="${SFML_INCLUDE:-/opt/homebrew/Cellar/sfml/2.6.1/include/}"
SFML_LIB="${SFML_LIB:-/opt/homebrew/lib/}"
```

Then students can set their paths dynamically:

```bash
export SFML_INCLUDE="/custom/path/to/include"
export SFML_LIB="/custom/path/to/lib"
```

This script should make compiling SFML projects much easier for your students. Let me know if you’d like further tweaks!
