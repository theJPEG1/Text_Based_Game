#include "Player.H"
#include "PlayerFactory.H"
#include "Enemy.H"
#include "EnemyFactory.H"
#include "Combat.H"
#include "PrettyColors.H"
#include "Saving.H"

#include "attacksEffects.H"

#include "include/json.hpp"
    using json = nlohmann::json;

#include <iostream>
    using std::cout;
#include <vector>
    using std::cout;
    using std::cin;
#include <time.h>
#include <fstream>
    using std::ifstream;
#include <string>
    using std::string;

//void newNames(vector<string>& nameSetter);
void combat(Player& newPlayer, PrettyColors& color);
void craftSpell(Player& newPlayer, PrettyColors& color);

struct locations
{
    /*
        State Reminders

        T1 = town 1
        T1D = town 1 day
        T1N = town 1 night

        CR1 = Cross Roads 1 (Forest or Town)

        F1 = Forest 1
    */

    PrettyColors color;

    locations(Player& player) 
    {
        p = player;
        CraftingMaterials cLoad;

        cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");
    };

    string state;
    Player p;
    vector<CraftingMaterials> cMats;

    void loadCrossRoads()
    {
        color.clearScreen();

        if(state == "CR1")
        {
            int keyboardInput = 0;
            cout << "You see a clearing towards a town and a path South into the woods?\n"
                << "[1] Go To Town \t[2] Follow South\n";
            cout << "-> ";

            while(keyboardInput <= 0 || keyboardInput > 2)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    state = "T1";
                    loadTown();
                }

                else if(keyboardInput == 2)
                {

                }

                else
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }
    };

    void loadForest()
    {
        color.clearScreen();

        if(state == "F1")
        {
            int keyboardInput = 0;
            cout << "You see a path that leads North and a path that leads South. What do you do?\n"
                << "[1] Follow North \t[2] Follow South\n"
                << "[3] Explore the Woods \t[4] Forage for materials\n";
            cout << "-> ";

            while(keyboardInput <= 0 || keyboardInput > 4)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    state = "T1";
                    loadTown();
                }

                else if(keyboardInput == 2)
                {

                }

                else
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }
    };

    void loadTown()
    {
        p.addToInventory(cMats.at(0), 5);
        color.clearScreen();

        if(state == "T1" || state == "T1D" || state == "T1N")
        {
            int keyboardInput = 0;
            cout << "Welcome to the town. What would you like to do?\n"
                << "[1] Enter Blacksmith \t[2] Enter Shop\n"
                << "[3] Enter Guild Center\t[4] Town Center\n"
                << "[5] Leave Town\t\t[6] Save + Quit\n";
            cout << "-> ";

            while(keyboardInput <= 0 || keyboardInput > 6)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    loadBlacksmith();
                }

                else if(keyboardInput == 2)
                {
                    loadShop();
                }

                else if(keyboardInput == 3)
                {
                    loadGuildCenter();
                }

                else if(keyboardInput == 4)
                {
                    loadTownCenter();
                }

                else if(keyboardInput == 5)
                {
                    state = "CR1";
                    loadCrossRoads();
                }

                else if(keyboardInput == 6)
                {
                    Saving::saveToFile(p, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
                    Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", p.getCustomAtks());
                }

                else
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }
    };

    void loadBlacksmith()
    {
        color.clearScreen();

        if(state == "T1" || state == "T1D" || state == "T1N")
        {
            int keyboardInput = 0;
            cout << "Welcome to the Blacksmith. What would you like to do?\n"
                << "[1] Buy \t[2] Craft\n"
                << "[3] Rumor\t[4] Leave\n";
            cout << "-> ";

            while(keyboardInput <= 0 || keyboardInput > 4)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    cout << "something about buying\n";
                    loadTown();
                }

                else if(keyboardInput == 2)
                {
                    p.printInventory();
                    color.pauseTerminal(3);
                    loadTown();
                }

                else if(keyboardInput == 3)
                {
                    cout << "something about rumors\n";
                    loadTown();
                }

                else if(keyboardInput == 4)
                {
                    loadTown();
                }

                else 
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }
    };

    void loadShop()
    {
        color.clearScreen();

        if(state == "T1" || state == "T1D")
        {
            int keyboardInput = 0;
            cout << "Welcome to the Shop. What would you like to do?\n"
                << "[1] Buy \t[2] Sell\n"
                << "[3] Rumor\t[4] Leave\n";
            cout << "-> ";

            while(keyboardInput <= 0 || keyboardInput > 4)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    cout << "something about buying\n";
                    loadTown();
                }

                else if(keyboardInput == 2)
                {
                    cout << "something about selling\n";
                    loadTown();
                }

                else if(keyboardInput == 3)
                {
                    cout << "something about rumors\n";
                    loadTown();
                }

                else if(keyboardInput == 4)
                {
                    loadTown();
                }

                else 
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }

        else if(state == "T1N")
        {

        }
    };

    void loadGuildCenter()
    {
        color.clearScreen();

        if(state == "T1" || state == "T1D" || state == "T1N")
        {
            int keyboardInput = 0;
            cout << "Welcome to the Guild Center. What would you like to do?\n"
                << "[1] Guild Card \t[2] check inventory\n"
                << "[3] Quest Log\t[4] Leave\n";
            cout << "-> ";

            while(keyboardInput <= 0 || keyboardInput > 4)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    cout << "something about guild card\n";
                    loadTown();
                }

                else if(keyboardInput == 2)
                {
                    cout << "something about inventory\n";
                    loadTown();
                }

                else if(keyboardInput == 3)
                {
                    cout << "something about quest logs\n";
                    loadTown();
                }

                else if(keyboardInput == 4)
                {
                    loadTown();
                }

                else 
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }
    };

    void loadTownCenter()
    {
        color.clearScreen();

        if(state == "T1" || state == "T1D")
        {
            int keyboardInput = 0;
            cout << "Welcome to the Town Center. What would you like to do?\n"
                << "[1] Talk to people \t[2] Toss in a coin\n"
                << "[3] wait till night\t[4] Leave\n";
            cout << "-> ";


            while(keyboardInput <= 0 || keyboardInput > 4)
            {
                cin >> keyboardInput;

                if(keyboardInput == 1)
                {
                    cout << "something about buying\n";
                    loadTown();
                }

                else if(keyboardInput == 2)
                {
                    cout << "something about selling\n";
                    loadTown();
                }

                else if(keyboardInput == 3)
                {
                    cout << "something about rumors\n";
                    loadTown();
                }

                else if(keyboardInput == 4)
                {
                    loadTown();
                }

                else 
                {
                    cout << "!Invalid Input!\n";
                    keyboardInput = 0;
                }
            }
        }

        else if(state == "T1N")
        {

        }
    };

    
};

int main()
{
    bool inGame = false;
    PrettyColors color;
    time_t timer;
    srand(time(&timer));
    Player newPlayer;

    ifstream inFile;
        inFile.open("playerData/playerStatsSave.json");

        if(!inFile)
        {
            cout << color.RED << "Error opening file.\n" << color.DEFAULT;
            exit(1);
        }

        json j;
        inFile >> j;
    
    bool playerExists = false;
    if(!j.empty())
    {
        cout << "[1] Load from File (" << color.YELLOW << j["name"] << " | Level: " << j["level"] << " | " << color.YELLOW << "Exp: " << j["xp"] << "/" << j["xpToNextLevel"] << " | " << color.CYAN << "Health: " << j["hp"] << "/" << j["maxHp"] << color.DEFAULT << ")"
            <<"\n[2] New Player\n-> ";

        inFile.close();

        while(!playerExists)
        {
            int keyboardInput = 0;
            cin >> keyboardInput;

            if(keyboardInput == 1)
            {
                newPlayer = PlayerFactory::loadFromFile("playerData/playerStatsSave.json");
                playerExists = true;
            }

            else if(keyboardInput == 2)
            {
                newPlayer = PlayerFactory::createPlayer();

                Saving::saveToFile(newPlayer, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
                playerExists = true;
            }

            else
            {
                cout << color.RED << "INVALID INPUT!\n" << color.DEFAULT;
            }
        }
    }

    else
    {
        newPlayer = PlayerFactory::createPlayer();

        Saving::saveToFile(newPlayer, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
        playerExists = true;
    }

    inGame = true;

    while(inGame)
    {
        locations l(newPlayer);
        l.state = "T1";

        l.loadTown();

        inGame = false;
    }

    // cout << "making load\n";
    // CraftingMaterials load;

    
    // vector<CraftingMaterials> mats = load.loadCraftingMaterialss("GameData/craftingMaterials.json");

    // Attacks newAtk = Attacks::createAttack(mats.at(0), mats.at(1), mats.at(2));

    // newPlayer.addCustomAtk(newAtk);

    // newPlayer.setSpecificSlot(newAtk, 0);

    // cout << newAtk.thisEffects.size();

    // while(newPlayer.getHealth() > 0)
    // {
    //     combat(newPlayer, color);
    //     cout << "saving player\n";
    //     Saving::saveToFile(newPlayer, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
    //     cout << "saved player, now saving cus attacks.";
    //     Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", newPlayer.getCustomAtks());
    // }

    
    

    return 0;
};

void combat(Player& newPlayer, PrettyColors& color)
{
    // Enemy e1 = EnemyFactory::createEnemy("Forest", "", " the Slime", 10, 5, 8, 3, 7);
    // Enemy e2 = EnemyFactory::createEnemy("Forest", "", " the Squirel", 2, 2, 25, 1, 3);
    // Enemy e3 = EnemyFactory::createEnemy("Forest", "", " the Bunny", 2, 2, 35, 1, 4);
    // Enemy e4 = EnemyFactory::createEnemy("Forest", "", " the Wolf", 16, 8, 10, 5, 10);
    // Enemy e5 = EnemyFactory::createEnemy("Forest", "", " the Boar", 16, 10, 11, 6, 12);
    // Enemy e6 = EnemyFactory::createEnemy("Forest", "", " the Bear", 20, 13, 10, 9, 15);
    // Enemy e7 = EnemyFactory::createEnemy("Forest", "", " the Sprig", 26, 11, 13, 15, 20);
    // Enemy e8 = EnemyFactory::createEnemy("Forest", "", " the Stump Golem", 32, 16, 8, 18, 25);
    // Enemy e9 = EnemyFactory::createEnemy("Forest", "", " the ???", 20, 5, 5, 20, 30);
    // Enemy e10 = EnemyFactory::createEnemy("Forest", "", " the Dragon", 37, 15, 15, 30, 60);

    vector<vector<Enemy>> forest = EnemyFactory::loadRegionEnemy("Forest");

    Combat forestCombat(newPlayer, forest, "Forest");

    forestCombat.determineEnemy();
    //forestCombat.printGui();

    forestCombat.newCombatTest();

    cout << color.YELLOW << "You survived the encounter!\n" << color.DEFAULT;
};
