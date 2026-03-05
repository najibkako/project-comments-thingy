#include <iostream>
#include <string>
#include "gameState.hpp"
#include "Drunkedness.hpp"

int money = 100;
int souls = 0;
int luck = 0;
int drunkenness = 0;

void runGameStateDemoOrWhatever() {
    drunkPrint("Here are your stats you sad sad man");
    drunkPrint("Balance: $" + std::to_string(money));
    drunkPrint("Souls: " + std::to_string(souls));
    drunkPrint("Luck: " + std::to_string(luck));
    drunkPrint("Drunkenness: " + std::to_string(drunkenness));
}
