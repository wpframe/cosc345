#include "Casino.h"
#include <ctime>
#include <cstdlib>

Casino::Casino() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Casino::rouletteWheel() {
    return std::rand() % 37;
}

double Casino::rouletteMultiplier(int result) {
    if (result == 0) return 35.0;
    return 1.0;
}

std::vector<std::string> Casino::slotMachineSpin() {
    std::vector<std::string> symbols = {"BAR", "7", "Cherry", "Lemon"};
    std::vector<std::string> result(3);

    for (int i = 0; i < 3; ++i) {
        result[i] = symbols[std::rand() % symbols.size()];
    }
    return result;
}

double Casino::slotMachineMultiplier(const std::vector<std::string>& result) {
    if (result[0] == "7" && result[1] == "7" && result[2] == "7") return 10.0;
    if (result[0] == "BAR" && result[1] == "BAR" && result[2] == "BAR") return 5.0;
    if (result[0] == "Cherry" && result[1] == "Cherry" && result[2] == "Cherry") return 3.0;
    if (result[0] == "Lemon" && result[1] == "Lemon" && result[2] == "Lemon") return 2.0;
    return 0.0;
}

// Blackjack had a LOT of assistance with ChatGPT to get to the desired result as 

void Casino::startBlackjack() {
    playerHand.clear();
    dealerHand.clear();

    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());
}

std::tuple<std::string, std::string> Casino::hit() {
    auto card = drawCard();
    playerHand.push_back(card);
    return card;
}

std::tuple<std::string, std::string> Casino::doubleDown() {
    auto card = hit();
    stand();
    return card;
}

std::vector<std::tuple<std::string, std::string>> Casino::stand() {
    int dealerTotal = computeHandTotal(dealerHand);
    while (dealerTotal < 16) {
        auto card = drawCard();
        dealerHand.push_back(card);
        dealerTotal = computeHandTotal(dealerHand);
    }
    return dealerHand;
}

double Casino::blackjackMultiplier(int playerTotal, int dealerTotal) {
    if (playerTotal > 21) return 0.0;
    if (dealerTotal > 21 || playerTotal > dealerTotal) return 2.0;
    if (playerTotal == dealerTotal) return 1.0;
    return 0.0;
}

std::tuple<std::string, std::string> Casino::drawCard() {
    std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string cards[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

    std::string suit = suits[std::rand() % 4];
    std::string card = cards[std::rand() % 13];

    return std::make_tuple(card, suit);
}

int Casino::computeHandTotal(const std::vector<std::tuple<std::string, std::string>>& hand) {
    int total = 0;
    int aceCount = 0;

    for (const auto& card : hand) {
        if (card.first == "Ace") {
            aceCount++;
            total += 11;
        } else if (card.first == "Jack" || card.first == "Queen" || card.first == "King") {
            total += 10;
        } else {
            total += std::stoi(card.first);
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return total;
}
