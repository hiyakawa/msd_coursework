//
//  Cards.h
//  Cards
//
//  Created by Laura Zhang on 8/30/22.
//

#ifndef Cards_h
#define Cards_h

#include <vector>
#include <string>

struct Card {
    int rank;
    std::string suit;
};

std::vector<Card> createCardDeck();

void deckPrinter(std::vector<Card> card_deck);

#endif /* Cards_h */
