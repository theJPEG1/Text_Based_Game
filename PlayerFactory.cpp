#include "PlayerFactory.H"


PrettyColors PlayerFactory::colors;

/**
 * @brief creates a brand new player
 */

Player PlayerFactory::createPlayer()
{
    int healthValue    =  10;
    int dexterityValue =   5;
    int strengthValue  =   5;
    int mindValue      =   5;

    string monthValue =  "";
    string nameValue  =  "";
    string timeValue  =  "";
    int dayValue      =   0;

    createPlayerBirthday(nameValue, monthValue, timeValue, dayValue);
    allocateStatPoints(healthValue, strengthValue, dexterityValue, mindValue);

    Player newPlayer(nameValue, monthValue, timeValue, dayValue, healthValue, strengthValue, dexterityValue, mindValue);

    //month value increases
        if(monthValue == "Sirtus")
        {
            //health
            newPlayer.increaseMaxHealth(2);
            newPlayer.increaseHealth(2);
        }

        else if(monthValue == "Thetus")
        {
            //strength
            newPlayer.increaseStrength(2);
        }

        else if(monthValue == "Motus")
        {
            //dexterity
            newPlayer.increaseDexterity(2);
        }

        else if(monthValue == "Zectus")
        {
            //mind
            newPlayer.increaseMind(2);
        }

        else if(monthValue == "Pentus")
        {
            //luck
            newPlayer.increaseLuck(2);
        }

    //day value increases

        if(dayValue >= 1 && dayValue <= 3)
        {
            newPlayer.increaseMaxHealth(1);
            newPlayer.increaseHealth(1);
        }

        else if(dayValue >= 4 && dayValue <= 6)
        {
            newPlayer.increaseStrength(1);
        }

        else if(dayValue >= 7 && dayValue <= 9)
        {
            newPlayer.increaseDexterity(1);
        }

        else if(dayValue >= 10 && dayValue <= 12)
        {
            newPlayer.increaseMind(1);
        }

        else if(dayValue >= 13 && dayValue <= 15)
        {
            newPlayer.increaseLuck(1);
        }

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

            if(attacksFile.at(i).type == "spell")
            {
                newPlayer.addCombatSpells(attacksFile.at(i));
            }
        }
        
    }

    newPlayer.setAllCombat(actionsToPlayer);

    //inventorty
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");

    for(size_t i = 0; i < cMats.size(); i++)
    {
        newPlayer.addToInventory(cMats.at(i), 1);
    }

    newPlayer.increaseNovas(20);
    
    return newPlayer;
};


/**
 * @brief Loads in a player from a file
 */
Player PlayerFactory::loadFromFile(const string& filename)
{
    ifstream inFile;

    inFile.open(filename);
    ifstream attackFile;
    ifstream combatMagicFile;
    combatMagicFile.open("playerData/playerCombatBook.json");

    attackFile.open("playerData/PlayerAction/attacks.json");

    if(!inFile || !combatMagicFile || !attackFile)
    {
        cout << colors.RED << "Error opening file.\n" << colors.DEFAULT;
        exit(1);
    }

    json playerStats;
    inFile >> playerStats;

    //player info
        string nameValue   = playerStats["name"];
        string monthValue   = playerStats["month"];
        string timeValue   = playerStats["time"];
        int    dayValue   = playerStats["day"];
    
    //player stats
        int healthValue    = playerStats["hp"];
        int maxHealthValue = playerStats["maxHp"];
        int strengthValue  = playerStats["strength"];
        int dexterityValue = playerStats["dexterity"];
        int mindValue      = playerStats["mind"];
        int luckValue = playerStats["luck"];

    //Player leveling
        int levelValue     = playerStats["level"];
        int curXp = playerStats["xp"];
        int xpToLevel = playerStats["xpToNextLevel"];

    Player newPlayer(nameValue, monthValue, dayValue, timeValue,
                     healthValue, maxHealthValue, strengthValue, dexterityValue,
                     mindValue, luckValue, levelValue, curXp, xpToLevel);
        
    newPlayer.increaseHealthPotionCount(playerStats["healthPotions"]);
    newPlayer.increaseManaPotionCount(playerStats["manaPotions"]);

    newPlayer.increaseNovas(playerStats["novas"]);

    //What does this portion do?
//  1. Reads in a json file from the loaction playerData/playerCombatBook.json
//  2. Opens a second file library with all the attacks and custom ones
//  3. Uses the playerCombatBook Json and the ID's inside to fill the players action library
//  4. Opens a third file that contains if the player knows the attack or not and push that in its own thing

    json j;
    json attackIDs = j["Attack IDs"];

    combatMagicFile >> attackIDs;

    Attacks load;
    vector<Attacks> actionsToPlayer;

    vector<Attacks> customAtks = load.loadAttacks("playerData/PlayerAction/customAttacks.json");

    cout << customAtks.size() << "\n";
    for(size_t i = 0; i < customAtks.size(); i++)
    {
        for(size_t o = 0; o < attackIDs["Attack IDs"].size(); o++)
        {
            if(customAtks.at(i).id == attackIDs["Attack IDs"][o]["ID"])
            {
                actionsToPlayer.push_back(customAtks.at(i));
            }
        }

        if(customAtks.at(i).type == "spell")
        {
            newPlayer.addCombatSpells(customAtks.at(i));
        }

        else if(customAtks.at(i).type == "attack")
        {
            newPlayer.addCombatAttacks(customAtks.at(i));
        }
        

        newPlayer.addCustomAtk(customAtks.at(i));
    }

    vector<Attacks> attacksFile = load.loadAttacks("playerData/PlayerAction/attacks.json");

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

        if(attacksFile.at(i).type == "spell")
        {
            newPlayer.addCombatSpells(attacksFile.at(i));
        }

        else if(attacksFile.at(i).type == "attack")
        {
            newPlayer.addCombatAttacks(attacksFile.at(i));
        }
    }

    newPlayer.setAllCombat(actionsToPlayer);

    cout << newPlayer.getAllCombat().size() << "\n";


    inFile.close();
    combatMagicFile.close();

    

    //opening the file for crafing materials
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");
    ifstream craftInventory("playerData/playerInventorySave.json");

    if(!craftInventory.is_open()) 
    {
        cout << "Error opening playerInventory.json\n";
    }

    json jInventory;
    craftInventory >> jInventory;
    craftInventory.close();

    for (size_t i = 0; i < jInventory.size(); i++)
    {
        string id = jInventory[i]["id"];
        int amount = jInventory[i]["amount"];

        // Find the matching crafting material by ID
        for (size_t j = 0; j < cMats.size(); j++)
        {
            if (cMats[j].id == id)
            {
                newPlayer.addToInventory(cMats[j], amount);
                break; // stop searching once found
            }
        }
    }
    
    return newPlayer;
}


/**
 * @brief allows the player to allocate their stats where they want them
 * @param healthValue the value to modify to make the player health
 * @param strengthValue the value to modify to make the player stregnth
 * @param dexterityValue the value to modify to make the player dexterity
 * @param mindValue the value to modify to make the player mind
 */
void PlayerFactory::allocateStatPoints(int& healthValue, int& strengthValue, int& dexterityValue, int& mindValue)
{
    bool healthAllocated    = false;
    bool strengthAllocated  = false;
    bool dexterityAllocated = false;
    bool mindAllocated      = false;

    int allocationPoints  = 20;
    int pointsToSend      =  0;

    cout << colors.DEFAULT;

    while (allocationPoints > 0)
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
};


/**
 * @brief allows the player to make their birthday
 * @param name the value to modify to make the player name
 * @param monthBorn the value to modify to make the player month they aer born
 * @param timeBorn the value to modify to make the player time they are born
 * @param dayBorn the value to modify to make the player day they are born
 */
void PlayerFactory::createPlayerBirthday(string& name, string& monthBorn, string& timeBorn, int& dayBorn)
{
    bool nameCreated = false;
    bool monthSelected = false;
    bool timeSelected = false;
    bool daySelected = false;

    vector<string> months = {"Salumen", "Fortismen", "Aglismen", "Magimen", "Felixmen"};
    vector<string> times = {"Day", "Afternoon", "Night"};
    
    while(!nameCreated)
    {
        colors.clearScreen();
        cout << colors.YELLOW << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        if(name.length() > 10)
        {
            cout << colors.RED << "\n! Error (Name longer than 10) Try Again!\n" << colors.DEFAULT;
        }

        else
        {
            nameCreated = true;
        }
    }

    cout << colors.DEFAULT;

    while(!monthSelected)
    {
        colors.clearScreen();

        cout << colors.RED << "(THIS CANNOT BE CHANGED LATER)\n" << colors.DEFAULT;

        cout << "Salumen borns have moe vitality\n"
             << "Fortismen borns are stronger\n"
             << "Aglismen borns are more agile\n"
             << "Magimen borns are more adept in magic\n"
             << "Felixmen borns are rare and considered lucky\n";

        cout << "What Month where you born: ";

        
        getline(cin, monthBorn);

        for(size_t i = 0; i < months.size(); i++)
        {
            if(monthBorn == months.at(i))
            {
                monthSelected = true;
            }
        }

        if(!monthSelected)
        {
            cout << colors.RED << "\n! Error (Invalid Input) Try Again!\n" << colors.DEFAULT;
        }

        cout << colors.DEFAULT;
    }

    while(!timeSelected)
    {
        colors.clearScreen();

        cout << colors.RED << "(THIS CANNOT BE CHANGED LATER)\n" << colors.DEFAULT;
        cout << "Day | Afternoon | Night\n";

        cout << "What time where you born: ";

        getline(cin, timeBorn);

        for(size_t i = 0; i < times.size(); i++)
        {
            if(timeBorn == times.at(i))
            {
                timeSelected = true;
            }
        }

        if(!timeSelected)
        {
            cout << colors.RED << "\n! Error (Invalid Input) Try Again!\n" << colors.DEFAULT;
        }

        cout << colors.DEFAULT;
    }

    while(!daySelected)
    {
        colors.clearScreen();

        cout << colors.RED << "(THIS CANNOT BE CHANGED LATER)\n" << colors.DEFAULT;

        cout << "What day of the month (1-15) where you born: ";

        cin >> dayBorn;

        if(dayBorn <= 15 || dayBorn > 0)
        {
            daySelected = true;
        }

        else
        {
            cout << colors.RED << "\n! Error (Invalid Input) Try Again!\n" << colors.DEFAULT;
        }

        cout << colors.DEFAULT;
    }

}