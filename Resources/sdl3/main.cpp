#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <iomanip>
#include <random>
#include <sstream>
#include <unordered_map>

vector<string> Rank = {"",     "Two",   "Three", "Four", "Five",
                       "Six",  "Seven", "Eight", "Nine", "Ten",
                       "Jack", "Queen", "King",  "Ace"};
vector<string> Suit = {"Clubs", "Diamonds", "Hearts", "Spades"};

////////////////////////////////////////////////////////////////////////////////////

std::map<int, std::string> rankName = {
    {2, "2"}, {3, "3"},   {4, "4"},  {5, "5"},  {6, "6"},  {7, "7"}, {8, "8"},
    {9, "9"}, {10, "10"}, {11, "J"}, {12, "Q"}, {13, "K"}, {14, "A"}};

std::map<int, std::string> suitName = {{0, "♣"}, {1, "♦"}, {2, "♥"}, {3, "♠"}};

////////////////////////////////////////////////////////////////////////////////////

/*****************************************************************
   ___   _   ___ ___     ___ _      _   ___ ___
  / __| /_\ | _ \   \   / __| |    /_\ / __/ __|
 | (__ / _ \|   / |) | | (__| |__ / _ \\__ \__ \
  \___/_/ \_\_|_\___/   \___|____/_/ \_\___/___/
*****************************************************************/
class Card {
private:
  int value; // 0-51

public:
  Card(int value = 0);

  int getValue() const;
  int getRank() const;
  int getSuit() const;

  std::string getRankName() const;
  std::string getSuitName() const;
  //   std::string toString() const;
};

string Card::getRankName() const { return Rank[getRank()]; }
string Card::getSuitName() const { return Suit[getSuit()]; }

Card::Card(int v) { value = v; }

int Card::getRank() const { return value % 13; }

int Card::getSuit() const { return value / 13; }

int Card::getValue() const { return value; }

/*****************************************************************
  ___  ___ ___ _  __   ___ _      _   ___ ___
 |   \| __/ __| |/ /  / __| |    /_\ / __/ __|
 | |) | _| (__| ' <  | (__| |__ / _ \\__ \__ \
 |___/|___\___|_|\_\  \___|____/_/ \_\___/___/
******************************************************************/

class Deck {
private:
  std::vector<Card> deck;

  void genCards() {
    for (int i = 0; i < 52; i++) {
      deck.push_back(Card(i));
    }
  }

public:
  Deck(bool shuffle = 0);

  void shuffle();
  Card deal();
  bool empty() const;
  int size() const;
};

Deck::Deck(bool shuffle = 0) {
  genCards();
  if (shuffle) {
    shuffle();
  }
}

void Deck::shuffle() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::shuffle(deck.begin(), deck.end(), gen);
}

Card Deck::deal() {
  Card card = deck.back();
  deck.pop_back();
  return card;
}

bool Deck::empty() const { return deck.size() == 0; }
int Deck::size() const { return deck.size(); }

///////////////////////////////////////////////////////////////////////////

int main() {

  Deck deck(1);

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("SDL3 Cards", 800, 600, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

  int cardIndex = getRandomNumber(0, 51);

  // Load image directly into a GPU texture
  SDL_Texture *card = IMG_LoadTexture(renderer, "./png/00.png");

  if (!card) {
    SDL_Log("Could not load image: %s", SDL_GetError());
    return 1;
  }

  bool running = true;

  while (running) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        running = false;
    }

    // Clear background
    SDL_SetRenderDrawColor(renderer, 20, 100, 40, 255);
    SDL_RenderClear(renderer);

    // Destination rectangle
    SDL_FRect dest = {
        100.0f, // x
        100.0f, // y
        150.0f, // width
        210.0f  // height
    };

    SDL_RenderTexture(renderer, card,
                      nullptr, // entire source image
                      &dest);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(card);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}