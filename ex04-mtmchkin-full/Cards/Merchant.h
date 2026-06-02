#ifndef MERCHANT_H
#define MERCHANT_H

#include "Card.h"

class Merchant : public Card{
public:
    Merchant();
    void applyEncounter(PlayerPtr &player) const override;
};


#endif //MERCHANT_H
