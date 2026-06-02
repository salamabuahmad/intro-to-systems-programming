#ifndef WELL_H
#define WELL_H
#include "Card.h"

class Well : public Card{
public:
    Well();
    void applyEncounter(PlayerPtr& player) const override;
};

#endif //WELL_H
