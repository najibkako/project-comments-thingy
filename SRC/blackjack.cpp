#include <iostream>
#include <cstdlib>
#include <ctime>

#include "blackjack.hpp"
#include "gameState.hpp"
#include "Drunkedness.hpp"

struct Card {
    int rank; // 1-13
    int suit; // 0-3
};
// Helper functions for card names and values
static const char* suitName(int suit) {
    switch (suit) {
        case 0: return "Hearts";
        case 1: return "Diamonds";
        case 2: return "Clubs";
        default: return "Spades";
    }
}
// Helper function to get rank name
static const char* rankName(int rank) {
    switch (rank) {
        case 1: return "Ace";
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        default: return "";
    }
}
// Prints a card in a readable form
static void printCard(const Card& c) {
    if (c.rank >= 2 && c.rank <= 10) std::cout << c.rank;
    else std::cout << rankName(c.rank);

    std::cout << " of " << suitName(c.suit);
}
// Deck functions
static void initDeck(Card deck[52]) {
    int idx = 0;
    for (int s = 0; s < 4; ++s) {
        for (int r = 1; r <= 13; ++r) {
            deck[idx].suit = s;
            deck[idx].rank = r;
            ++idx;
        }
    }
}
// Fisher-Yates shuffle algorithm
static void shuffleDeck(Card deck[52]) {
    for (int i = 51; i > 0; --i) {
        int j = rand() % (i + 1);
        Card tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}
// Deals the next card from the deck and advances the index
static Card dealCard(Card deck[52], int& nextIndex) {
    Card c = deck[nextIndex];
    ++nextIndex;
    return c;
}
// Calculates the value of a hand, treating Aces as 1 or 11
static int cardValueNoAce(int rank) {
    if (rank >= 2 && rank <= 10) return rank;
    if (rank >= 11 && rank <= 13) return 10;
    return 0;
}
// Calculates total hand value, counting Aces as 1 or 11
static int handValue(const Card hand[], int count) {
    int total = 0;
    int aces = 0;
// First count non-Ace cards and track Aces
    for (int i = 0; i < count; ++i) {
        if (hand[i].rank == 1) aces++;
        else total += cardValueNoAce(hand[i].rank);
    }

    total += aces;
//Count Aces as 11 if it doesn't bust
    while (aces > 0 && total + 10 <= 21) {
        total += 10;
        aces--;
    }
    return total;
}
// Prints a hand, optionally hiding the dealer's first card
static void printHand(const char* who, const Card hand[], int count, bool hideFirstCard) {
    std::cout << who << " hand: ";
    for (int i = 0; i < count; ++i) {
        if (hideFirstCard && i == 0) std::cout << "[Hidden Card]";
        else printCard(hand[i]);

        if (i < count - 1) std::cout << ", ";
    }
    std::cout << "\n";
}
// Reads an integer from input, returns false if invalid
static bool readInt(int& out) {
    std::cin >> out;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// Uses GLOBAL money/souls from gameState.hpp (no parameters!)
void playBlackjack() {

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    bool keepPlaying = true;

    while (keepPlaying) {
        std::cout << "\n=============== BLACKJACK ================\n";
        std::cout << "Souls: " << souls << " | Money: $" << money << "\n";

        // Choose betting currency
        char mode;
        std::cout << "Bet with (m)oney or (s)ouls? ";
        std::cin >> mode;

        bool soulMode = (mode == 's' || mode == 'S');
        bool moneyMode = (mode == 'm' || mode == 'M');

        if (!soulMode && !moneyMode) {
            std::cout << "Choose 'm' or 's'.\n";
            continue;
        }

        // Flavor text
        if (soulMode) {
            std::cout << "\nThe Devil appears and just grins at you.\n";
            std::cout << "\"Let us see what you're REALLY worth :)))))))))),\" the Devil says.\n";
        } else {
            std::cout << "\nYou sit at a regular table. The dealer is waiting to bankrupt you.\n";
        }

        // Check resources
        if (moneyMode && money <= 0) {
            std::cout << "You're out of money! WOMP WOMP.\n";
            return;
        }
        if (soulMode && souls <= 0) {
            std::cout << "\"Empty.\" The Devil smiles. \"Come back when you lost more morality.\"\n";
            return;
        }

        // Bet
        int bet = 0;
        if (moneyMode) std::cout << "Enter your bet amount (money): $";
        else std::cout << "Enter your bet amount (souls): ";

        if (!readInt(bet)) {
            std::cout << "Invalid number.\n";
            continue;
        }

        if (bet <= 0) {
            std::cout << "Bet must be at least 1.\n";
            continue;
        }

        if (moneyMode && bet > money) {
            std::cout << "Bet must be between $1 and $" << money << ".\n";
            continue;
        }
        if (soulMode && bet > souls) {
            std::cout << "\"You can't wager what you don't own,\" the Devil starts teabagging your ass.\n";
            continue;
        }

        Card deck[52];
        initDeck(deck);
        shuffleDeck(deck);
        int nextCard = 0;

        Card player[11];
        Card dealer[11];
        int playerCount = 0, dealerCount = 0;

        // initial deal
        player[playerCount++] = dealCard(deck, nextCard);
        dealer[dealerCount++] = dealCard(deck, nextCard);
        player[playerCount++] = dealCard(deck, nextCard);
        dealer[dealerCount++] = dealCard(deck, nextCard);

        // show
        printHand("Dealer", dealer, dealerCount, true);
        printHand("Player", player, playerCount, false);

        int playerScore = handValue(player, playerCount);
        int dealerScore = handValue(dealer, dealerCount);

        std::cout << "Player value: " << playerScore << "\n";

        bool playerBlackjack = (playerCount == 2 && playerScore == 21);
        bool dealerBlackjack = (dealerCount == 2 && dealerScore == 21);

        auto addWinnings = [&](int amount) {
            if (moneyMode) money += amount;
            else souls += amount;
        };

        auto subtractLoss = [&](int amount) {
            if (moneyMode) money -= amount;
            else souls -= amount;
        };

        auto winMsg = [&](int amount) {
            if (soulMode) {
                std::cout << "\"FAHHHHHHHHH\" the Devil says. \"Take " << amount
                          << " souls. For now.\"\n";
            } else {
                std::cout << "You win $" << amount << "!\n";
            }
        };

        auto loseMsg = [&](int amount) {
            if (soulMode) {
                std::cout << "The Devil collects " << amount << " souls and grins.\n";
            } else {
                std::cout << "You lose $" << amount << ".\n";
            }
        };

        auto pushMsg = [&]() {
            if (soulMode) {
                std::cout << "\"A draw.\" The Devil frowns. \"Man and I was cheating and EVERYTHING.\"\n";
            } else {
                std::cout << "Push! Bets returned.\n";
            }
        };

        // check natural blackjack
        if (playerBlackjack && dealerBlackjack) {
            pushMsg();
        } 
        else if (playerBlackjack) {
            // Blackjack pays 3:2
            int win = bet + bet / 2;

            addWinnings(win);

            if (soulMode) {
                std::cout << "BLACKJACK!\n";
                std::cout << "\"Luck... or fate... idk man you're the one who sent money to big Benjamin,\" the Devil hisses.\n";
                std::cout << "You gain " << win << " souls.\n";
            } else {
                std::cout << "BLACKJACK! You win $" << win << "!\n";
            }
        } 
        else if (dealerBlackjack) {
            subtractLoss(bet);
            if (soulMode) std::cout << "\"BLACKJACK,\" the Devil whispers. \"Pay up. Buttercup.\"\n";
            loseMsg(bet);
        } 
        else {
            // player turn
            bool playerBust = false;

            while (true) {
                char choice;
                std::cout << "hit or stand? (h/s): ";
                std::cin >> choice;

                if (choice == 'H' || choice == 'h') {
                    player[playerCount++] = dealCard(deck, nextCard);
                    printHand("Player", player, playerCount, false);

                    playerScore = handValue(player, playerCount);
                    std::cout << "Player value: " << playerScore << "\n";

                    if (playerScore > 21) {
                        playerBust = true;
                        break;
                    }
                } 
                else if (choice == 'S' || choice == 's') {
                    break;
                } 
                else {
                    std::cout << "Please enter 'h' to hit or 's' to stand.\n";
                }
            }

            // dealer turn
            printHand("Dealer", dealer, dealerCount, false);
            dealerScore = handValue(dealer, dealerCount);
            std::cout << "Dealer value: " << dealerScore << "\n";

            bool dealerBust = false;

            if (!playerBust) {
                while (handValue(dealer, dealerCount) < 17) {
                    dealer[dealerCount++] = dealCard(deck, nextCard);
                    printHand("Dealer", dealer, dealerCount, false);

                    dealerScore = handValue(dealer, dealerCount);
                    std::cout << "Dealer value: " << dealerScore << "\n";
                }
                if (dealerScore > 21) dealerBust = true;
            }

            // determine winner
            if (playerBust) {
                subtractLoss(bet);
                if (soulMode) std::cout << "\"BUST.\" The Devil Laughs at your goofy ass.\n";
                loseMsg(bet);
            } 
            else if (dealerBust) {
                addWinnings(bet);
                if (soulMode) std::cout << "\"Hell nah,\" the Devil mutters.\n";
                winMsg(bet);
            } 
            else if (playerScore > dealerScore) {
                addWinnings(bet);
                winMsg(bet);
            } 
            else if (playerScore < dealerScore) {
                subtractLoss(bet);
                loseMsg(bet);
            } 
            else {
                pushMsg();
            }
        }

        std::cout << "Now: Souls = " << souls << " | Money = $" << money << "\n";

        char again;
        std::cout << "Play again? (Y/N): ";
        std::cin >> again;

        keepPlaying = (again == 'Y' || again == 'y');
    }
}
