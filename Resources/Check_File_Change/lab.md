## 🧠 File Watcher Lab: Can You Catch a File in the Act?

> “Is it _really_ changing, or is it just pretending?”  
> — A suspicious programmer, probably

---

### 👀 What's the Point?

In the real world, programs often need to **notice when a file changes** — for example:

- A config file that gets updated (should we reload it?)
- A log file that stops growing (is the service dead?)
- A homework folder that mysteriously updates right before the deadline 👀

This project shows you **two ways** to detect file changes in C++:

1. **Timestamps** (fast and simple)
2. **Hashing** (thorough but heavier)

You’ll explore the trade-offs and decide what “changed” really means — because surprise: the computer doesn’t know until _you define it._

---

### 🛠 What You’ll Build

You’ll write and test C++ programs that:

- Watch a file for updates
- Compare timestamps or content hashes
- Print a message when something changes
- Help you understand what kinds of changes actually matter

---

### 🚦 Two Detection Methods

#### 🕒 Method 1: Check the Last Modified Time

Like checking the date on a milk carton — if it’s newer than the one you remembered, it probably changed.

- ✅ Fast
- ✅ Catches edits _and_ when someone just saves without changing anything
- ❌ Can be fooled (e.g., a file touched with `touch file.txt`)
- ❌ Won’t catch if someone replaces contents but keeps same timestamp

---

#### 🔐 Method 2: Hash the Contents

This is like taking a fingerprint of the file's content. If anything inside changes — even a single space — the fingerprint is different.

- ✅ Super accurate
- ✅ Ignores timestamp tricks
- ❌ Slower (has to read whole file)
- ❌ Won’t catch if the file was touched but not changed

---

### 🧪 Try This!

#### 1. Create a file:

```bash
echo "test 123" > example.txt
```

#### 2. Run your programs:

```bash
./detect_time      # For timestamp
./detect           # For hashing (requires OpenSSL)
```

#### 3. Try stuff:

- Add a line
- Delete a line
- Just hit save
- Run `touch example.txt`

See what each method detects. Make a table!

---

### 🔁 Extensions & Project Ideas

Want to go further? Pick one:

- ✅ Watch a **directory** instead of a file (loop over `.cpp` files?)
- ✅ Combine **both methods** for more reliable detection
- ✅ Log when and what changed over time
- ✅ Use `std::filesystem` to scan folders
- ✅ Use `inotify` (Linux) or `ReadDirectoryChangesW` (Windows) for event-based monitoring

Bonus: Make a terminal dashboard that updates live 👀

---

### 💬 Teacher Notes (yes, your prof has opinions)

> “Hashing is amazing — until you realize the timestamp would’ve been fine and 10x faster.”

Use hashing when:

- You care about _what_ changed
- File edits matter more than file activity
- You don’t trust the timestamp

Use timestamps when:

- You care about _whether_ something happened
- You’re polling files every few seconds
- You don’t need to verify exact contents

---

### 🧠 Reflection Questions

1. If a file is being updated by a process but the content stays the same, what method works better?
2. What happens when you `touch` a file? Why does that matter?
3. Why would `git` use SHA1 hashes to detect changes?
4. How could you avoid unnecessary reads of giant files?

---

### ✅ Final Tip

Think like an OS: fast, efficient, and lazy — until it _really_ matters. Then be paranoid and check everything.
