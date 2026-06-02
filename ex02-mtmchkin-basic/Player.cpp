#include "Player.h"
#include "utilities.h"

Player :: Player(const char* name , int maxHP , int force)
{
    level = 1;
    coins = 0;

    if(maxHP <= 0)
    {
        this -> maxHP = 100;
    }
    else
    {
        this -> maxHP = maxHP;
    }

    HP = this -> maxHP;

    if(force < 0)
    {
        force = 5;
    }
    else
    {
        this -> force = force;
    }

    this -> name = name;
}

void Player:: levelUp()
{
    if(this -> level == 10)
    {
        return;
    }
    this -> level += 1;
}

int Player:: getLevel()
{
    return (this -> level);
}

void Player:: buff(int givenForce)
{
    this -> force += givenForce;
}

void Player:: heal(int givenHealth)
{
    if(this -> HP == maxHP || givenHealth < 0)
    {
        return;
    }

    if(this -> HP + givenHealth <= maxHP)
    {
        this -> HP += givenHealth;
    }

    else
    {
        this -> HP = maxHP;
    }
}

void Player:: damage(int damageTaken)
{
    if(damageTaken < 0)
    {
        return;
    }

    if(this -> HP <= damageTaken)
    {
        this -> HP = 0;
    }

    else
    {
        this -> HP -= damageTaken;
    }
}

bool Player:: isKnockedOut()
{
    if(HP > 0)
    {
        return false;
    }

    return true;
}

void Player:: addCoins(int coinsWon)
{
    this -> coins += coinsWon;
}

bool Player:: pay(int payment)
{
    if(this -> coins >= payment)
    {
        this -> coins -= payment;
        return true;
    }

    return false;
}

int Player:: getAttackStrength()
{
    return (this -> level + this -> force);
}
void Player::printInfo() {
    printPlayerInfo(name,level,force,HP,coins);
}