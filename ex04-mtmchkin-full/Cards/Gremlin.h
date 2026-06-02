#ifndef GREMLIN_H
#define GREMLIN_H

#include "Card.h"

class Gremlin : public Card{
public:
    Gremlin();
    void applyEncounter(PlayerPtr &player) const override;
};


#endif //GREMLIN_H
