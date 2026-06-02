#include "Healer.h"


Healer::Healer(std::string name) : Player(std::move(name)) {
    m_type = HEALER;
}

void Healer::heal(int givenHealth) {
    if(m_HP + 2 * givenHealth >= m_maxHP){
        m_HP = m_maxHP;
    }
    else{
        m_HP += 2 * givenHealth;
    }
}