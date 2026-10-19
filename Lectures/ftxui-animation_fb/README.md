<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: L09-ftxui-animation_fb
name: L09-ftxui-animation_fb
title: NO TITLE
description: NO DESCRIPTION
category: Lectures
date_due:
  month: '10'
  day: '19'
  year: 2026
  hour: 8
```

</details>

# FTXUI fireball demo

A deliberately small terminal battle demo: press **Space** to have Thorin swing
his sword at Malakai, **f** to hurl a fireball across the arena at him, and
**q** or **Esc** to quit. The animation is presentation code; the
damage calculation lives in the battle model and can be tested or reused without
FTXUI.

## Build and run

You need CMake 3.20+, a C++20 compiler, Git, and a terminal with UTF-8 support.
The first configure downloads FTXUI through CMake.

```sh
cmake -S . -B build
cmake --build build
./build/fireball_demo
```

On Windows, run `build\\Debug\\fireball_demo.exe` when using a multi-config
generator such as Visual Studio.

## How the fireball works

`FireballAnimation` follows the same pattern as `SwordSwingAnimation`: a
background thread steps through frames (Cast, Flight, Impact, Recover) and asks
FTXUI to redraw after each one. The Flight frame repeats `kFlightSteps` times,
and `Position()` tells the renderer how far along the fireball is, so
`FireballLane()` can pad it over to the right column.

The damage is still calculated by `Battle::ExecuteAttack()` the moment you press
**f**. The renderer simply shows Malakai's old HP until the fireball lands, so
the health bar drops on impact instead of before the fireball leaves Thorin's
hands.

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
