#include "Gremlin.h"

Gremlin::Gremlin(): Card(){
    m_type = "Gremlin";
    m_force = 5;
    m_loot = 2;
    m_hpLossOnDefeat = 10;
}



void Gremlin::applyEncounter(PlayerPtr& player) const {
    if(player->getAttackStrength() >= m_force){
        player->levelUp();
        player->addCoins(m_loot);
        printWinBattle(player->getName(),m_type);
        return;
    }
    player->damage(m_hpLossOnDefeat);
    printLossBattle(player->getName(),m_type);
}
