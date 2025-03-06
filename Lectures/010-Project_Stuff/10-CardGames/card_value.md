---
title: "Determining Card Rank and Suit Using Mod and Div"
description: "A formula to compute a card's rank and suit using modular arithmetic and integer division."
---

## Card Suit and Rank

If you number a deck of 52 cards from 0 to 51, you can determine the suit and rank using the following formulas.

### Rank:

$\text{rank} = n \mod 13$

- This gives you a value from 0 to 12, which you can then map to Ace, 2, 3, …, Queen, King.
- For instance, if you want Ace to be 1, you might use $\text{rank} = (n \mod 13) + 1$ with a special case for face cards.

### Suit:

$\text{suit} = n \div 13$

- This uses integer division, yielding values from 0 to 3.
- You can then map these to the four suits, e.g., 0 = Clubs, 1 = Diamonds, 2 = Hearts, 3 = Spades.

### Example in Pseudocode

```python
def getCard(n):
    rank = n mod 13 # Remainder: 0 to 12 (adjust mapping as needed)
    suit = n div 13 # Integer division: 0 to 3
    return (rank, suit)
```

### Example Mapping

- If $n = 0$:
  - rank = $0 \mod 13 = 0$→ (could be Ace, if you decide 0 represents Ace or 1 after adjustment)
  - suit = $0 \div 13 = 0$→ Clubs
- If $n = 51$:
  - rank = $51 \mod 13 = 12$→ King (if you map 12 to King)
  - suit = $51 \div 13 = 3$→ Spades

This straightforward method lets you easily compute both the rank and suit for any card in a standard deck using just mod and div operations.
