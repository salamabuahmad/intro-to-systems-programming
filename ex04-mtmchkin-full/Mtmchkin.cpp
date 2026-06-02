#include "Mtmchkin.h"
#include "fstream"
#include "Exception.h"
#include <list>

std::list<string> jobs = {"Healer", "Ninja", "Warrior"};

void BuildQueue(std::ifstream *deck, queue<unique_ptr<Card>> &cardSet) {
    char line[256];
    int counter = 0;

    while (deck->getline(line, sizeof(line))) {
        counter++;
        unique_ptr<Card> card = unique_ptr<Card>(new Card());
        if (strcmp(line, "Barfight") == 0) {
            card = unique_ptr<Card>(new Barfight());
        } else if (strcmp(line, "Dragon") == 0) {
            card = unique_ptr<Card>(new Dragon());
        } else if (strcmp(line, "Gremlin") == 0) {
            card = unique_ptr<Card>(new Gremlin());
        } else if (strcmp(line, "Mana") == 0) {
            card = unique_ptr<Card>(new Mana());
        } else if (strcmp(line, "Merchant") == 0) {
            card = unique_ptr<Card>(new Merchant());
        } else if (strcmp(line, "Treasure") == 0) {
            card = unique_ptr<Card>(new Treasure());
        } else if (strcmp(line, "Well") == 0) {
            card = unique_ptr<Card>(new Well());
        } else if (strcmp(line, "Witch") == 0) {
            card = unique_ptr<Card>(new Witch());
        } else {
            throw DeckFileFormatError(counter);

        }
        cardSet.push(std::move(card));
    }

    if (counter < 5) {
        throw DeckFileInvalidSize();
    }
}

bool checkEnglishLetters(const string &word) {
    for (char i: word) {
        if (!std::isalpha(i)) {
            return false;
        }
    }
    return true;
}

bool checkInvalidName(const string &name) {
    if (name.size() > 15 || !checkEnglishLetters(name)) {
        printInvalidName();
        return true;
    }
    return false;
}

bool checkInvalidJob(const string &job) {
    for (const string &i: jobs) {
        if (i == job) {
            return false;
        }
    }
    printInvalidClass();
    return true;
}

bool checkInvalid(string line) { // checks if there are more words
    line.erase(0, line.find_first_not_of(' '));
    line.erase(line.find_last_not_of(' ') + 1);
    if (line.empty()) {
        return false;
    }
    printInvalidInput();
    return true;
}


void StartGame(queue<unique_ptr<Player>> &playerSet, int *playersNum) {
    printStartGameMessage();
    printEnterTeamSizeMessage();
    cin >> *playersNum;
    while (*playersNum < 2 || *playersNum > 6) {
        printInvalidTeamSize();
        printEnterTeamSizeMessage();
        cin >> *playersNum;
    }
    for (int i = 0; i < *playersNum; i++) {
        printInsertPlayerMessage();
        string name, job, line;
        cin >> name >> job;
        std::getline(cin, line);
        while (checkInvalidName(name) || checkInvalidJob(job) || checkInvalid(line)) {
            cin >> name >> job;
            std::getline(cin, line);
        }

        unique_ptr<Player> player;
        if (job == "Healer") {
            player = unique_ptr<Player>(new Healer(name));
        } else if (job == "Ninja") {
            player = unique_ptr<Player>(new Ninja(name));
        } else if (job == "Warrior") {
            player = unique_ptr<Player>(new Warrior(name));
        }
        playerSet.push(std::move(player));

    }
}


Mtmchkin::Mtmchkin(const std::string &fileName) {
    std::ifstream deck(fileName.c_str());
    if (!deck) {
        throw DeckFileNotFound();
    }
    m_numOfRounds = 0;
    m_playersNum = 0;
    BuildQueue(&deck, m_cardSet);
    StartGame(m_playerSet, &m_playersNum);
}

int Mtmchkin::getNumberOfRounds() const {
    return m_numOfRounds;
}

bool Mtmchkin::isGameOver() const {
    return m_playerSet.empty();
}


void Mtmchkin::printLeaderBoard() {
    printLeaderBoardStartMessage();
    int rank = 1;
    for (vector<PlayerPtr>::iterator it = m_winners.begin(); it != m_winners.end(); it++) {
        printPlayerLeaderBoard(rank, **it);
        rank++;
    }
    int length = m_playerSet.size();
    for (int i = 0; i < length; i++) {
        PlayerPtr player = std::move(m_playerSet.front());
        m_playerSet.pop();
        printPlayerLeaderBoard(rank, *player);
        m_playerSet.push(std::move(player));
        rank++;
    }
    for (vector<PlayerPtr>::iterator it = m_dead.begin(); it != m_dead.end(); it++) {
        printPlayerLeaderBoard(rank, **it);
        rank++;
    }
}

void Mtmchkin::playRound() {
    m_numOfRounds++;
    printRoundStartMessage(m_numOfRounds);
    int length = m_playerSet.size();


    for (int i = 0; i < length; i++) {
        PlayerPtr currentPlayer = std::move(m_playerSet.front());
        m_playerSet.pop();

        printTurnStartMessage(currentPlayer->getName());
        CardPtr currentCard = std::move(m_cardSet.front());
        m_cardSet.pop();
        currentCard->applyEncounter(currentPlayer);
        m_cardSet.push(std::move(currentCard));
        m_playerSet.push(std::move(currentPlayer));

    }

    UpdateGame();
    if (isGameOver()) {
        printGameEndMessage();
    }

}

void Mtmchkin::UpdateGame() {

    int length = m_playerSet.size();


    for (int i = 0; i < length; i++) {
        PlayerPtr currentPlayer = std::move(m_playerSet.front());
        m_playerSet.pop();
        if (currentPlayer->getLevel() >= 10) {
            m_winners.push_back(std::move(currentPlayer));
        } else if (currentPlayer->getHP() <= 0) {
            m_dead.insert(m_dead.begin(), std::move(currentPlayer));
        } else {
            m_playerSet.push(std::move(currentPlayer));
        }
    }
}


