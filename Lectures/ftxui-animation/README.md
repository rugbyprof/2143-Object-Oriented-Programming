# FTXUI sword-swing demo

A deliberately small terminal battle demo: press **Space** to have Thorin attack
Malakai, and **q** or **Esc** to quit. The animation is presentation code; the
damage calculation lives in the battle model and can be tested or reused without
FTXUI.

## Build and run

You need CMake 3.20+, a C++20 compiler, Git, and a terminal with UTF-8 support.
The first configure downloads FTXUI through CMake.

```sh
cmake -S . -B build
cmake --build build
./build/sword_swing_demo
```

On Windows, run `build\\Debug\\sword_swing_demo.exe` when using a multi-config
generator such as Visual Studio.

## Design: start data-driven

No, this game does **not** need a base `Move` class with one subclass per attack
yet. A value-type `Move` is enough while attacks differ only by data such as a
name, damage, resource cost, and animation kind. `Battle::ExecuteAttack()`
turns that data into an `AttackResult`; the UI reads the result and selects an
animation. This keeps the rules independent of FTXUI and avoids a class for
every sword or spell.

Introduce a polymorphic `Move` interface only when attacks truly need different
algorithms or state: for example, a heal that targets an ally, a poison that
creates a lasting effect, a fireball that damages several targets, or a move
whose legality is calculated in a unique way. At that point, a virtual
`Resolve(...)` can be a useful runtime-polymorphic seam. Do not create it just
because several moves have different names or damage values.
