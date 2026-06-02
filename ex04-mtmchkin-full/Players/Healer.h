#ifndef HEALER_H
#define HEALER_H

#include "Player.h"

class Healer: public Player{
public:
    explicit Healer(std::string);
    void heal(int givenHealth) override;
};



#endif //HEALER_H
