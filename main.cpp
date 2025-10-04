#include "Player.H"
#include "PlayerFactory.H"
#include "Enemy.H"
#include "EnemyFactory.H"
#include "Combat.H"
#include "PrettyColors.H"
#include "Saving.H"
#include "Spells.H"

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

    int i = 0;
    while(i < 5)
    {
        combat(newPlayer, color);
        Saving::saveToFile(newPlayer, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
        i++;
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

    vector<Enemy> forest = EnemyFactory::loadRegionEnemy("Forest");

    Combat forestCombat(newPlayer, forest, "Forest");

    forestCombat.determineEnemy();
    //forestCombat.printGui();

    forestCombat.newCombatTest();

    cout << color.YELLOW << "You survived the encounter!\n" << color.DEFAULT;
};

void craftSpell(Player& newPlayer, PrettyColors& color)
{
    vector<CraftingMaterial> matsUsed;
    vector<CraftingMaterial> allSpellMats { CraftingMaterial("?", "SPELL", 1, 4, 320, "NOTHING"), CraftingMaterial("Multi", "SPELL", 1, 4, 320, "MULTICAST"), CraftingMaterial ("Strap", "SPELL", 1, 4, 320, "BIND"), CraftingMaterial("Counter", "Spell", 5, 5, 320, "COUNTER") };

    cout << "Choose up to 3 spell materials:\n[0] Empty\t";

    for(size_t i = 1; i < allSpellMats.size(); i ++)
    {
        cout << "[" << i << "] " << allSpellMats.at(i).getName() << " | Effect: " << allSpellMats.at(i).getEffect() << "\t";

        if(i % 2 == 0)
        {
            cout << "\n";
        }
    }

    cout << matsUsed.size();

    int keyboardInput = -1;
    while(matsUsed.size() < 3)
    {
        cout << "-> ";
        cin >> keyboardInput;

        matsUsed.push_back(allSpellMats.at(keyboardInput));

        cout << "\n" << matsUsed.at(matsUsed.size() - 1).getName() << " Selected.\n";
    }

    Spells newSpell = Spells::craftedSpell(matsUsed.at(0), matsUsed.at(1), matsUsed.at(2));
    newPlayer.setCombatBook(0, newSpell);
};
