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

    cout << "making load\n";
    CraftingMaterials load;

    
    vector<CraftingMaterials> mats = load.loadCraftingMaterialss("GameData/craftingMaterials.json");

    Attacks newAtk = Attacks::createAttack(mats.at(0), mats.at(1), mats.at(2));

    newPlayer.addCustomAtk(newAtk);

    newPlayer.setSpecificSlot(newAtk, 0);

    cout << newAtk.thisEffects.size();

    while(newPlayer.getHealth() > 0)
    {
        combat(newPlayer, color);
        cout << "saving player\n";
        Saving::saveToFile(newPlayer, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
        cout << "saved player, now saving cus attacks.";
        Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", newPlayer.getCustomAtks());
    }

    
    

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
