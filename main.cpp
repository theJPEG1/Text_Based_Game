#include "Player.H"
#include "PlayerFactory.H"
#include "Enemy.H"
#include "EnemyFactory.H"
#include "Combat.H"
#include "PrettyColors.H"
#include "Saving.H"
#include "Actions.H"
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

    CraftingMaterials load;
    vector<CraftingMaterials> mats = load.loadCraftingMaterialss("GameData/craftingMaterials.json");
    map<string, CraftingMaterials> cMats;

    for(size_t i = 0; i < mats.size(); i++)
    {
        cMats[mats.at(i).id] = mats.at(i);
    }

    Attacks loadAtk;
    vector<Attacks> aAtk = loadAtk.loadAttacks("playerData/PlayerAction/attacks.json");
    map<string, Attacks> allAtks;

    for(size_t i = 0; i < aAtk.size(); i++)
    {
        allAtks[aAtk.at(i).id] = aAtk.at(i);
    }


    GameState gs(newPlayer, cMats, allAtks);

    Actions action(gs);


    while(inGame)
    {
        action.loadAreaFromJson("Town1Day/town.json");

        if(newPlayer.getHealth() <= 0)
        {
            inGame = false;
        }
    }
    
    

    return 0;
};

