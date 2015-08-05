#ifndef CARD_H
#define CARD_H

#include <string>

// maximum kinds of rank and suit
const int MAX_RANK = 13;
const int MAX_SUIT = 4;

// card's rank and suit enums
// LAST and FIRST are used for enum class iteration
enum class Rank {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK,
                 QUEEN, KING, LAST, FIRST = ACE};
enum class Suit {CLUB, DIAMOND, HEART, SPADE, LAST, FIRST = CLUB};

// maps for rank/suit enums and rank/suit strings
const std::string RANK_STRINGS[MAX_RANK] = {"A", "2", "3", "4", "5", "6", "7",
                                           "8", "9", "10", "J", "Q", "K"};
const std::string SUIT_STRINGS[MAX_SUIT] = {"C", "D", "H", "S"};

// a poker card with rank and suit
class Card {
private:
    Rank mRank; // rank of the card
    Suit mSuit; // suit of the card   
public:
    explicit Card(const Rank &rank, const Suit &suit);  // construct a card
    std::string toString() const;                       // convert the card to string
};

#endif
