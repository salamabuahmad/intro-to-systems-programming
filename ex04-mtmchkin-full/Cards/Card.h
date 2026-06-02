#ifndef CARD_H
#define CARD_H

#define MAX_HP 100

#include <string>
#include <memory>
#include "../utilities.h"
#include "../Players/Player.h"

using std::unique_ptr;

typedef unique_ptr<Player> PlayerPtr;

class Card{
protected:
    std::string m_type; // can be a Gremlin, which, dragon, merchant, treasure, well ,barfight,  or a mana.

    int m_force;  // The force
    int m_loot; // The profit you get when winning a battle or when getting a "Treasure" card
    int m_hpLossOnDefeat; // The amount of hp you lose when losing the battle

    int m_cost; // The cost of a "Buff/Heal" card
    int m_heal; // The amount of HP you get when buying a "HEAL" card
    int m_buff; // force increse

public:
    Card():m_force(0), m_loot(0), m_hpLossOnDefeat(0), m_cost(0),m_heal(0), m_buff(0){};
    virtual void applyEncounter(PlayerPtr& player) const {};
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    ~Card() = default;
    Card(Card& obj) = default;

};


#endif //CARD_H
