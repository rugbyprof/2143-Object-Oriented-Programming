#pragma once

#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

#include "Card.hpp"
#include "Hand.hpp"

// Draws one card. Lives here because HandView is its main user.
ftxui::Element renderCard(const Card& card);

class HandView {
private:
    const Hand& hand;
    int selectedCard = 0;

public:
    HandView(const Hand& h);

    int selectedIndex() const;
    void resetSelection();

    bool handleEvent(ftxui::Event event);

    ftxui::Element render() const;

    std::string selectedCardName() const;

    ftxui::Component attach(ftxui::Component child);
};
