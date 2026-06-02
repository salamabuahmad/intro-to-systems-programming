#ifndef WITCH_H
#define WITCH_H
#include "Card.h"

class Witch : public Card{
public:
    Witch();
    void applyEncounter(PlayerPtr& player) const override;
};



#endif //WITCH_H
