//
//  Poker.h
//  Poker
//  Group members: Muyuan Zhang, Thomas Ford
//  Created by Laura Zhang on 8/31/22.
//

#ifndef Poker_h
#define Poker_h

#include <vector>
#include <string>

struct Card {
    int rank;
    std::string suit;
};

std::vector<Card> createDeck();

void printDeck(std::vector<Card> card_deck);

void shuffleDeck(std::vector<Card>& deck);

bool isFlush(std::vector<Card> deck);

bool isStraight(std::vector<Card> deck);

bool isStraightFlush(std::vector<Card> deck);

bool isRoyalFlush(std::vector<Card> deck);

bool isFullHouse(std::vector<Card> deck);

std::vector<Card> pickFiveCards(std::vector<Card>& deck);

std::vector<int> shuffleAndCount(std::vector<Card>& deck, int times);

#endif /* Poker_h */
