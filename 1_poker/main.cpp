#include <iostream>
#include "card.h"
#include "deck.h"

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
    std::cout << "Picking up " << pickNum << " cards:" << std::endl;
    for (int i = 0; i < pickNum; ++i) {
        Card *c = deck.pickOneCard();
        if (c)
            std::cout << c->toString() << std::endl;
        else
            std::cout << "There's no card in the deck" << std::endl;
    }
    return 0;
}
