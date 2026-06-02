#ifndef BARFIGHT_H
#define BARFIGHT_H

#include "Card.h"

class Barfight : public Card{
public:
    Barfight();
    void applyEncounter(PlayerPtr &player) const override;
};

#endif //BARFIGHT_H
