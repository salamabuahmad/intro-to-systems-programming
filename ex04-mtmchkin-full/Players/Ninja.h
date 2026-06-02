#ifndef NINJA_H
#define NINJA_H

#include "Player.h"

class Ninja: public Player{
public:
    explicit Ninja(std::string);
    void addCoins(int coinsWon) override;
};


#endif //NINJA_H
