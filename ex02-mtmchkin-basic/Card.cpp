#include "Card.h"

Card::Card(CardType type, const CardStats &stats) {
    this->m_effect = type;
    this->m_stats = stats;
}

void Card::applyEncounter(Player &player) const {
    if (this->m_effect == CardType::Buff) {
        if (player.pay(this->m_stats.cost)) {
            player.buff(this->m_stats.buff);
        }
    }
    if (this->m_effect == CardType::Battle) {
        if (player.getAttackStrength() >= this->m_stats.force) {
            player.levelUp();
            player.addCoins(this->m_stats.loot);
            printBattleResult(true);
        } else {
            player.damage(this->m_stats.hpLossOnDefeat);
            printBattleResult(false);
        }
    }

    if (this->m_effect == CardType::Heal) {
        if (player.pay(this->m_stats.cost)) {
            player.heal(this->m_stats.heal);
        }
    }

    if (this->m_effect == CardType::Treasure) {
        player.addCoins(this->m_stats.loot);
    }
}

void Card::printInfo() const {
    if (this->m_effect == CardType::Buff) {
        printBuffCardInfo(this->m_stats);
    }

    if (this->m_effect == CardType::Battle) {
        printBattleCardInfo(this->m_stats);
    }

    if (this->m_effect == CardType::Heal) {
        printHealCardInfo(this->m_stats);
    }
    if (this->m_effect == CardType::Treasure) {
        printTreasureCardInfo(this->m_stats);
    }
}