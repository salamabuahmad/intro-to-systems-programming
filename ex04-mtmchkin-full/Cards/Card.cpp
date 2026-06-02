#include "Card.h"

std::ostream &operator<<(std::ostream &os, const Card &card) {
    printCardDetails(os,card.m_type);
    printEndOfCardDetails(os);
    if(card.m_type == "Dragon" ||card.m_type == "Gremlin" || card.m_type == "Witch"){
        printMonsterDetails(os,card.m_force,card.m_hpLossOnDefeat,card.m_loot,card.m_type == "Dragon");
    }
    return os;
}
