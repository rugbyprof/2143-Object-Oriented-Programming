---
title: "Downloadable Word Lists"
description: "A curated collection of downloadable, plain-text English word lists from public domain and open projects for coding, research, and exploration."
category: "resource"
tags: ["words", "dictionary", "plaintext", "data", "language"]
slug: "word-lists"
order: 4
visibility: "public"
---

# Downloadable Word Lists

This collection of downloadable English word lists exists for one simple reason: **realistic programs need realistic data.** Whether you’re building a spell-checker, doing text mining, creating a crossword generator, or just want to test your string algorithms with something more challenging than `["cat", "dog", "bat"]` — these lists are for you.

> These are public domain or openly licensed resources, available as **plain-text files** that are easy to parse, easy to preview, and easy to break things with (on purpose).

## 📦 Word List Sources

### 1. **SCOWL (Spell Checker Oriented Word Lists)**

- **Description**: SCOWL is a flexible English word list generator that lets you download different sizes and dialects (American, British, etc.).
- **Link**: [SCOWL Word Lists](http://wordlist.aspell.net/)
- **Formats**: `.txt` (one word per line)

### 2. **12dicts Word Lists**

- **Description**: Derived from various public domain dictionaries. Offers precompiled lists organized by usage frequency.
- **Link**: [12dicts Word Lists](http://wordlist.aspell.net/12dicts/)
- **Formats**: `.txt`

### 3. **The English Open Word List (EOWL)**

- **Description**: Simple, open, and friendly — great for general use or spelling-related programs.
- **Link**: [EOWL GitHub](https://github.com/dwyl/english-words)
- **Formats**: `.txt`, also `.json` in some forks

### 4. **Moby Project Word Lists**

- **Description**: One of the largest free word lists ever compiled, including synonyms, parts of speech, and names.
- **Link**: [Moby Project on Gutenberg](https://www.gutenberg.org/ebooks/3201)
- **Formats**: `.txt`

### 5. **CMU Pronouncing Dictionary**

- **Description**: Provides not only the words but also phonetic transcriptions. Useful for audio/linguistics projects.
- **Link**: [CMUdict](http://www.speech.cs.cmu.edu/cgi-bin/cmudict)
- **Formats**: `.txt` with word and phoneme pairs (can be filtered)

### 6. **Roger Mitton’s Public Domain List**

- **Description**: A clean, no-frills English word list compiled from public domain resources.
- **Link**: [Roger Mitton’s List](http://www.someya-net.com/words/)
- **Formats**: `.txt`

---

## 🧠 Why These Matter

Most student programs start with synthetic or toy data. That’s fine, but it’s not how things work outside the classroom. Real-world development involves handling:

- Inconsistent casing (`"Apple"` vs `"apple"`)
- Duplicates
- Encoding issues (ASCII, UTF-8, BOM headaches)
- Huge file sizes
- Odd spacing or punctuation

By giving you these larger lists, we’re training your brain and your code to survive in the wild.

---

## 📝 Formats You’ll Encounter

All lists are in **plain-text ASCII-compatible formats**, such as:

- `.txt`: One word per line
- `.csv`: Words with metadata (e.g. frequency, part-of-speech)
- `.json`: Nested or flat arrays of words, great for APIs and apps
- `.tsv`: Tab-separated, easier when commas are in the data

These formats are easy to open, parse, and process in **Python, C++, Bash, or even Excel**.

---

## 💡 Pro Tips

- Use these lists to test **search algorithms**, **autocomplete**, **sorting**, **regex**, or **data cleaning** skills.
- Want to simulate a **typing test** or **hangman game**? These are perfect.
- Trying to build a **scrabble solver**? These are your cheat sheets.
- Curious about **prefix trees or tries**? Load one of these and start building.

---

Enjoy! And remember — if you're building something cool with one of these lists, share it in class or drop a link in the Discord. We’re all here to get better.
