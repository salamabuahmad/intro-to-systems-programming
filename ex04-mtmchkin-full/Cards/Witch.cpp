#include "Witch.h"

Witch::Witch() : Card(){
    m_type = "Witch";
    m_force = 11;
    m_loot = 2;
    m_buff = -1;
    m_hpLossOnDefeat = 10;
}



void Witch::applyEncounter(PlayerPtr& player) const {
    if(player->getAttackStrength() >= m_force){
        player->levelUp();
        player->addCoins(m_loot);
        printWinBattle(player->getName(),m_type);
        return;
    }
    player->buff(m_buff);
    player->damage(m_hpLossOnDefeat);
    printLossBattle(player->getName(),m_type);
}
