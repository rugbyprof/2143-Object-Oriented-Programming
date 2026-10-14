#include "HandView.hpp"
#include <vector>
using namespace ftxui;
namespace {
    std::string shortRank(const Card& card) {
        const std::string ranks = "A23456789TJQK";
        return std::string(1, ranks[card.getRank()]);
    }
    std::string suitSymbol(const Card& card) {
        static const std::vector<std::string> suits = {
            "♣",
            "♦",
            "♥",
            "♠"};
        return suits[card.getSuit()];
    }
} // namespace
Element renderCard(const Card& card) {
    std::string rank = shortRank(card);
    std::string suit = suitSymbol(card);
    bool isRed = card.getSuit() == 1 || card.getSuit() == 2;
    auto face = vbox({
                    text(rank),
                    filler(),
                    text(suit) | center,
                    filler(),
                    text(rank) | align_right,
                }) |
                size(WIDTH, EQUAL, 7) | size(HEIGHT, EQUAL, 5) | border;
    if (isRed) {
        return face | color(Color::Red);
    }
    return face;
}
HandView::HandView(const Hand& h)
    : hand(h) {
}
int HandView::selectedIndex() const {
    return selectedCard;
}
void HandView::resetSelection() {
    selectedCard = 0;
}
bool HandView::handleEvent(Event event) {
    if (event == Event::ArrowRight) {
        if (selectedCard + 1 < hand.size()) {
            selectedCard++;
        }
        return true;
    }
    if (event == Event::ArrowLeft) {
        if (selectedCard > 0) {
            selectedCard--;
        }
        return true;
    }
    return false;
}
Element HandView::render() const {
    Elements elements;
    for (int i = 0; i < hand.size(); i++) {
        Card card(hand.getCard(i));
        auto element = renderCard(card);
        if (i == selectedCard) {
            element = element | bgcolor(Color::Blue);
        }
        elements.push_back(element);
        elements.push_back(text(" "));
    }
    return hbox(std::move(elements));
}
std::string HandView::selectedCardName() const {
    if (hand.size() == 0) {
        return "No card selected";
    }
    Card card(hand.getCard(selectedCard));
    return card.toString();
}
Component HandView::attach(Component child) {
    return CatchEvent(child, [this](Event event) {
        return handleEvent(event);
    });
}
