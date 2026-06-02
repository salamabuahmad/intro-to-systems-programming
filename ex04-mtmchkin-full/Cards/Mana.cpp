#include "Mana.h"

Mana::Mana() : Card(){
    m_type = "Mana";
    m_heal = 10;
}

void Mana::applyEncounter(PlayerPtr &player) const {
    if(player->getType() == "Healer"){
        player->heal(m_heal);
    }
    printManaMessage(player->getType() == "Healer");
}


