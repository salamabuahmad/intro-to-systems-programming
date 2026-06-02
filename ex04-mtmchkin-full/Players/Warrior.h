#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player{
public:
    explicit Warrior(std::string);
    int getAttackStrength() override;
};



#endif //WARRIOR_H
