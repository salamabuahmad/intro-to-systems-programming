#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_

#include <string>
#include <queue>
#include <memory>
#include <vector>

#include "Cards/Card.h"
#include "Players/Player.h"
#include "Cards/Barfight.h"
#include "Cards/Dragon.h"
#include "Cards/Gremlin.h"
#include "Cards/Mana.h"
#include "Cards/Merchant.h"
#include "Cards/Treasure.h"
#include "Cards/Well.h"
#include "Cards/Witch.h"

#include "Players/Healer.h"
#include "Players/Ninja.h"
#include "Players/Warrior.h"
#include "Players/Player.h"

using std::queue;
using std::unique_ptr;
using std::string;
using std::cin;
using std::cerr;
using std::endl;
using std :: vector;


typedef unique_ptr<Card> CardPtr;
typedef unique_ptr<Player> PlayerPtr;

class Mtmchkin{
private:
    queue<CardPtr> m_cardSet;
    queue<PlayerPtr> m_playerSet;
    int m_playersNum;
    int m_numOfRounds;
    vector <PlayerPtr> m_winners;
    vector <PlayerPtr> m_dead;

    void UpdateGame();

public:

    /*
    * C'tor of Mtmchkin class
    *
    * @param filename - a file which contains the cards of the deck.
    * @return
    *      A new instance of Mtmchkin.
    */
    explicit Mtmchkin(const std::string &fileName);

    /*
    * Play the next Round of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void playRound();

    /*
    * Prints the leaderBoard of the game at a given stage of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void printLeaderBoard() ;

    /*
    *  Checks if the game ended:
    *
    *  @return
    *          True if the game ended
    *          False otherwise
    */
    bool isGameOver() const;

    /*
    *  Returns the number of rounds played.
    *
    *  @return
    *          int - number of rounds played
    */
    int getNumberOfRounds() const;

};




#endif /* MTMCHKIN_H_ */
