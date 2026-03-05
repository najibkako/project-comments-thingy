#include "Drunkedness.hpp"
// connects this file to its header

#include "gameState.hpp"
// gives access to global variables:
// money, souls, luck, drunkenness

#include <iostream>
// allows us to use cout

#include <cstdlib>
// allows us to use rand()

#include <cctype>
// allows us to check if a character is a letter


// ==================================================
// DRUNKIFY FUNCTION
// Replaces random letters with symbols depending
// on how drunk the player is
// ==================================================

std::string drunkify(const std::string& text)
{ 
    const char symbols[] = { '$', '#', '@', '%', '&' };
    const int symbolCount = 5;

    std::string result = text;

    int d = drunkenness;

    

    if (d < 0)
        d = 0;

    if (d > 100)
        d = 100;
// Loop through each character and randomly replace letters with symbols based on drunkenness
    for (int i = 0; i < (int)result.length(); i++)
    {
        char c = result[i];

        // only modify letters
        if (std::isalpha((unsigned char)c))
        {
            int roll = rand() % 100;

            // drunkenness controls chance of replacement
            if (roll < d)
            {
                result[i] = symbols[rand() % symbolCount];
            }
        }
    }

    return result;
}


// ==================================================
// DRUNK PRINT
// Prints text after applying drunkify()
// ==================================================

void drunkPrint(const std::string& text)
{
    std::cout << drunkify(text) << std::endl;
}


// ==================================================
// UPDATE LUCK FROM DRUNKENNESS
// Every 10 drunkenness = +1 luck
// Luck is capped at 10
// ==================================================

void updateLuckFromDrunkenness()
{
    luck = drunkenness / 10;

    if (luck > 10)
        luck = 10;

    if (luck < 0)
        luck = 0;
}
