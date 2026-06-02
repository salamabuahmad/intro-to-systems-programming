#include "Warrior.h"

Warrior::Warrior(std::string name) : Player(std::move(name)){
    m_type = WARRIOR;
}

int Warrior::getAttackStrength() {
    return (m_force*2 + m_level);
}


