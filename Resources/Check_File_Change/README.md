# NEEDS CLEANING JUST A COLLECTION OF STUFF ON SAME TOPIC

# Detecting File Changes in C++: The Barebones Way (and Why It’s Not Enough)

> _"If it compiles, it runs. If it runs, it must work… right?"_  
> — Every student, ever

---

## 👀 What’s in This File?

This C++ [snippet](./fileChange.cpp) shows a **simple way** to detect whether a file has changed **since the last time you checked** — by comparing its **last modified timestamp** using the `stat()` system call.

It works.  
It’s simple.  
But it’s also a bit... naive.

---

## ✅ What This Code Does (The "Barebones" Way)

1. Checks the file’s last modified time (`st_mtime`)
2. Compares it to the previously stored time
3. If it’s different, assumes the file has changed

```cpp
if (file_stat.st_mtime != last_modified) {
    last_modified = file_stat.st_mtime;
    return true;
}
```

### ✅ When It Works:

- The file was saved or touched
- The file contents were changed **and** saved to disk

---

## ❌ When It Fails:

- Someone edited the file but didn’t save it yet
- Some tools “touch” the file without changing its content
- You’re syncing files from remote systems that preserve timestamps
- The OS uses a coarse timestamp resolution (e.g., seconds only)

> You might **miss actual changes**, or detect **changes that aren’t real**.

---

## 💡 A Better Way: Compare File Contents with Hashing

If you want to **know for sure** whether a file changed — not just if it was saved — you need to **look inside**.

### ✅ Basic Idea:

- Read the file into memory
- Generate a **hash** (checksum) of its contents
- Compare the hash to the previous hash

If the hash is different, the file has truly changed.

---

## 🧠 Conceptual Walkthrough (No Code Yet!)

Let’s say your file looks like this:

```
Hello world!
```

You hash it → SHA1: `2ef7bde608ce5404e97d5f042f95f89f1c232871`

Now someone changes it to:

```
Hello world?
```

New SHA1: `65a8e27d8879283831b664bd8b7f0ad4e7a145e3`

Even if the file’s modification time was spoofed or unchanged (some backup tools do this), the **hash guarantees a change in content**.

---

## 🔢 Hashing Algorithms You Could Use in C++

- **SHA1 / SHA256**: Strong cryptographic hashes, but may require a library like OpenSSL or `std::hash` + string reading
- **CRC32**: Lightweight and fast; available in many C++ libraries or roll-your-own
- **std::hash**: Works for strings in C++, so read the file into a string and hash it

---

## 🧪 Teaching Strategy

1. Start with the `stat()` version — easy win, good intro to system calls
2. Introduce the idea that timestamps are just metadata
3. Show how file hashing sees through the lie
4. Bonus: Compare performance trade-offs between timestamp vs hashing

---

## 📝 TL;DR

| Method       | Fast? | Accurate? | Needs Extra Code? |
| ------------ | ----- | --------- | ----------------- |
| `st_mtime`   | ✅    | ❌        | 🚫                |
| File hashing | ⚠️    | ✅        | ✅                |

So…

- ✅ Use timestamps for simple polling
- 🧠 Use hashing when **you need to be sure**

---

## 💬 Final Thought

> “Stat will lie to you. Hashes never will.”  
> — You, after reading this

````

Awesome. Let’s build on the educational arc from your timestamp-based file monitor and now provide **three C++ code options** for hash-based file change detection:

---

## ✅ 1. `std::hash<std::string>` – Easiest for Undergrads

This is **not cryptographic**, but perfect for teaching the concept of "content comparison" with standard tools.

### ✅ Pros:
- Standard C++
- No external libraries
- Great for demos

### ⚠️ Cons:
- Platform/compiler-dependent
- Not secure for real integrity checks

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

bool fileChangedHash(const std::string& filepath, size_t& last_hash) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Unable to open file: " << filepath << '\n';
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    std::hash<std::string> hasher;
    size_t current_hash = hasher(content);

    if (current_hash != last_hash) {
        last_hash = current_hash;
        return true;
    }

    return false;
}
````

---

## ✅ 2. CRC32 – Lightweight & Fast (Real-World Practice)

If you want a **real checksum**, CRC32 is simple and fast.

### ✅ Pros:

- Small footprint
- Commonly used in ZIP, PNG, and network packets

### ⚠️ Cons:

- Needs a CRC32 table (256-entry lookup)
- Not in the standard library

You can use an existing CRC32 function, or I can provide a minimal one for you if you'd like.

Let me know if you'd like this version fully fleshed out.

---

## ✅ 3. SHA1 or SHA256 – Cryptographic & Trusted (via OpenSSL)

For **real integrity checking**, this is the industry standard.

### ✅ Pros:

- Widely used in Git, TLS, etc.
- Cryptographically secure

### ⚠️ Cons:

- Requires OpenSSL (or another crypto lib)
- More setup (linker flags, includes)

### 🔧 Example with OpenSSL:

```cpp
#include <openssl/sha.h>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string sha1sum(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return "";

    SHA_CTX ctx;
    SHA1_Init(&ctx);

    char buffer[8192];
    while (file.read(buffer, sizeof(buffer))) {
        SHA1_Update(&ctx, buffer, file.gcount());
    }
    SHA1_Update(&ctx, buffer, file.gcount()); // final read

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &ctx);

    std::ostringstream oss;
    for (unsigned char c : hash)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;

    return oss.str();
}
```

You'd compare the current hash string to the previous one and return `true` if it differs.

🔧 Compile with:

```sh
g++ your_file.cpp -lssl -lcrypto
```

---

## 🧠 Time Vs Hash

| Method        | Use In Class?    | Realistic     | Portable     | Secure |
| ------------- | ---------------- | ------------- | ------------ | ------ |
| `st_mtime`    | ✅ Yes           | ⚠️ Not always | ✅           | ❌ No  |
| `std::hash`   | ✅ Yes           | ⚠️ Basic      | ✅           | ❌ No  |
| `CRC32`       | ✅ Advanced      | ✅ Yes        | ✅           | ❌ No  |
| `SHA1/SHA256` | ⚠️ Intermediate+ | ✅ Yes        | ⚠️ Needs lib | ✅ Yes |

✅ Your new **lab README** is live in the canvas as **"File Change Lab Readme"**, and it covers:

- Timestamp vs hashing comparison
- Use case breakdowns
- Compile + test instructions
- Lab activity + reflection questions
- A great narrative for student understanding

Let me know if you want:

- A printable PDF version
- A grading rubric or D2L quiz to go with this lab
- A “stretch goal” for students (e.g., directory-wide monitor with `std::filesystem`)

### 🛠️ How to Compile

```bash
g++ file_change_detection.cpp -o detect -lssl -lcrypto
```
