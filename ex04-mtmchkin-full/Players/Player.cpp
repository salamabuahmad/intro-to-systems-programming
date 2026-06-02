#include "Player.h"
#include "../utilities.h"

Player::Player(std::string name){
    m_name = std::move(name);
    m_level = 1;
    m_coins = 10;
    m_force = 5;
    m_maxHP = 100;
    m_HP = m_maxHP;
    m_type = NORMAL;
}

void Player::levelUp() {
    if(m_level == 10) {
        return;
    }
    m_level++;
}

int Player::getLevel() const {
    return m_level;
}

void Player::buff(int givenForce) {
    m_force += givenForce;
    if(m_force < 0)
        m_force = 0;
}

void Player :: heal(int givenHealth){
    if(m_HP + givenHealth >= m_maxHP){
        m_HP = m_maxHP;
    }
    else{
        m_HP += givenHealth;
    }
}

void Player::damage(int damageTaken) {
    if(m_HP - damageTaken <= 0){
        m_HP = 0;
    }
    else{
        m_HP -= damageTaken;
    }
}

bool Player::isKnockedOut() const {
    return m_HP <= 0;
}

void Player::addCoins(int coinsWon) {
    m_coins += coinsWon;
}

bool Player::pay(int payment) {
    if(m_coins >= payment){
        m_coins -= payment;
        return true;
    }

    return false;
}

int Player::getAttackStrength() {
    return m_level + m_force;
}

void Player::levelDown(int n) {
    m_level -= n;
}

std::string Player::getName() {
    return m_name;
}

std::string Player::getType() {
    return m_type;

}

int Player::getCoins() const {
    return m_coins;
}

int Player ::getHP() const {
    return m_HP;
}


std::ostream& operator<<(std::ostream& os, const Player& object){
    printPlayerDetails(os,object.m_name,object.m_type,object.m_level,object.m_force,object.m_HP,object.m_coins);
    return os;
}
