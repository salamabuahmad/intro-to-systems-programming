#ifndef DRAGON_H
#define DRAGON_H
#include "Card.h"

class Dragon : public Card{
public:
    Dragon();
    void applyEncounter(PlayerPtr& player) const override;
};





#endif //DRAGON_H
