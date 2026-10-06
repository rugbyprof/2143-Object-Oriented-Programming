```yaml
topic: "52-Card Deck in C++"
focus: "Class structure"
level: "OOP teaching example"
recommendation: "Card + Deck first; Hand later"
```

Poker is a **really good C++ OOP example** showing composition. Below is a breakdown of a set of classes to implement the start of a poker game.

```text
Card
Deck
Hand       ← add later
Player     ← add much later, if needed
Game       ← only when there is actually a game
```

The important relationship is **composition**:

> A `Deck` **has 52 Cards**.

## 1. `Card` class

I'd let `Card` store the integer `0–51`, precisely because you get to preserve your `/ 13` and `% 13` trick.

```cpp
class Card {
private:
    int value;              // 0-51

public:
    Card(int value = 0);

    int getValue() const;
    int getRank() const;
    int getSuit() const;

    std::string getRankName() const;
    std::string getSuitName() const;
    std::string toString() const;
};
```

Implementation:

```cpp
int Card::getRank() const {
    return value % 13;
}

int Card::getSuit() const {
    return value / 13;
}
```

That's a beautiful little class for beginning OOP because the **internal representation is hidden**.

The user doesn't need to know that:

```cpp
card.getSuit()
```

is actually:

```cpp
value / 13
```

That's encapsulation without having to give you a 47-slide PowerPoint about encapsulation.

---

# 2. `Deck` class

Then the deck contains cards:

```cpp
class Deck {
private:
    std::vector<Card> cards;

public:
    Deck();

    void shuffle();
    Card deal();
    bool empty() const;
    int size() const;
};
```

Constructor:

```cpp
Deck::Deck() {
    for (int i = 0; i < 52; i++) {
        cards.push_back(Card(i));
    }
}
```

Now you have:

```text
Deck
 │
 └── vector<Card>
       │
       ├── Card(0)
       ├── Card(1)
       ├── Card(2)
       ├── ...
       └── Card(51)
```

This is a fantastic example of:

> **Deck HAS-A Card**

rather than inheritance.

A `Deck` isn't a `Card`, so:

```cpp
class Deck : public Card
```

Inheriting would be complete nonsense. This example reinforces **composition vs. inheritance**. In this case composition (a `deck` has `cards`).

---

# 3. Shuffle

With modern C++:

```cpp
void Deck::shuffle() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::shuffle(cards.begin(), cards.end(), gen);
}
```

This is a good example of using STL's built in power. 

---

# 4. Deal

The simplest version:

```cpp
Card Deck::deal() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}
```

Which introduces another useful idea:

```text
Deck before:

[A][B][C][D][E]
             ↑
            back()

deal()

[A][B][C][D]

returns E
```

No need to randomly select a card when dealing if you've already shuffled the deck.

That's another nice algorithmic discussion:

> **Shuffle once, then remove cards.**

rather than:

> Randomly generate cards repeatedly and figure out how not to deal duplicates.

---

# 5. `Hand` class

Once `Card` and `Deck` work:

```cpp
class Hand {
private:
    std::vector<Card> cards;

public:
    void addCard(const Card& card);
    void clear();

    int size() const;

    void show() const;
};
```

Now you've got two classes containing cards:

```text
              Card
             /    \
            /      \
           ▼        ▼
        Deck       Hand
          │          │
     vector<Card> vector<Card>
```

But importantly:

**Neither inherits from `Card`.**

They're both containers **of Cards**.

Again, this is  a really nice example of composition.

---

# 6. Clean Interactions

Our program starts looking like:

```cpp
int main() {

    Deck deck;
    Hand player;

    deck.shuffle();

    player.addCard(deck.deal());
    player.addCard(deck.deal());
    player.addCard(deck.deal());
    player.addCard(deck.deal());
    player.addCard(deck.deal());

    player.show();

    return 0;
}
```

Which is remarkably readable.

Even a weak programmer can pretty much tell you what that program does.

---

# 7. Redo

Here's a **great OOP progression** starting from the beginning:

We start with:

```cpp
int card = 37;

int suit = card / 13;
int rank = card % 13;
```

Then:

### Stage 1 — Procedural

```cpp
int getSuit(int card);
int getRank(int card);
string getCardName(int card);
```

Deck:

```cpp
vector<int> deck;
```

This is the functions-and-containers version.

Then ask:

> We're passing these integers around everywhere. What actually **is** a card?

---

### Stage 2 — `Card`

Turn:

```cpp
int card;
```

into:

```cpp
Card card;
```

Now:

```cpp
card.getRank();
card.getSuit();
card.toString();
```

Boom: encapsulation.

---

### Stage 3 — `Deck`

Instead of:

```cpp
vector<Card> deck;
```

floating around in `main()`:

```cpp
Deck deck;
```

Now:

```cpp
deck.shuffle();
deck.deal();
deck.size();
```

Boom: composition.

---

### Stage 4 — `Hand`

Add:

```cpp
Hand hand;
```

Now:

```cpp
hand.addCard(deck.deal());
```

More composition.

---

### Stage 5 — Poker-ish behavior

Now we get cards, deck, and hand. Let's introduce some poker behavior:

```cpp
bool hasPair() const;
bool hasTwoPair() const;
bool hasThreeOfKind() const;
bool hasFlush() const;
bool hasStraight() const;
```

And now you have an actual algorithmic problem to solve using our objects.

---

# Adding `enum class`

Let's improve `Card` with enums:

```cpp
enum class Suit {
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

enum class Rank {
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};
```

Then:

```cpp
class Card {
private:
    int value;

public:
    Card(int value);

    Rank getRank() const;
    Suit getSuit() const;

    std::string toString() const;
};
```

Internally we can **still use the beautiful 0–51 encoding**.

Conceptually:

```text
                  Card
              ┌───────────┐
              │ value: 27 │
              └─────┬─────┘
                    │
          ┌─────────┴─────────┐
          │                   │
       value / 13          value % 13
          │                   │
          ▼                   ▼
      Suit::Hearts         Rank::Two
```

This is a particularly nice demonstration of **abstraction**:

> Internally, the card is just an integer.
>
> Externally, the class presents meaningful concepts like `Suit`, `Rank`, and `toString()`.

We looked at poker using this progression: **`int` → functions → `Card` → `Deck` → `Hand`**. Each new class solves a problem the you have already experienced. So, again, repeat repeat repeat until you start to get it. 