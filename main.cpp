#include "Player.h"
#include "PlayerFactory.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "Combat.h"
#include "PrettyColors.h"
#include "Saving.h"
#include "Actions.h"
#include "attacksEffects.h"

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
    if(!j.is_null() && !j.empty())
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
        string temp;
        cout << "A story is much like that of a tree, but with branches that extend forever upwards and roots the burrow forever deeper."
             << "\nEach story has similar points but with widly differnt outcomes, and it hardly deviates from the origonal.\n";
    
        color.pauseTerminal(1);
        cout << "So I ask, Who are you?\n";

        color.pauseTerminal(2);

        newPlayer = PlayerFactory::createPlayer();

        color.clearScreen();

        cout << "Very well " << newPlayer.getName() << ", I look forward to seeing how your story plays out.\n";
        color.pauseTerminal(2);

        Saving::saveToFile(newPlayer, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
        playerExists = true;
    }

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


    GameState* gs = new GameState(newPlayer, cMats, allAtks);

    cout << &newPlayer;

    Actions action(gs);

    string loadArea = "Locations/Town1Day/town.json";

    

    while(gs->inGame)
    {
        loadArea = action.loadAreaFromJson(loadArea);
    }
    

    Saving::saveToFile(gs->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
    Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gs->player.getCustomAtks());
    Saving::saveInventory("playerData/playerInventorySave.json", gs->player);

    delete gs;
    
    

    return 0;
};

