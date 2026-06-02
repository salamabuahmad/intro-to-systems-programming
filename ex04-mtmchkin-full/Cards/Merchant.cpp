#include "Merchant.h"

Merchant::Merchant() : Card(){
    m_type = "Merchant";
    m_cost = 5;
    m_heal = 1;
    m_buff = 1;
}

void Merchant::applyEncounter(PlayerPtr& player) const {
    int choice = -1;
    printMerchantInitialMessageForInteractiveEncounter(std::cout,player->getName(),player->getCoins());
    std::string line;

    while (choice != 0 && choice != 1 && choice != 2) {
        std::getline(std::cin, line);
        try{
            choice = std::stoi(line);
            if (choice != 0 && choice != 1 && choice != 2){
                printInvalidInput();
            }
        }catch (std::invalid_argument& e){
            throw e;
        }
    }


    std::cin >> choice;

    if(choice == 1){
        if(!player->pay(m_cost)){
            printMerchantInsufficientCoins(std::cout);
            return;
        }
        player->heal(m_heal);
    }

    if(choice == 2){
        if(!player->pay(2 * m_cost)){
            printMerchantInsufficientCoins(std::cout);
            return;
        }
        player->buff(m_buff);
    }

    printMerchantSummary(std::cout,player->getName(),choice,m_cost * choice);

}
