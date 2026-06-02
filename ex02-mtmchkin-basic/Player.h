#ifndef BV00516F_PLAYER_H
#define BV00516F_PLAYER_H
#include <string>

class Player{
    const char *name;
    int level;
    int force;
    int maxHP;
    int HP;
    int coins;

public:
    explicit Player(const char* name , int maxHP = 100, int force = 5);
    //explicit Player(const char* name);
    Player(const Player&) = default;
    ~Player() = default;
    Player &operator=(const Player &other) = default;
    void levelUp();
    int getLevel();
    void buff(int givenForce);
    void heal(int givenHealth);
    void damage(int damageTaken);
    bool isKnockedOut();
    void addCoins(int coinsWon);
    bool pay(int payment);
    int getAttackStrength();
    void printInfo();

};

#endif