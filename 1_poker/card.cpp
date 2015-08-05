#include "card.h"

// construct a card
Card::Card(const Rank &rank, const Suit &suit) : mRank(rank), mSuit(suit) {
    // throw exception if rank/suit is invalid
    if (static_cast<int>(mRank) >= MAX_RANK) 
        throw std::invalid_argument("Invalid Rank");
    else if (static_cast<int>(mSuit) >= MAX_SUIT)
        throw std::invalid_argument("Invalid Suit");
}

// convert the card to string
std::string Card::toString() const {
    return SUIT_STRINGS[static_cast<int>(mSuit)] + RANK_STRINGS[static_cast<int>(mRank)];
}


