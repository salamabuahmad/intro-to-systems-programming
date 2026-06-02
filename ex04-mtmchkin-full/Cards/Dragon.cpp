#include "Dragon.h"

Dragon::Dragon() : Card(){
    m_type = "Dragon";
    m_force = 25;
    m_loot = 1000;
    m_hpLossOnDefeat = MAX_HP;
}



void Dragon::applyEncounter(PlayerPtr &player) const {
    if(player->getAttackStrength() >= m_force){
        player->levelUp();
        player->addCoins(m_loot);
        printWinBattle(player->getName(),m_type);
        return;
    }
    player->damage(m_hpLossOnDefeat);
    printLossBattle(player->getName(),m_type);
}
