#include <iostream>
#include "card.h"
#include "deck.h"

void pickNCards(Deck &deck, const int &n);

int main(int argc, const char *argv[])
{
    // generating a deck
    Deck deck = Deck(); 

    std::cout << "Before shuffling:" << std::endl;
    deck.print();

    // shuffing
    deck.shuffle();
    std::cout << "After shuffling:" << std::endl;
    deck.print();

    // picking up cards from the deck
    const int pickNum = 5;
    pickNCards(deck, pickNum);

    return 0;
}

// pick up n cards from the deck
void pickNCards(Deck &deck, const int &n) {
    std::cout << "Picking up " << n << " cards:" << std::endl;
    for (int i = 0; i < n; ++i) {
        Card *c = deck.pickOneCard();
        if (c)
            std::cout << c->toString() << std::endl;
        else
            std::cout << "There's no card in the deck" << std::endl;
    }
}
