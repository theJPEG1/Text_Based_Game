#include "Player.H"
#include "PlayerFactory.H"
#include "PrettyColors.H"
#include "attacksEffects.H"
#include "include/json.hpp"
    using json = nlohmann::json;
    using ordered_json = nlohmann::ordered_json;

#include <string>
    using std::string;
#include <fstream>
    using std::ifstream;
    using std::ofstream;
#include <iostream>
    using std::cin;
    using std::cout;

void allocateStatPoints(int& healthValue, int& strengthValue, int& dexterityValue, int& mindValue, string& nameValue);

Player PlayerFactory::createPlayer()
{
    int healthValue    =  10;
    int strengthValue  =   5;
    int dexterityValue =   5;
    int mindValue      =   5;
    string nameValue   =  "";

    allocateStatPoints(healthValue, strengthValue, dexterityValue, mindValue, nameValue);

    Player newPlayer(healthValue, healthValue, strengthValue, dexterityValue, mindValue, nameValue, 1 , 0, 50);

//default combat inventory
    ofstream combatF;
    ordered_json j;
    ordered_json attackIDs = j["Attack IDs"];

    combatF.open("playerData/playerCombatBook.json");

    attackIDs["Attack IDs"][0]["ID"] = "normal";
    attackIDs["Attack IDs"][1]["ID"] = "normal";
    attackIDs["Attack IDs"][2]["ID"] = "normal";
    attackIDs["Attack IDs"][3]["ID"] = "normal";
    attackIDs["Attack IDs"][4]["ID"] = "magicPunch";
    attackIDs["Attack IDs"][5]["ID"] = "magicPunch";
    attackIDs["Attack IDs"][6]["ID"] = "magicPunch";
    attackIDs["Attack IDs"][7]["ID"] = "magicPunch";
    

    combatF << attackIDs;

    std::ofstream outAttacks("playerData/playerCombatBook.json");
    outAttacks << attackIDs.dump(3);

    combatF.close();

    Attacks load;

    vector<Attacks> attacksFile = load.loadAttacks("playerData/PlayerAction/attacks.json");

    vector<Attacks> actionsToPlayer;

    cout << attacksFile.size() << "\n";

    for(size_t i = 0; i < attacksFile.size(); i++)
    {
        for(size_t o = 0; o < attackIDs["Attack IDs"].size(); o++)
        {
            if(attacksFile.at(i).id == attackIDs["Attack IDs"][o]["ID"])
            {
                actionsToPlayer.push_back(attacksFile.at(i));
            }
        }
        
    }

    newPlayer.setAllCombat(actionsToPlayer);
    
    return newPlayer;
};

Player PlayerFactory::loadFromFile(const string& filename)
{
    PrettyColors color;
    ifstream inFile;

    inFile.open(filename);
    ifstream attackFile;
    ifstream combatMagicFile;
    combatMagicFile.open("playerData/playerCombatBook.json");

    attackFile.open("playerData/PlayerAction/attacks.json");

    if(!inFile || !combatMagicFile || !attackFile)
    {
        cout << color.RED << "Error opening file.\n" << color.DEFAULT;
        exit(1);
    }

    json playerStats;
    inFile >> playerStats;

    int healthValue    = playerStats["hp"];
    int maxHealthValue = playerStats["maxHp"];
    int strengthValue  = playerStats["strength"];
    int dexterityValue = playerStats["dexterity"];
    int mindValue      = playerStats["mind"];
    string nameValue   = playerStats["name"];
    int levelValue     = playerStats["level"];

    Player newPlayer(healthValue, maxHealthValue, strengthValue, dexterityValue, mindValue, nameValue, levelValue, playerStats["xp"], playerStats["xpToNextLevel"]);

    newPlayer.setHealthPotionCount(playerStats["healthPotions"]);
    newPlayer.setManaPotionCount(playerStats["manaPotions"]);
    newPlayer.setStrengthPotionCount(playerStats["strengthPotions"]);
    newPlayer.setDexterityPotionCount(playerStats["dexterityPotions"]);

    //What does this portion do?
//  1. Reads in a json file from the loaction playerData/playerCombatBook.json
//  2. Opens a second file library with all the attacks and custom ones
//  3. Uses the playerCombatBook Json and the ID's inside to fill the players action library
//  4. Opens a third file that contains if the player knows the attack or not and push that in its own thing
//  
//   
    json j;
    json attackIDs = j["Attack IDs"];

    combatMagicFile >> attackIDs;

    Attacks load;
    vector<Attacks> actionsToPlayer;

    vector<Attacks> customAtks = load.loadAttacks("playerData/PlayerAction/customAttacks.json");

    for(size_t i = 0; i < customAtks.size(); i++)
    {
        for(size_t o = 0; o < attackIDs["Attack IDs"].size(); o++)
        {
            if(customAtks.at(i).id == attackIDs["Attack IDs"][o]["ID"])
            {
                actionsToPlayer.push_back(customAtks.at(i));
            }
        }
        
    }

    vector<Attacks> attacksFile = load.loadAttacks("playerData/PlayerAction/attacks.json");

    for(size_t i = 0; i < attacksFile.size(); i++)
    {
        for(size_t o = 0; o < attackIDs["Attack IDs"].size(); o++)
        {
            if(attacksFile.at(i).id == attackIDs["Attack IDs"][o]["ID"])
            {
                actionsToPlayer.push_back(attacksFile.at(i));
            }
        }
        
    }

    newPlayer.setAllCombat(actionsToPlayer);

    cout << newPlayer.getAllCombat().size() << "\n";


    inFile.close();
    combatMagicFile.close();
    
    return newPlayer;
}

void allocateStatPoints(int& healthValue, int& strengthValue, int& dexterityValue, int& mindValue, string& nameValue)
{
    PrettyColors colors;

    bool healthAllocated    = false;
    bool strengthAllocated  = false;
    bool dexterityAllocated = false;
    bool mindAllocated      = false;

    int allocationPoints  = 20;
    int pointsToSend      =  0;
    cin.ignore();
    cout << "What is your " << colors.YELLOW << "name: ";
    getline(cin, nameValue);

    cout << colors.DEFAULT;

    while (allocationPoints >= 1)
    {
        if(!healthAllocated)
        {
            cout << "You have " << allocationPoints << " Points left for allocation.\n";
            cout << "There are 4 stats: " << colors.CYAN << "Health | " << 
                colors.RED << "Strength | " << colors.GREEN << "Dexterity | " << colors.MAGENTA << "Mind |" << colors.DEFAULT << "\n"; 
            cout << "How many points towards " << colors.CYAN << "Health: ";
            cin >> pointsToSend;

            if(allocationPoints >= pointsToSend && pointsToSend >= 0 && allocationPoints > 0)
            {
                healthAllocated = true;
                healthValue += pointsToSend;
                allocationPoints -= pointsToSend;
                cout << colors.DEFAULT;

                colors.clearScreen();
            }

            else
            {
                cout << "\n" << colors.RED << "! INVALID INPUT !\n" << colors.DEFAULT;
            }
        }

        if(!strengthAllocated)
        {
            cout << "You have " << allocationPoints << " Points left for allocation.\n";
            cout << "There are 4 stats: " << colors.CYAN << "Health | " << 
                colors.RED << "Strength | " << colors.GREEN << "Dexterity | " << colors.MAGENTA << "Mind |" << colors.DEFAULT; 
            cout << "\nHow many points towards " << colors.RED << "Strength: ";
            cin >> pointsToSend;

            if(allocationPoints >= pointsToSend && pointsToSend >= 0 && allocationPoints > 0)
            {
                strengthAllocated = true;
                strengthValue += pointsToSend;
                allocationPoints -= pointsToSend;
                cout << colors.DEFAULT;

                colors.clearScreen();
            }

            else
            {
                cout << "\n" << colors.RED << "! INVALID INPUT !\n" << colors.DEFAULT;
            }
        }

        if(!dexterityAllocated)
        {
            cout << "You have " << allocationPoints << " Points left for allocation.\n";
            cout << "There are 4 stats: " << colors.CYAN << "Health | " << 
                colors.RED << "Strength | " << colors.GREEN << "Dexterity | " << colors.MAGENTA << "Mind |" << colors.DEFAULT; 
            cout << "\nHow many points towards " << colors.GREEN << "Dexterity: ";
            cin >> pointsToSend;

            if(allocationPoints >= pointsToSend && pointsToSend >= 0 && allocationPoints > 0)
            {
                dexterityAllocated = true;
                dexterityValue += pointsToSend;
                allocationPoints -= pointsToSend;
                cout << colors.DEFAULT;

                colors.clearScreen();
            }

            else
            {
                cout << "\n" << colors.RED << "! INVALID INPUT !\n" << colors.DEFAULT;
            }
        }

        if(!mindAllocated)
        {
            mindAllocated = true;
            mindValue += allocationPoints;
            allocationPoints -= allocationPoints;
        }
    }

    cin.ignore();
};
