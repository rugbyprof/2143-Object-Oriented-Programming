# P01 Setup: Compiler + CMake + FTXUI

You will **not** install FTXUI yourself. The starter's `CMakeLists.txt` downloads and builds it for you the first time you build. You only need three things:

1. A C++17 compiler (`g++` or `clang++`, either is fine)
2. CMake 3.20 or newer
3. A modern terminal

Wondering what CMake actually *is*, or what the commands below do? See **[CMake_Basics.md](./CMake_Basics.md)**.

Follow **only** the section for your operating system, top to bottom. Don't skip steps or pick and choose from different tutorials. If something fails, check the [Troubleshooting](#troubleshooting) table **before** you search online.

> **Keep your project in a simple path.** Something like `C:\dev\p01` or `~/dev/p01`.
> **Not** in OneDrive, iCloud Drive, Dropbox, or any folder with spaces in its name. Sync folders and spaces cause most of the "it worked yesterday" problems.

---

## macOS

### 1. Install the compiler

```bash
xcode-select --install
```

A dialog pops up. Click **Install**. If it says the tools are already installed, that's fine.

> On a Mac, `g++` and `clang++` are **the same compiler** (Apple Clang). It doesn't matter which name a tutorial uses.

### 2. Install CMake

If you have [Homebrew](https://brew.sh):

```bash
brew install cmake
```

No Homebrew? Download the macOS `.dmg` from <https://cmake.org/download/>. Open **CMake.app** once, then run this once so the terminal can find it:

```bash
sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
```

### 3. Verify

```bash
g++ --version
cmake --version
```

Both should print a version, and CMake must be **3.20 or higher**. Now go to [Build the toolchain check](#build-the-toolchain-check-everyone).

---

## Windows (MSYS2 + g++)

We use **MSYS2 UCRT64**. It gives you a real `g++` plus CMake and Ninja, all from one place.

### 1. Install MSYS2

Download the installer from <https://www.msys2.org> and keep the default location, `C:\msys64`.

### 2. Install the tools

From the Start menu, open **"MSYS2 UCRT64"**. The prompt must say **UCRT64** in purple, not MSYS or MINGW64. Then run:

```bash
pacman -Syu
```

If it closes the window, reopen **MSYS2 UCRT64** and run:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

Press Enter to accept the defaults, then `Y`.

### 3. Add the tools to your Windows PATH

This lets VS Code, PowerShell, and Windows Terminal find `g++` too.

1. Press the Windows key and type **"environment variables"**, then open **"Edit the system environment variables"**.
2. Click **Environment Variables...**. Under *User variables*, select **Path** and click **Edit**.
3. Click **New**, add `C:\msys64\ucrt64\bin`, and click OK on every window.
4. **Close and reopen** any terminals and VS Code.

### 4. Verify

Open a **new** PowerShell or VS Code terminal:

```powershell
g++ --version
cmake --version
ninja --version
```

All three must print versions. If you see `'g++' is not recognized`, redo step 3, and make sure you actually closed and reopened the terminal.

### 5. Use a good terminal

Run your game in **Windows Terminal** (it comes with Windows 11; it's free in the Microsoft Store for Windows 10) or in the **VS Code terminal**.
Do **not** use the old blue-ish `cmd.exe` window or the MSYS2 "mintty" window. They mangle the card suits and arrow keys.

### Plan B: WSL

If MSYS2 fights you, Ubuntu on WSL works too:

```bash
sudo apt update && sudo apt install -y build-essential cmake
```

From then on, follow the Linux/macOS commands.

---

## Build the toolchain check (everyone)

From inside the `starter/` folder:

**macOS / Linux / WSL**

```bash
cmake -S . -B build
cmake --build build
./build/check
```

**Windows (PowerShell or VS Code terminal)**

```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\check.exe
```

The first `cmake -S . -B build` downloads FTXUI and takes a minute. After that, builds are fast.

**Success looks like this:** a box with four card suits (♣ ♦ ♥ ♠). The ♦ and ♥ are red, the arrow keys move the double border, and `q` quits.

**Milestone 0:** take a screenshot of it running, terminal and all, and submit it.

---

## The everyday build loop

After the first time, this is all you do:

```bash
cmake --build build      # compile (only re-builds what changed)
./build/game             # run the TUI   (Windows: .\build\game.exe)
./build/game --text      # run the console version
```

You only re-run the `cmake -S . -B build ...` line if you:

- add a new `.cpp` file, or
- delete the `build/` folder.

### Text-only build without CMake (Milestone 1 only)

Before you have written any FTXUI code, you can build the console version with a single command:

```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o game
```

Once `TuiView.cpp` exists, this command no longer links. Use CMake from then on.

---

## Troubleshooting

| You see                                                     | What it means / fix                                                                                                                |
| ----------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| `cmake: command not found` / `'cmake' is not recognized`    | CMake isn't on your PATH. Mac: redo step 2. Windows: redo step 3, then **reopen** the terminal.                                    |
| `CMake 3.20 or higher is required`                          | Old CMake. Mac: `brew upgrade cmake`. Windows: `pacman -Syu`.                                                                      |
| `Could not find ... NMake` or it tries to use Visual Studio | You forgot `-G Ninja` on Windows. Delete `build/` and configure again **with** `-G Ninja`.                                         |
| `Does not match the generator used previously`              | You switched generators. Delete the `build/` folder and configure again.                                                           |
| Fails while downloading FTXUI                               | You need internet for the first configure. Campus Wi-Fi blocking it? Try another network once. After that it's cached in `build/`. |
| `fatal error: ftxui/...: No such file`                      | You compiled with plain `g++` instead of CMake. Use `cmake --build build`.                                                         |
| `undefined reference to Hand::...` (or similar)             | You added a new `.cpp`. Re-run the configure line (`cmake -S . -B build ...`).                                                     |
| Suits show as `?` or boxes, or arrow keys print `^[[D`      | Wrong terminal. Use Windows Terminal or the VS Code terminal.                                                                      |
| `libstdc++-6.dll was not found`                             | Your `CMakeLists.txt` lost the `if(MINGW) ... -static` block. Put it back.                                                         |
| Anything weird after editing `CMakeLists.txt`               | Delete `build/` and configure again. This fixes about half of all CMake problems.                                                  |

Still stuck? Bring **(1)** the exact command you ran and **(2)** the full error text, copy-pasted rather than a phone photo, to office hours or the class forum.
