#include "Treasure.h"

Treasure::Treasure() : Card(){
    m_type = "Treasure";
    m_loot = 10;
}



void Treasure::applyEncounter(PlayerPtr& player) const {
    player->addCoins(m_loot);
    printTreasureMessage();
}
