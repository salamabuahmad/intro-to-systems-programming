#ifndef PLAYER_H
#define PLAYER_H
#include "iostream"
#include <string>

#define NORMAL "Normal"
#define NINJA "Ninja"
#define WARRIOR "Warrior"
#define HEALER "Healer"

class Player{
protected:
    std::string m_name;
    std::string m_type;
    int m_level;
    int m_force;
    int m_HP;
    int m_maxHP;
    int m_coins;

public:
    explicit Player(std::string name);
    Player(const Player&) = default;
    Player() = default;
    ~Player() = default;
    Player& operator=(const Player&) = default;
    void levelUp();
    int getLevel() const;
    int getHP() const;
    void buff(int givenForce);
    virtual void heal(int givenHealth);
    void damage(int damageTaken);
    bool isKnockedOut() const;
    virtual void addCoins(int coinsWon);
    bool pay(int payment);
    virtual int getAttackStrength();
    void levelDown(int n = 1);
    std::string getName();
    std::string getType();
    int getCoins() const;


    friend std::ostream& operator<<(std::ostream& os, const Player& object);

};















#endif //PLAYER_H
