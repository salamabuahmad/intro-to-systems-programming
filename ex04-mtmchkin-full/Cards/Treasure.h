#ifndef TREASURE_H
#define TREASURE_H

#include "Card.h"

class Treasure : public Card{
public:
    Treasure();
    void applyEncounter(PlayerPtr& player) const override;
};

#endif //TREASURE_H
