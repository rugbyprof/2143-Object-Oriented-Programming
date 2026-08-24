# 🎲 Dice Game Lab: Roll, Simulate, Dominate

> “All programming is a gamble… might as well roll with it.”

---

### 👀 What's This About?

This lab is all about **rolling dice using C++**. Yeah, the same dice you'd use in Monopoly, Yahtzee, or D&D.

But here’s the fun twist: instead of just generating numbers, you’ll explore **how randomness works**, how to simulate different types of dice, and how to build your own dice-based games and logic.

If you're a fan of probability, games, or programming that doesn't put you to sleep — this is the place to be.

---

## 🧠 Concepts You’ll Learn

- How to use the C++ random library (`<random>`)
- What a “fair” die really is (and how to test fairness)
- How to represent a die in a class
- Simulating dice rolls and storing results
- Projecting probability distributions visually
- Extending to real-world games

---

### 🧱 What’s Already Here?

Your current C++ code includes:

- `Die` class that handles face count and rolling
- Basic simulation of thousands of rolls
- Frequency tracking using `std::map`
- Optional use of `#define` to change behavior
- A solid foundation for _any_ dice-based system

#### 📋 Potential Fixes/Enhancements:

- Use `std::uniform_int_distribution<>` instead of `rand()` for better randomness
- Wrap RNG with a proper seed once (`std::random_device`)
- Add ASCII art or terminal animation for visual flair
- Output histogram of results for probability visualization

---

## 🎮 Dice-Based Project Ideas

Here’s where you shine. Build on the starter code and create something fun, weird, or just super nerdy.

---

### 🧮 1. Dice Frequency Analyzer

Roll a die 100,000 times. Plot the results (text or chart). Prove your die is fair.

Bonus: allow users to test custom-sided dice (e.g., 3-sided, 100-sided, D20, etc.)

---

### 🧠 2. Guess the Dice

- The program picks a number between 2 and 12.
- You roll two dice and try to guess if you’ll match.
- Track how close you were and let students play against each other.

---

### 💣 3. C++ Yahtzee Mini

- Simulate 5 dice rolls.
- Let users reroll specific dice (store state).
- Score based on Yahtzee rules.

Just don’t get sued. Call it _Yah-T-See_ if you're paranoid.

---

### 🔁 4. Dice War

- Two players roll a die each round.
- Highest die wins the round.
- Best of 7 or 11 wins the game.
- Tie = rematch round.

Simple enough to implement. Brutal enough to be fun.

---

### 🔢 5. Dice Pattern Match

- Let users choose a pattern (e.g., “Roll three 6s”).
- Roll dice until the pattern is met.
- Track number of attempts. Add stats.

Great for demonstrating randomness and patience.

---

## 🔧 Sample Output (Basic Frequency Table)

```
Simulating 100000 rolls of a 6-sided die...

Face | Frequency
----------------
  1  | 16555
  2  | 16572
  3  | 16710
  4  | 16788
  5  | 16545
  6  | 16830
```

You can get fancier with text bars or even export to CSV.

---

## 💬 Thought Starters

- What happens if a die isn't “fair”? How would you prove that?
- Could you simulate two dice and calculate the probability of each total?
- How would you simulate loaded dice?
- What’s the lowest number of sides a die can have? (3D printing fans — show us!)

---

## 🔥 Want to Go Big?

- Simulate **risk battles** with 3v2 dice rolls
- Build a **turn-based dice combat system** (RPG style)
- Create a **dice-based board game** in terminal or with simple GUI
- Add **sound effects** or **ASCII animations** when you roll

---

## ✅ Final Tip

Dice are sneaky teachers. They help you learn:

- Classes and encapsulation
- Random number generation
- Data analysis and histograms
- Game loops and input handling

…while tricking you into thinking you’re just goofing off. So roll with it.
