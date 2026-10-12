# FTXUI building blocks

Small, standalone programs. Each one shows one FTXUI technique you can use when building your P01 `TuiView`.
They are building blocks, not a game. Read one, run it, and adapt the parts you need.

| File | Shows you how to |
|------|------------------|
| `01_colors.cpp` | style text (`bold`, `dim`, `inverted`), set text and background colors, choose a color from a variable |
| `02_keys.cpp` | react to arrow keys, Enter, letters, and a range of number keys with `CatchEvent` |
| `03_mouse.cpp` | find out which element was clicked with `reflect(box)` and `box.Contain(x, y)` |
| `04_buttons.cpp` | make buttons that run a function when clicked, in several styles |
| `05_show_hide.cpp` | show different buttons at different times with `Maybe` |
| `06_layout.cpp` | arrange things with `hbox`, `vbox`, `filler`, `size`, border styles, and `window`; write a function that returns an `Element` |
| `07_input_slider.cpp` | read text with `Input` and a number with `Slider` |

## Build

**With CMake** (works anywhere the P01 starter builds):

```bash
cd Resources/ftxui
cmake -S . -B build
cmake --build build
./build/02_keys
```

**With g++ and Homebrew FTXUI** (macOS): each file's header comment has the exact command.

```bash
g++ -std=c++17 02_keys.cpp -I$(brew --prefix ftxui)/include \
  -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom -lftxui-screen -o 02_keys
```

## Things that trip people up

- **Buttons ignore clicks:** they must be in a `Container`, and that container must be passed to `Renderer(container, ...)`.
- **The mouse does nothing:** some terminals don't send mouse events. Always give every action a key too.
- **`reflect` boxes are always empty:** the `Box` variables must be declared outside the render lambda.
- **Keep the rules out of the view.** A key or button handler should make *one* call into your game class and nothing more.
