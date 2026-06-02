#include "Barfight.h"

Barfight::Barfight(): Card() {
    m_type = "Barfight";
    m_hpLossOnDefeat = 10;
}

void Barfight::applyEncounter(PlayerPtr &player) const {
    if(player->getType() != "Warrior"){
        player->damage(m_hpLossOnDefeat);
    }
    printBarfightMessage(player->getType() == "Warrior");
}

