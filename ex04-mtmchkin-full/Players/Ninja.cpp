#include "Ninja.h"

Ninja::Ninja(std::string name) : Player(std::move(name)) {
    m_type = NINJA;
}

void Ninja::addCoins(int coinsWon) {
    m_coins += 2 * coinsWon;
}