#include "Mtmchkin.h"
#include <iostream>


#define MAX_LEVEL 10

Mtmchkin::Mtmchkin(const char *playerName, Card *cardsArray, int numOfCards) : m_player(playerName) {
    for (int i = 0; i < numOfCards; i++)
        this->m_cardsArray[i] = cardsArray[i];
    this->m_numOfCards = numOfCards;
    this->m_currentStatus = GameStatus::MidGame;
    this->m_currentCard = -1;
}
Mtmchkin::~Mtmchkin() {
    delete[] m_cardsArray;
}

Mtmchkin& Mtmchkin::operator=(const Mtmchkin& other) {
    if (this == &other) {
        return *this;
    }

    m_player = other.m_player;
    delete[] m_cardsArray;
    m_numOfCards = other.m_numOfCards;
    m_cardsArray = new Card[m_numOfCards];
    for (int i = 0; i < m_numOfCards; ++i) {
        m_cardsArray[i] = other.m_cardsArray[i];
    }

    m_currentStatus = other.m_currentStatus;
    m_currentCard = other.m_currentCard;

    return *this;
}


void Mtmchkin::playNextCard() {
    m_currentCard++;
    if (m_currentCard == m_numOfCards) {
        m_currentCard = 0;
    }
    m_cardsArray[m_currentCard].printInfo();
    m_cardsArray[m_currentCard].applyEncounter(m_player);
    m_player.printInfo();
    if (m_player.getLevel() == MAX_LEVEL) {
        m_currentStatus = GameStatus::Win;
    }
    if (m_player.isKnockedOut()) {
        m_currentStatus = GameStatus::Loss;
    }
}
bool Mtmchkin::isOver() const {
    if (m_currentStatus != GameStatus::MidGame) {
        return true;
    }
    return false;
}
GameStatus Mtmchkin::getGameStatus() const {
    return m_currentStatus;
}