#include "deck.h"

// shuffles the cards in the deck
void Deck::shuffle() {

    srand(time(NULL));
    for (int i = mCards.size() - 1; i > 0; --i) {
        // pick up a random index from 0 to i
        int rand_i = rand() % (i + 1);
        std::swap(mCards[i], mCards[rand_i]);
    }
}

// pick up one card at the top of the deck
Card* Deck::pickOneCard() {

    if (!mCards.empty()) {
        Card* top = mCards.back();
        mCards.pop_back();
        return top;
    }
    else
        return nullptr;
}

// generate cards in the deck
Deck::Deck() {
    generateDefaultCards();
}

// delete all cards
Deck::~Deck() {
    for (auto &c : mCards)
        delete c;
}

// generate standard 52 poker cards
void Deck::generateDefaultCards() {

    for (Suit suit = Suit::FIRST; suit != Suit::LAST; 
            suit = static_cast<Suit>(static_cast<int>(suit) + 1)) {
        for (Rank rank = Rank::FIRST; rank != Rank::LAST;
                rank = static_cast<Rank>(static_cast<int>(rank) + 1)) {

            mCards.push_back(new Card(rank, suit));
        }
    }
}

// print all the cards in the deck
void Deck::print() const {

    for (auto &c : mCards) {
        std::cout << c->toString() << " ";
    }
    std::cout << std::endl;
}

