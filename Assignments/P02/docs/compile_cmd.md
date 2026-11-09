# G++ What ?!?

Below is a breakdown of the compiler flags we use. You don't have to use all of them, but most of you should, since they give you a lot more information.

## Where do these flags live now?

P02 builds with CMake, so you don't type a `g++` command yourself. The flags are set in `CMakeLists.txt`:

| `CMakeLists.txt` line                                             | Plain `g++` equivalent                             |
| ----------------------------------------------------------------- | -------------------------------------------------- |
| `set(CMAKE_CXX_STANDARD 17)`                                      | `-std=c++17`                                       |
| `set(CMAKE_BUILD_TYPE Release)`                                   | `-O3` (see `-O2` below)                            |
| `target_compile_options(imgtool PRIVATE -Wall -Wextra -pedantic)` | `-Wall -Wextra -pedantic`                          |
| `target_include_directories(imgtool SYSTEM PRIVATE include)`      | `-isystem include`                                 |
| `target_link_libraries(imgtool PRIVATE ftxui::dom ftxui::screen)` | `-I<ftxui>/include ... -lftxui-dom -lftxui-screen` |

That last row is the reason we use CMake: the FTXUI paths differ on every computer, and CMake works them out for you.

`-isystem` works like `-I` (search this folder for headers), but it also tells the compiler "this is someone else's code, don't warn me about it." That keeps the stb headers' warnings out of your build output.

## 🏎 `-O2` — Optimization Level 2

This tells the compiler:

> “Please try reasonably hard to make this code fast.”

There are levels:

- `-O0` → No optimization (default for debugging)
- `-O1` → Some optimization
- `-O2` → Good balance of speed and compile time
- `-O3` → Aggressive optimization (can increase binary size)
- `-Ofast` → YOLO mode (may break strict standards compliance)

### Why use `-O2` for our class?
- Produces realistic performance
- Doesn't usually break debugging
- Standard “normal” build level in production

If you want easier debugging, use `-O0 -g` (no optimization)

---

## ⚠️ `-Wall` — Enable Common Warnings

This does **not** mean “all warnings.”  
It means:

> “Turn on the common, important warnings.”

**Examples it might catch**:
- Unused variables
- Missing return statements
- Suspicious comparisons
- Implicit conversions

It’s basically:

> “Hey friend, you wrote something fishy.”

And that’s good.

---

## ⚠️➕ `-Wextra` — More Warnings

This enables additional warnings beyond `-Wall`.

**Examples:**
- Unused parameters
- Signed/unsigned mismatches
- More subtle questionable behavior

For us in a learning environment, it's good.

**It makes students confront:**
- sloppy logic
- incorrect types
- silent bugs

---

## 📏 `-pedantic` — Follow the C++ Standard Strictly

This tells the compiler:

> “Warn me if I’m doing something non-standard.”

**It prevents:**
- GCC extensions
- Non-portable shortcuts
- Compiler-specific hacks

**Why it matters:**
I want all of you writing **standard C++**, not the “it works on my machine” C++.

---

## 🧠 What These Flags Really Mean Together

When you compile with:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic
```

You are saying:

> Compile using the C++17 standard,  
> optimize reasonably,  
> warn me about suspicious code,  
> and don’t let me cheat with non-standard extensions.

That’s a very responsible build.

---

## 🎓 In Laypersons Terms

You can say:

- `-O2` → makes your code faster
- `-Wall -Wextra` → makes your code cleaner
- `-pedantic` → makes your code portable

**Why does it matter:**

> Because C++ will happily compile terrible code unless you ask it not to.

That’s not a joke.

---

# 🔥 What Happens If You Don’t Use Them?

You get away with:
- keeping unused variables
- possibly comparing signed and unsigned types
- forget to include return statements (even in void)
- ignore implicit narrowing (loss of precision or similarly demoting one type to another with possible data loss)
- accidentally rely on compiler quirks

**And C++ says:**

> Sure. Why not.

---

## 🧪 Optional Advanced Move (If You Want To Be Spicy)

You can add:

```bash
-Werror
```

That turns warnings into errors.

The you *must* fix them. This can be frustrating. 

It's  brutal early on, but fantastic for releasable code.


# Final Thought

Those flags aren’t magic.

They’re just you telling the compiler:

> “Please hold my students to a higher standard than they would naturally hold themselves to.”
