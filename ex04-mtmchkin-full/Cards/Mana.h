#ifndef MANA_H
#define MANA_H

#include "Card.h"

class Mana : public Card{
public:
    Mana();
    void applyEncounter(PlayerPtr& player) const override;
};

#endif //MANA_H
