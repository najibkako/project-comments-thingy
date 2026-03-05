#include <iostream>
// allows us to use cin and cout

#include <cstdlib>
// allows us to use rand()

#include <string>
// allows us to use std::to_string

#include "coinflip.hpp"
// includes function declaration

#include "gameState.hpp"
// gives access to global variables:
// money, luck, drunkenness

#include "Drunkedness.hpp"
// gives access to drunkPrint() and updateLuckFromDrunkenness()


void coinflip()
{
    // make sure luck matches current drunkenness
    updateLuckFromDrunkenness();

    // ===== START GAME =====

    drunkPrint("Here Let's Flip a Coin!");
    drunkPrint("You have $" + std::to_string(money) + " available to bet.");

    int betAmount;
    char playerChoice;

    // ----- GET BET AMOUNT -----
    drunkPrint("Enter your bet amount: ");
    std::cin >> betAmount;

    // validate bet
    if (betAmount > money || betAmount <= 0)
    {
        drunkPrint("you ain't got money like that bro bet a valid amount.");
        return;
        // exits function early if invalid
    }

    // ----- GET PLAYER CHOICE -----
    drunkPrint("Choose Heads (H) or Tails (T): ");
    std::cin >> playerChoice;

    if (playerChoice != 'H' && playerChoice != 'T' &&
        playerChoice != 'h' && playerChoice != 't')
    {
        drunkPrint("bro there are two options how did you even manage??? Please choose H or T.");
        return;
    }

    // ===== LUCK SYSTEM =====
    // Base win chance = 50%
    // Each luck point adds +2%
    // Max win chance = 75%

    int winChance = 50 + (luck * 2);

    if (winChance > 75)
        winChance = 75;

    int roll = rand() % 100;
    // random number between 0 and 99

    bool choseHeads = (playerChoice == 'H' || playerChoice == 'h');

    char coinResult;

    if (roll < winChance)
    {
        // FORCE WIN (coin matches player choice)
        coinResult = choseHeads ? 'H' : 'T';
    }
    else
    {
        // FORCE LOSS (coin opposite of player choice)
        coinResult = choseHeads ? 'T' : 'H';
    }

    // show result
    if (coinResult == 'H')
        drunkPrint("The coin landed on: Heads");
    else
        drunkPrint("The coin landed on: Tails");

    // ===== DETERMINE WIN OR LOSS =====

    if ((choseHeads && coinResult == 'H') ||
        (!choseHeads && coinResult == 'T'))
    {
        drunkPrint("BIG WIN BABYY! You gain $" + std::to_string(betAmount) + ".");
        money += betAmount;
    }
    else
    {
        drunkPrint("womp womp you lose $" + std::to_string(betAmount) + ".");
        money -= betAmount;
    }

    drunkPrint("You now have $" + std::to_string(money) + " remaining.");
}
