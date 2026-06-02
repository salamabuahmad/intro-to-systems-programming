#include "Well.h"

Well :: Well() : Card(){
    m_type = "Well";
    m_hpLossOnDefeat = 10;
}

void Well::applyEncounter(PlayerPtr& player) const {
    if(player->getType() != "Ninja"){
        player->damage(m_hpLossOnDefeat);
    }
    printWellMessage(player->getType() == "Ninja");
}

