#include <iostream>
// allows us to use cout and cin (input/output)

#include <cstdlib>
// allows us to use rand()

#include <ctime>
// allows us to use time() for random seeding

#include "coinflip.hpp"
// includes the coinflip gambling game

#include "gameState.hpp"
// includes global player stats (money, luck, drunkenness, souls)

#include "Drunkedness.hpp"
// includes drunkPrint and drunkify (messes up text when drunk)

#include "blackjack.hpp"
// includes blackjack game functions

int main() {

    srand(time(0));
    // seeds the random number generator once at program start
    // without this, rand() would give the same numbers every time, im gonna off myself

    bool running = true;
    // controls the main game loop
    // when running becomes false, the game ends

    // ===== DRINK COSTS =====
    int whiskeyCost = 10;
    int vodkaCost = 20;
    int bloodyMaryCost = 30;

    int bloodyMaryCount = 0;
    // keeps track of how many Bloody Marys the player has had for jumpscare logic

    // sets the price for each drink

    while (running) {
        // main loop runs until player quits

        runGameStateDemoOrWhatever();
        // shows current player stats

        drunkPrint("");
        drunkPrint("What would you like to do?");
        drunkPrint("1) Drink");
        drunkPrint("2) Coinflip");
        drunkPrint("3) Donate Money to IsntReal!");
        drunkPrint("4) Play Blackjack (Requires 15 souls)");
        drunkPrint("5) Quit");
        drunkPrint("Choice: ");
        // drunkPrint messes up letters depending on drunkenness

        int choice;
        std::cin >> choice;
        // takes player input

        if (choice == 1) {

            drunkPrint("");
            drunkPrint("Choose a drink:");
            drunkPrint("1) Whiskey ($10)  -> +1 luck, +5 drunk");
            drunkPrint("2) Vodka Shots ($20) -> +2 luck, +10 drunk");
            drunkPrint("3) Bloody Mary ($30) -> +3 luck, +8 drunk");
            drunkPrint("Choice: ");

            int drinkChoice;
            std::cin >> drinkChoice;

            if (drinkChoice == 1) {

                if (money < whiskeyCost) {
                    drunkPrint("Your broke ass cant afford a whiskey you bum how do you even have less than 10$ are we being fr chat?.");
                }
                else {
                    money -= whiskeyCost;
                    // subtract drink cost from money

                    luck += 1;
                    // whiskey increases luck a little

                    drunkenness += 5;
                    // whiskey increases drunkenness slightly

                    if (drunkenness > 100)
                        drunkenness = 100;
                    // caps drunkenness at 100

                    drunkPrint("You drink a Whiskey and remember your wife and kids that left you because of your drinking and gamblin habit you fucking bum.");
                }
            }

            else if (drinkChoice == 2) {

                if (money < vodkaCost) {
                    drunkPrint("You can't afford Vodka Shots... you cant aford shit not gonna lie.. broke ahh");
                }
                else {
                    money -= vodkaCost;
                    // subtract cost

                    luck += 2;
                    // vodka increases luck more than whiskey

                    drunkenness += 10;
                    // vodka makes you twice as drunk as whiskey

                    if (drunkenness > 100)
                        drunkenness = 100;

                    drunkPrint("You take Vodka Shots and you feel your ancestors shamefully look down on you.");
                }
            }

            else if (drinkChoice == 3) {

                if (money < bloodyMaryCost) {
                    drunkPrint("You can't afford a Bloody Mary you little shit.");
                }
                else {
                    money -= bloodyMaryCost;
                    // subtract cost

                    luck += 3;
                    // bloody mary increases luck as much as 3 whiskeys

                    drunkenness += 8;
                    // moderate drunkenness increase

                    if (drunkenness > 100)
                        drunkenness = 100;

                    drunkPrint("You drink a Bloody Mary. hope this was worth your family.");

                    // ===== BLOODY MARY x3 JUMPSCARE =====
                    bloodyMaryCount++;

                    if (bloodyMaryCount >= 3) {

                        std::cout << R"(         +  #-.++-##--+..--#+ .. - -++-+###+.##+---+++----..              .  
 ---.  ######+###--##-#+++..+ -##-+--###++-###-.#####--###+-+-.-...--#. ... 
     .##++#++  ####.-###+####-++#.######-+##+#+#####++#+#+#+#+-++...- . ... 
 .. .###.-#######-+ #####++####.######++#########++#++#-+####+##+----... -  
 ..-##.#- -####--####-  .---.++#+..-+##++++++++#++########- +-##+########++ 
-+##+.-#####+-..++-#########--....------.-----++#####+-#-#####-+##+..-#..##.
#+######++--+###+.... ....-++++##-++-++###+####--. . .####++####+######+#-.+
-###+---++.  ..--#+-----++#+++######+++--++-+#####-###. .-####+####++.####+ 
+#.# #+--#########+#####+-.---.  ..----..-+.--..++###+#+##+ +##.+-#+++--#-#+
 ++#..+#++#-------.-.++###########################++####+##+  #####+##++##+-
.- ##--##.-+#..######+--.         ..     .        .++-.+##+#+#  ## #+#+#-##+
 ##+####-+####+   . ....-.-.-+-...-....-.- ...-..+ ......++#-### ###+#++-+#-
+-+#-..+##+. ...+ -.---.-.-...   .  .    ......-.-.--+---.--#+..#  ##-+####-
.#+.-+##-...+-..-.+...-.-........--  .-. .  ......--...--.-++## #-# .##-#+#+
---.+#+..++...---.-----.... --###########-... .-.-.--.-.-....-##..+#. .###-#
 .-##-..--+-+--...--.---. .-#-##        ##.-.-. ....-.-.-.-----+##-.#-#  ###
.+##-.++--.------..... .. +++#+         -#+++-......-.-.-.-------+#######.  
.#+------+-------...-.---+++--            ..--+- .-..----.-------.-#++-##++-
++-+-+--+--------.--++++#+--+ ####    #####-.+-+# .--..--------++.---+#++-##
 ---+------------.+--+##+-+####+###  ########+++#+- +---------------.-.++++ 
.+++++-++-+++-------+-############    ########+++#+.-.------+++----+-+-----.
-+++++++---+++---.++#+++++##             #   ######...----+---++-++++++---. 
.-++++++++++++++--+########  ++   #####.  #  ##-+###-.-+--------+--+++++++-.
.+++++++++++++++++#+++######  #       -   .+-##+####---+--+++++++--++-+---- 
.+++++++++++++++++##+#######. #   ####+.+--+###+##+#++-+++------+--++++---- 
.+++++++++++++++-#++########+   #########.-+####+####++-----++-++-++--+++-- 
.+++++++++++++++-#++#########  ########-##.#####+####++--++----++-++--+++-- 
.++++++++++++++++++#######+##- ###    +### ##########++++++++++++-++--+++-+ 
-++++++++#+++++++++#########+#--#########+#####+++##+#+--++++++++++-+------ 
.++++++++++++++++++++#+####+#-+.-#   ..--.#+###++##++++++++-----+---+------.
-+++#++++++++++++++++#++++++####-######+#+#+##++++#+++++---+++++-----+-+-+-.
.++++++++++++++++#+#++##+#####++###########-+#-+-++++++++------+++++++++--- 
.++++++++++++++##############-+++++###+++###+######-.+++--------+------++-- 
.+++++++#+#######   -# .#.-+-.-++--##+.--++#-###+######+++--+.+-----+.-+++- 
.+++++-####    +     +  # +#+..++..##+##+-+###--++-#  ######+-------+-----..
.++#++-##       #    + ++ +-. .++.-##+##+++##+.-+.# ..     ##-+----.+++---..
-++++++#     .    ## #  # ++  .+- ..#-+#.++-## -. +  .##.   +#+.---+++---.-.
-+++++##    -     -     # .#  -##.-.+..+.-# ##.--.# - ..     ##.+---...-+#- 
-++++##     -  + +   . .- .-  .+-.+ -++#. # .#.-.-- --.+..    ##-----#+--.- 
-#-#+##       -      -  # .-  -.. +++--+  # +#.- +  .  - ..   ##+.++-----.-.
.++++#     .-   .       # .# .++-.+ +++#  - #. +  + -+.- -+    #+---+-+++-- 
.+#+##      -   .  -    - -+ .+.. +++--# -- #- + .# .... .-.   -+.--...---..
.++++#     .-      .   .# ++ -+-  -..-.- +  #  + -+ ++....-..   #-.---+----.
-++#+#      ..          # .- -.+  . +--+ #  #  + ++ -+..--...   #-+-.------ 
-++++#     . #  .         -. ..-. +.. .+ #  # .. #+ ...--.. .   #-.-+------.
.+++-#     . #          - -  - ...  ###. #  + .- .. ..++#-.     #----.--.-. 
-++#-#      .#          - + .- .. -.   . #. #- . -.  ##+-.      #-+-----.-. 
-++++#       #            .       .  -.  # .#. . .   #-.-.  .   #...-.-+--. 
-++++#      .#+           -  ...  ##-++  #  + .+.-#  #.....     #--...-+-...
.#+#-#       .#         . .          -.. +  # .. -.  #+-+..    -#--..-.-.-. 
.++++#      - #         .    . .. ##-..+ #. + --.--  .-.--. .+ #+-------..-.
-++++#        #    .    .      .  .. .+  -  - .. +   .+..  ..  #-----..---- 
.+++##+      -+-   .        .. .. #.++.. .+ #... ..  .+-..     #---------.. 
-++++##     -#+#             .  . #--.-- +. - .. ... -+.....   #......---++.
.++++##     .- #+       .  . .... .- .-  +  #... . ..#+-. ..   #------+--#+.
.+++++#   . + -#-       .    ...  ##..#  #..- ..     #+.....  -#-------.-#+-
-+++++#  ....  +             .  --  .-+  #..-  -.-.  #.-...   --.--....-.#-.
-++++-#     .  #        .  . -+.  #-.+#  -- -...     #.....   #+--.......#--
-+++++#     +  #        . .+ +...  . .# -.. ...-.. . #......  #--...----.#+-
.+++++#    +-  #        . .. +    -##+-  #- -. -...  ##-....  #.....--.-.#+-
-+++++##  .#  +#       .  .. ---  +. .-. #  -- -     -#-.... --.-...-....#--
-+++++##  -   ##          +. -.+...#...  -- -- ..    .#--..  #--....-..-.#-+
#########     #            . .---..-. -  +- .- .      .#--#  #..++++++++-###
                                                                            )";

                        // reset stats
                        drunkenness = 0;
                        luck = 0;

                        // reset counter so it can happen again after 3 more
                        bloodyMaryCount = 0;
                    }
                }
            }

            else {
                drunkPrint("do you know how to type dumbass? write a valid drink brotha");
                // invalid drink option
            }
        }

        else if (choice == 2) {
            coinflip();
            // runs the coinflip gambling game
        }

        else if (choice == 3) {
            // donate money to IsntReal

            int donationAmount = 67;

            if (money >= donationAmount) {

                money -= donationAmount;
                // subtract donation

                int roll = (rand() % 100) + 1;
                // random number 1–100

                int soulsGained = 0;

                if (roll <= 5) {
                    // 5% chance — only 1 soul (bad outcome)
                    soulsGained = 1;
                    souls += soulsGained;

                    drunkPrint("You donate $67 to IsntReal.");
                    drunkPrint("The Devil is left speechless...");
                    drunkPrint("\"47 missles were fired and... you only got the janitor\"");
                    drunkPrint("You gain 1 soul.");
                }
                else if (roll <= 10) {
                    // 5% chance — JACKPOT
                    soulsGained = 10;
                    souls += soulsGained;

                    drunkPrint("You donate $67 to IsntReal.");
                    drunkPrint("You see a mushroom cloud in the distance.");
                    drunkPrint("\"INTERESTING...\" the Devil whispers.");
                    drunkPrint("You gain 10 souls.");
                }
                else {
                    // 90% normal outcome — 1 to 5 souls
                    soulsGained = (rand() % 5) + 1;
                    souls += soulsGained;

                    drunkPrint("You donate $67 to IsntReal. You hear a distant explosion.");
                    drunkPrint("The Devil nods slightly.");
                    drunkPrint("You gain " + std::to_string(soulsGained) + " souls.");
                }
            }
            else {
                drunkPrint("You do not please lord Benjamin.");
                drunkPrint("You need $67 to donate. Current money: $" + std::to_string(money));
            }
        }

        else if (choice == 4) {
            // blackjack is locked until you have 15 souls

            if (souls < 15) {
                drunkPrint("A cold voice hisses: \"Not yet.\"");
                drunkPrint("You need 15 souls to sit at the Devil's table.");
                drunkPrint("You currently have " + std::to_string(souls) + " souls.");
            }
            else {
                playBlackjack();
                // runs the blackjack gambling game
            }
        }

        else if (choice == 5) {
            running = false;
            // exits the loop and ends the program
        }

        else {
            drunkPrint("do you know how to type dumbass? write a valid drink brotha");
            // invalid main menu input
        }
    }

    return 0;
    // ends program successfully
}
