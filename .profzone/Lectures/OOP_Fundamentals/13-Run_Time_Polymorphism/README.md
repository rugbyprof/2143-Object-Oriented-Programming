# 🧩 Runtime Polymorphism — Why It Still Matters

Let’s be honest — runtime polymorphism is one of those topics that sounds abstract until you’ve _lived_ with growing codebases or systems that change faster than you can rewrite them. Most of the examples we show in class:

- “Shape → Circle → Square” or
- “Animal → Dog → Cat”
- "Character → Wizard → Jester”

They seem `too simple` to justify the hype. But small contrived examples is the best way to start talking about a concept. I wouldn't be worried about it if I thought it was unimportant. But I know better. I have limited industry experience, and code reuse and sustainable code bases are huge.

So, these examples are **about the future** — about keeping code flexible when you _don’t yet know what’s coming next._

---

## 🧠 What Runtime Polymorphism Enables

- **Extensibility without rewrites**  
  Systems built on base-class pointers (`Shape*`, `Character*`, `Animal*`) can gain new behaviors without rewriting existing logic.  
  That’s maintainability in action — change one piece, not the whole system.

- **Runtime flexibility**

  - Sometimes you don’t know the object type until the program runs — user choices, plug-ins, or events.
  - **Polymorphism keeps you from hard-coding every possibility.**

- **Cleaner, modular design**
  - Each class handles _how_ something happens; the main program only decides _when_ it happens.
  - This separation of concerns keeps code organized and scalable.

> "Separation of concern" == Decoupling

---

## ⚔️ Example 1 — The D&D Battle Queue

This code was written by ChatGPT, but based on my own ideas used in a previous assignment. I told it (hem/her) that I struggled to come up with an example that my students could implement, and felt it was still lacking the motivation behind dynamic polymorphism. It is a good example, but showing you how to do something doesn't always get the point across. At the end of the readme, there's a "don't do this" example.

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Character {
public:
    virtual void takeTurn() const {
        cout << "A generic character takes a swing.\n";
    }
    virtual ~Character() = default;
};

class Wizard : public Character {
public:
    void takeTurn() const override { cout << "The wizard casts Fireball!\n"; }
};

class Rogue : public Character {
public:
    void takeTurn() const override { cout << "The rogue strikes from the shadows!\n"; }
};

class Paladin : public Character {
public:
    void takeTurn() const override { cout << "The paladin smites the enemy!\n"; }
};

int main() {
    vector<unique_ptr<Character>> party;
    party.push_back(make_unique<Wizard>());
    party.push_back(make_unique<Rogue>());
    party.push_back(make_unique<Paladin>());

    cout << "⚔️ The hallway fight begins!\n";
    for (auto& hero : party)
        hero->takeTurn(); // Runtime decides which version to call
}
```

> The combat loop doesn’t need to know who’s fighting —
> it just says _“Next!”_ and the right behavior happens automatically.

That’s the same principle behind:

- A web server dispatching `processRequest()` to the right handler.
- A graphics engine calling `render()` on every object.
- A robotics controller running different device drivers.

---

## 🐘 Example 2 — The Polymorphic Zoo

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Animal {
public:
    virtual void speak() const { cout << "Some generic animal sound\n"; }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override { cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() const override { cout << "Meow!\n"; }
};

int main() {
    vector<unique_ptr<Animal>> zoo;
    zoo.push_back(make_unique<Dog>());
    zoo.push_back(make_unique<Cat>());

    cout << "🎪 Welcome to the Polymorphic Zoo!\n";
    for (auto& a : zoo)
        a->speak();
}
```

> Each animal knows how to speak; the zoo doesn’t need to check types or write conditionals.

---

## 🎨 Example 3 — The Shape Drawer

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Shape {
public:
    virtual void draw() const { cout << "Drawing generic shape\n"; }
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override { cout << "Drawing a circle\n"; }
};

class Square : public Shape {
public:
    void draw() const override { cout << "Drawing a square\n"; }
};

int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>());
    shapes.push_back(make_unique<Square>());

    cout << "🖌️ Rendering all shapes:\n";
    for (auto& s : shapes)
        s->draw();
}
```

> This same structure powers rendering pipelines, GUI widgets, and plug-in architectures.
> Small examples, big implications.

---

## 💡 Why These “Toy Examples” Matter

Every simple example you write trains habits that scale up:

- You’re **decoupling** what the program _does_ from _how_ it does it.
- You’re **trusting interfaces**, not implementations.
- You’re **designing for change**, not just for completion.

This is the mental model that survives real software growth — in games, frameworks, simulations, and enterprise systems.

So maybe your zoo or battle simulation won’t ship to Steam…
but the _design thinking_ behind it will carry you through every large system you build.

---

## ⚙️ Technical Breakdown

Runtime polymorphism works through **virtual functions** and **base-class pointers or references**.

### Key Benefits

1. **Decoupling Interface from Implementation**
   Program against the interface, not the details. Swap or extend classes without touching client code.

2. **Reusability and Extensibility**
   Functions using base-class pointers work automatically with any subclass.

   > (e.g. adding a new "character" doesn't effect the base class if proper methods are implemented)

3. **Dynamic Behavior**
   The correct method call is chosen at runtime — letting objects respond contextually.

   > (again, calling the correct draw or attack method based on the current instance of the object)

4. **Simpler Code**
   Removes huge `switch` statements and manual type checks.

   > (no more if this type, else if this type, else if this type ....)

5. **Plug-and-Play Architecture**
   Behaviors can be swapped (e.g., AI strategies, payment methods, rendering backends).

---

## 🧩 Where You’ll See It in the Wild

| Domain                   | Example of Runtime Polymorphism                               |
| ------------------------ | ------------------------------------------------------------- |
| **Game Engines**         | Entities overriding `update()` or `draw()`                    |
| **GUI Frameworks**       | Widgets share a base class but respond uniquely to user input |
| **Simulation Systems**   | Vehicles, weather, and actors sharing interfaces              |
| **Plugin Architectures** | Drop-in modules without recompiling the core                  |
| **Networking Layers**    | Different packet types handled via one base interface         |

---

## 🎯 The Core Idea

> Runtime polymorphism is about **trusting the interface** (base class is correctly implemented)
> You call a method, and the _right thing happens_ — even if you don’t know the exact type.

That trust lets you build:

- Extensible engines
- Modular systems
- Maintainable code that gracefully adapts to change

---

# Pain First: Tightly Coupled “Monster AI” (switch soup)

I had a counter example created to show why polymorphism helps (in this case dynamic).

**Smell:** One enum + many `switch`/`if` chains scattered across files.  
**Consequence:** Adding a new behavior = edit multiple places, re-test everything.

### 1) Behavior enum baked everywhere

```cpp
// Behavior.h
#pragma once
enum class BehaviorType { Aggressive, Defensive /* oh no, more later? */ };
```

### 2) `Monster` hard-codes behavior logic

```cpp
// Monster.h
#pragma once
#include "Behavior.h"
#include <string>

class Monster {
    std::string name_;
    BehaviorType behavior_;
public:
    Monster(std::string name, BehaviorType b) : name_(std::move(name)), behavior_(b) {}
    void update() {
        switch (behavior_) {
            case BehaviorType::Aggressive:
                // chase player, no mercy
                std::cout << name_ << " charges!\n"; break;
            case BehaviorType::Defensive:
                // keep distance, block
                std::cout << name_ << " shields up.\n"; break;
        }
    }
    BehaviorType behavior() const { return behavior_; }
};
```

### 3) UI also cares (duplicate knowledge)

```cpp
// MonsterUI.cpp
#include "Monster.h"
void renderBehaviorBadge(const Monster& m) {
    switch (m.behavior()) {
        case BehaviorType::Aggressive: std::cout << "[AGG]\n"; break;
        case BehaviorType::Defensive:  std::cout << "[DEF]\n"; break;
    }
}
```

### 4) Spawner duplicated mapping (third switch)

```cpp
// Spawner.cpp
#include "Monster.h"
Monster spawn(std::string name, std::string style) {
    if (style == "agg") return Monster(name, BehaviorType::Aggressive);
    else                return Monster(name, BehaviorType::Defensive);
}
```

### What happens when we add **Stealth**?

You must change **(at least)**:

1. `BehaviorType` enum
2. `Monster::update()` switch
3. `renderBehaviorBadge()` switch
4. `spawn()` mapping
5. Any analytics/logging code that `switch`es (there will be more…)

You’re violating **Open/Closed**: the system isn’t open to extension; it’s open to _surgery_.

---

# Relief: Decouple with Runtime Polymorphism

We move behavior into **objects**. The `Monster` knows only an interface; each behavior knows how to act and how to present itself.

### 1) Define a stable interface

```cpp
// IBehavior.h
#pragma once
#include <string>
struct IBehavior {
    virtual ~IBehavior() = default;
    virtual void update() = 0;
    virtual std::string badge() const = 0;  // UI hint moved here!
};
```

### 2) Implement concrete behaviors

```cpp
// Aggressive.h
#pragma once
#include "IBehavior.h"
#include <iostream>
struct Aggressive : IBehavior {
    void update() override { std::cout << "charges!\n"; }
    std::string badge() const override { return "[AGG]"; }
};

// Defensive.h
#pragma once
#include "IBehavior.h"
#include <iostream>
struct Defensive : IBehavior {
    void update() override { std::cout << "shields up.\n"; }
    std::string badge() const override { return "[DEF]"; }
};
```

### 3) Monster depends on the interface, not a type code

```cpp
// Monster.h
#pragma once
#include "IBehavior.h"
#include <memory>
#include <string>
#include <iostream>

class Monster {
    std::string name_;
    std::unique_ptr<IBehavior> behavior_;
public:
    Monster(std::string name, std::unique_ptr<IBehavior> b)
      : name_(std::move(name)), behavior_(std::move(b)) {}

    void update() {
        std::cout << name_ << " ";
        behavior_->update(); // runtime dispatch
    }
    void renderBadge() const {
        std::cout << behavior_->badge() << "\n"; // UI no longer switches
    }
};
```

### 4) Spawner composes behaviors (no `switch`)

```cpp
// Spawner.h
#pragma once
#include "Monster.h"
#include "Aggressive.h"
#include "Defensive.h"
#include <memory>
#include <string>

inline Monster spawn(std::string name, std::string style) {
    if (style == "agg") return Monster(std::move(name), std::make_unique<Aggressive>());
    if (style == "def") return Monster(std::move(name), std::make_unique<Defensive>());
    // default/fallback policy can be centralized here
    return Monster(std::move(name), std::make_unique<Defensive>());
}
```

### 5) Add a new behavior — **without touching Monster/UI**

```cpp
// Stealth.h
#pragma once
#include "IBehavior.h"
#include <iostream>
struct Stealth : IBehavior {
    void update() override { std::cout << "vanishes into the shadows.\n"; }
    std::string badge() const override { return "[STL]"; }
};
```

Wire it up only in the **composition** step (or via a plugin registry):

```cpp
// Spawner.h (add one line)
if (style == "stl") return Monster(std::move(name), std::make_unique<Stealth>());
```

> Notice what **didn’t** change:  
> `Monster`, `renderBadge`, and any analytics that ask the behavior for its own metadata.  
> You extended the system by **adding a class**, not by editing five switches.

---

## Why this matters (even in a “toy” example)

**Tightly coupled** code:

- duplicates knowledge (every layer must “know” the enum),
- scatters decisions (many switches),
- breaks Open/Closed (new feature = edit everywhere),
- makes regression risk explode.

**Polymorphic** design:

- centralizes each behavior’s logic and presentation,
- keeps clients stable (they just call the interface),
- reduces ripple edits,
- makes “add a behavior” a low-risk, local change.

> The example is simple on purpose. In real projects, the same pattern shows up in payment providers, file exporters, AI strategies, device drivers, render passes, and request handlers. Polymorphism turns a “rewrite hotspots everywhere” change into an “add a class” change.

---

## Exercise

1. See how hard it is to add `Berserk` and `Cowardly` to the first version.
2. How bad was it? How long did it take?
3. Add `Berserk` using the **polymorphic** version. Easy?

> Takeaway: Design matters ... right?

## 💬 Final Thoughts

If polymorphism still feels awkward, you’re not alone.
It took me years — and more than one “meh” lecture — before I realized this topic isn’t about fancy keywords; it’s about **future-proof design**.

Every `virtual` function you write is a small act of humility:
a way of saying _“I don’t know the future — but my code will be ready for it.”_

Tell your future self, _you’ll thank me later._
