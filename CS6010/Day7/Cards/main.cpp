//
//  main.cpp
//  Cards
//
//  Created by Laura Zhang on 8/30/22.
//

#include "Cards.h"
#include <iostream>

using namespace std;

// create a deck of cards
vector<Card> createCardDeck() {
    vector<Card> card_deck;                                                 // create an empty vector to store the deck
    vector<string> suits = {"Hearts", "Spades", "Clubs", "Diamonds"};       // create a vector to store the suits
    
    Card cur_card;                                                          // create an empty card
    
    for (int i = 0; i < 4; i++) {                                           // 4 types of suits
        for (int j = 1; j < 14; j++) {                                      // 13 types of ranks
            cur_card.suit = suits[i];                                       // assign the card a suit
            cur_card.rank = j;                                              // assign the card a rank
            
            card_deck.push_back(cur_card);                                  // push the current card into the deck
        }
    }
    
    return card_deck;
}

// print the deck
void deckPrinter(vector<Card> card_deck) {
    string ace = "A";
    string jack = "J";
    string queen = "Q";
    string king = "K";
    
    for (Card card : card_deck) {
        // rank 2 to 10 can be printed directly
        if (card.rank > 1 && card.rank < 11) {
            cout << card.suit << ", " << card.rank << endl;
        }
        
        else if (card.rank == 1) {
            cout << card.suit << ", " << ace << endl;
        }
        
        else if (card.rank == 11) {
            cout << card.suit << ", " << jack << endl;
        }
        
        else if (card.rank == 12) {
            cout << card.suit << ", " << queen << endl;
        }
        
        else if (card.rank == 13) {
            cout << card.suit << ", " << king << endl;
        }
        
        else {
            cerr << "Ranking of the card is out of range!" << endl;
        }
    }
}

int main(int argc, const char * argv[]) {
    // create and print a card deck
    deckPrinter(createCardDeck());
    
    return 0;
}
