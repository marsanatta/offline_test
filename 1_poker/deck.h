#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "card.h"

// a poker deck containing poker cards
class Deck {
private:
    std::vector<Card*> mCards;    // cards collection
    void generateDefaultCards(); // generate stardard 52 poker cards
public:
    explicit Deck();       // generate cards in the deck
    ~Deck();               // delete all cards
    void print() const;    // print all the cards in the deck
    void shuffle();        // shuffle the cards in the deck
    Card* pickOneCard();   // pick up one card at the top of the deck
};

#endif 
