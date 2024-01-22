//
//  main.cpp
//  Poker
//  Group members: Muyuan Zhang, Thomas Ford
//  Created by Laura Zhang on 8/31/22.
//

/*
 1,000,000 times of shuffing:
 Flush:          0.1904%
 Straight:       0.4026%
 Straight Flush: 0.0013%
 Royal Flush:    0.0002%
 Full House:     0.1455%
 */

#include "Poker.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char * argv[]) {
    // change the seed for rand()
    srand(time(NULL));
    
    // create some test "decks" which contain only 5 cards
    Card card_1 = {1, "Spades"};
    Card card_2 = {2, "Spades"};
    Card card_3 = {3, "Spades"};
    Card card_4 = {4, "Spades"};
    Card card_5 = {5, "Spades"};
    Card card_6 = {10, "Spades"};
    Card card_7 = {11, "Spades"};
    Card card_8 = {12, "Spades"};
    Card card_9 = {13, "Spades"};
    Card card_10 = {1, "Hearts"};
    Card card_11 = {1, "Diamonds"};
    Card card_12 = {2, "Diamonds"};
    Card card_13 = {3, "Hearts"};
    Card card_14 = {3, "Diamonds"};
    
    vector<Card> straightFlush = {card_5, card_4, card_3, card_2, card_1};
    vector<Card> fullHouse = {card_2, card_3, card_12, card_13, card_14};
    vector<Card> royalFlush = {card_6, card_7, card_8, card_9, card_1};
    vector<Card> straight = {card_3, card_4, card_5, card_11, card_12};
    vector<Card> flush = {card_2, card_3, card_4, card_5, card_6};
    
    // cout << isStraightFlush(straightFlush) << isFullHouse(fullHouse) << isStraight(royalFlush);
    // cout << isRoyalFlush(royalFlush) << isStraight(straight) << isFlush(flush) << endl;
    // expecting "111111"
    
    vector<Card> deck = createDeck();
    // deckPrinter(deck);
    
    cout << "Enter the times to shuffle the card deck:" << endl;
    int times;
    cin >> times;
    
    while (times < 1) {
        // print error message if shuffling time is less than 1
        cout << "Please enter a positive integer." << endl;
        cout << "Enter the times to shuffle the card deck:" << endl;
        cin >> times;
    }

    vector<int> shuffled_hand = shuffleAndCount(deck, times);

    cout << "Flush:          " << shuffled_hand[0] * 100.0 / times << "%" << endl;
    cout << "Straight:       " << shuffled_hand[1] * 100.0 / times << "%" << endl;
    cout << "Straight Flush: " << shuffled_hand[2] * 100.0 / times << "%" << endl;
    cout << "Royal Flush:    " << shuffled_hand[3] * 100.0 / times << "%" << endl;
    cout << "Full House:     " << shuffled_hand[4] * 100.0 / times << "%" << endl;
    
    return 0;
}
