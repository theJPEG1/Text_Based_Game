#include "Actions.H"

Actions::Actions(GameState* gameState)
{
    gc = gameState;

    actionMap["buyItems"] = std::bind(&Actions::buyItems, this);
    actionMap["craftItems"] = std::bind(&Actions::craftItems, this);
    actionMap["hearRumor"] = std::bind(&Actions::rumors, this);;
    actionMap["sellItems"] = std::bind(&Actions::sellItems, this);
    actionMap["viewGuildCard"] = std::bind(&Actions::viewGuildCard, this);
    actionMap["viewInventory"] = std::bind(&Actions::viewInventory, this);
    actionMap["effectView"] = std::bind(&Actions::printEffectList, this);
    actionMap["wellTalk"] = std::bind(&Actions::wellTalk, this);
    actionMap["tossInACoin"] = std::bind(&Actions::tossInACoin, this);

    actionMap["fight"] = std::bind(&Actions::fight, this);

    actionMap["healthPotion"] = std::bind(&Actions::addHealthPots, this);
    actionMap["manaPotion"] = std::bind(&Actions::addManaPots, this);
};

void Actions::loadAreaFromJson(string jsonToLoad)
{
    gc->colors.clearScreen();

    ifstream file(jsonToLoad);

    if (!file.is_open()) 
    {
        cout << "Failed to open " << jsonToLoad << "\n";
    }

    currentJson = jsonToLoad;

    json data;
    file >> data;

    string header = data["header"];

    json actions = data["Actions"];

    int keyboardInput = 0;
    while(keyboardInput <= 0 || keyboardInput > actions.size())
    {
        cout << "\n" << header << "\n";

        for (size_t i = 0; i < actions.size(); ++i)
        {
            if(actions.size() <= 4)
            {
                if(i % 2 == 0)
                {
                    cout << "\n";
                }
            }
            else
            {
                if(i % 3 == 0)
                {
                    cout << "\n";
                }
            }

            string actionPrint = actions[i]["actionDescription"];
            cout << actionPrint;

            if(actionPrint.length() < 30 && actionPrint.length() > 17)
            {
                cout << "\t";
            }

            if(actionPrint.length() < 16)
            {
                cout << "\t";
            }

            if(actionPrint.length() < 8)
            {
                cout << "\t";
            }
        
        }

        cout << "\n-> ";

        cin >> keyboardInput;

        string actionToCheck = actions[keyboardInput-1]["target"];

        if(actionToCheck.substr(actionToCheck.length() - 5, 5) == ".json")
        {
            file.close();
            loadAreaFromJson(actionToCheck);
        }

        else
        {
            actionMap.find(actionToCheck)->second();
        }

        keyboardInput = 0;
        
    }

    file.close();
    gc->colors.clearScreen();
};

void Actions::buyItems()
{
    gc->colors.clearScreen();

    ifstream file(currentJson);

    if (!file.is_open()) {
        cout << "Failed to open " << currentJson << "\n";
        return;
    }


    json data;
    file >> data;

    string type = data["type"];
    string buyMessage = data["buyMessage"];

    json inventory = data["Inventory"];

    int keyboardInput = 0;

    while(keyboardInput <= 0 || keyboardInput > inventory.size())
    {
        cout << "\n" << buyMessage << "\n";
        cout << "You have " << gc->player.getNovas() << " Novas.\n";

        for (size_t i = 0; i < inventory.size(); ++i)
        {
            if(inventory.size() <= 4)
            {
                if(i % 2 == 0)
                {
                    cout << "\n";
                }
            }
            else
            {
                if(i % 3 == 0)
                {
                    cout << "\n";
                }
            }

            string actionDesc = inventory[i]["actionDescription"];
            cout << actionDesc;

            if(!inventory[i]["Cost"].is_null())
            {
                int cost = inventory[i]["Cost"];
                cout << " | " << cost << " Novas\t";

                if(actionDesc.length() < 10)
                {
                    cout << "\t";
                }
            }

            else
            {
                cout << "\t";
            }
        }

        cout << "\n-> ";

        cin >> keyboardInput;

        if(!inventory[keyboardInput - 1]["Cost"].is_null())
        {
            if(gc->player.getNovas() >= inventory[keyboardInput - 1]["Cost"])
            {
                int cost = inventory[keyboardInput - 1]["Cost"];
                gc->player.increaseNovas(-cost);

                string idToLocation = inventory[keyboardInput - 1]["ID"];

                if(type == "blacksmith")
                {
                    gc->player.addCombatAttacks(gc->atks.find(idToLocation)->second);
                    gc->player.setSpecificSlot(gc->atks.find(idToLocation)->second, 0);
                }

                else if(type == "shop")
                {
                    potionsToAdd = inventory[keyboardInput - 1]["Amt"];
                }
            }
        }
    }

    loadAreaFromJson("Locations/" + currentJson);

    gc->colors.clearScreen();
};

void Actions::craftItems()
{
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");

    gc->colors.clearScreen();

    ifstream file(currentJson);

    if (!file.is_open()) {
        cout << "Failed to open " << currentJson << "\n";
        return;
    }


    json data;
    file >> data;

    string type = data["type"];
    string craftMes = data["craftMessage"];
    int maxRare = data["maxRarity"];

    string keyboardString = "";
    gc->player.printInventory(maxRare);

    vector <CraftingMaterials> crafting;

    int count = 0;
    bool matAdded = false;
    cout << "\nPick a material (BACK to go back)";
    

    while(count < 3 && keyboardString != "BACK")
    {
        cout << "\n-> ";
        getline(cin, keyboardString);
        
        for(size_t i = 0; i < cMats.size(); i++)
        {
            if(matAdded == false)
            {
                if(keyboardString == cMats.at(i).name )
                {
                    crafting.push_back(cMats.at(i));
                    matAdded = true;
                    count++;
                }
            }
        }

        matAdded = false;

        cout << "\n";
    }

    if(keyboardString != "BACK")
    {
        Attacks customAtk = customAtk.createAttack(crafting.at(0), crafting.at(1), crafting.at(2));
    
        gc->player.addCustomAtk(customAtk);

        if(customAtk.type == "spell")
        {
            gc->player.addCombatSpells(customAtk);
            gc->player.setSpecificSlot(customAtk, 4);
        }

        else if(customAtk.type == "attack")
        {
            gc->player.addCombatAttacks(customAtk);
            gc->player.setSpecificSlot(customAtk, 0);
        }

        cout << "Custom attack created and Slotted\n";

        for(size_t i = 0; i < crafting.size(); i++)
        {
            gc->player.addToInventory(cMats.at(i), -1);
        }
    }

    
}

void Actions::sellItems()
{
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");
    CraftingMaterials sellMat;

    gc->colors.clearScreen();

    ifstream file(currentJson);

    if (!file.is_open()) {
        cout << "Failed to open " << currentJson << "\n";
        return;
    }


    json data;
    file >> data;

    string sellMes = data["sellMessage"];

    cout << sellMes << "\n";

    gc->player.printInventory(1000);

    cout << "\nWhat would you like to sell? (BACK to go back)\n-> ";

    string keyboardString = "";
    int keyboardInput = 0;
    bool matAdded = false;
    bool itemSold = false;

    cin.ignore();
    getline(cin, keyboardString);

    if(keyboardString != "BACK")
    {
        for(size_t i = 0; i < cMats.size(); i++)
        {
            if(matAdded == false)
            {
                if(keyboardString == cMats.at(i).name )
                {
                    sellMat = cMats.at(i);
                    matAdded = true;
                }

                else
                {
                    sellMat.name = "NotFound";
                }
            }
        }

        if(sellMat.name != "NotFound")
        {
            cout << "\nHow many? That one is worth " << sellMat.price << " novas.";

            while(!itemSold)
            {
                cout << "\n-> ";
                cin >> keyboardInput;

                if(keyboardInput > 0 && keyboardInput <= gc->player.getInventoryAmount(sellMat))
                {
                    gc->player.addToInventory(sellMat, -keyboardInput);
                    int novasToAdd = sellMat.price * keyboardInput;

                    cout << "You made " << novasToAdd << " Novas!\n";
                    gc->player.increaseNovas(novasToAdd);
                    itemSold = true;
                }

                else
                {
                    cout << "\n! INVALID AMOUNT !\n";
                    keyboardInput = 0;
                }
            }
        }

        else
        {
            cout << "\n! INVALID MATERIAL NAME !\n";
        }
    }
};

void Actions::rumors()
{
    cout << "\n<INSERT RUMOR HERE>\n";
};

void Actions::viewGuildCard()
{
    gc->colors.clearScreen();
    gc->player.printGuildCard();
    cout << "\n";
};

void Actions::viewInventory()
{
    gc->colors.clearScreen();
    gc->player.printInventory(1000);
    cout << "\n";
};

void Actions::printEffectList()
{
    gc->colors.clearScreen();
    for(size_t i = 0; i < effects.size(); i++)
    {
        cout << effects.at(i) << "\t";

        if(effects.at(i).length() <= 6)
        {
            cout << "\t";
        }

        if (i % 2 == 0) 
        {
            std::cout << "\n";
        }
    }
};

void Actions::wellTalk()
{
    gc->colors.clearScreen();

    vector<string> wellTalks =
    {
        "Some say that this well is encahnted.\nA coin for a wish.\nI don't believe it though.\n",
        "I heard that there is a goblin that set up this well.\nIt's all just a ploy so he can get rich!\n",
        "I tossed in a coin and I feel better.\nStronger, faster, luckier, just all of it, better!\n",
        "I wonder what's at the bottom of the well?\nIt just looks like it goes on forever.\n", //quest start for bottom of the well option
        "This well is a curse on the town. People come and throw coins expecting riches.\nI know better!\n"
    };

    //better message logic so i can skew things
    string message = wellTalks.at(rand() % wellTalks.size());

    if(message == wellTalks.at(3))
    {
        //start the bottom of the well quest
    }

    //logic to add as a quest

    cout << message;
};

void Actions::tossInACoin()
{

    ifstream file(currentJson);

    if (!file.is_open()) {
        cout << "Failed to open " << currentJson << "\n";
        return;
    }

    json data;
    file >> data;

    json outData;
    file.close();

   

    int curCoinAmt = data.value("coinAmt", 0);

    if(gc->player.getNovas() > 0 && curCoinAmt <= 5025)
    {
        gc->player.increaseNovas(-1);

        curCoinAmt++;

        if(curCoinAmt >= 5000)
        {
            int chanceEncounter = (rand() % 100 + 1) - gc->player.getLuck();
            if(chanceEncounter > 10)
            {
                cout << "You watch as your coin floats down the well, with nothing in return.\n";
            }

            else if(chanceEncounter <= 10 && chanceEncounter > 5)
            {
                int whichStat = rand() % 5 + 1;

                if(whichStat == 1)
                {
                    cout << "Your health increases!\n";
                    gc->player.increaseMaxHealth(1);
                }

                else if(whichStat == 2)
                {
                    cout << "Your strength increases!\n";
                    gc->player.increaseStrength(1);
                }

                else if(whichStat == 3)
                {
                    cout << "Your dexterity increases!\n";
                    gc->player.increaseDexterity(1);
                }

                else if(whichStat == 4)
                {
                    cout << "Your mind increases!\n";
                    gc->player.increaseMind(1);
                }

                else if(whichStat == 5)
                {
                    cout << "Your luck increases!\n";
                    gc->player.increaseLuck(1);
                }
            }

            else 
            {
                cout << "Everything grow stronger!\n";
                    gc->player.increaseMaxHealth(1);
                    gc->player.increaseStrength(1);
                    gc->player.increaseDexterity(1);
                    gc->player.increaseMind(1);
                    gc->player.increaseLuck(1);
            }
        }

        else if( curCoinAmt < 5000 && curCoinAmt >= 2000)
        {
            int chanceEncounter = (rand() % 100 + 1) - gc->player.getLuck();
            if(chanceEncounter > 7)
            {
                cout << "You watch as your coin floats down the well, with nothing in return.\n";
            }

            else if(chanceEncounter <= 7 && chanceEncounter > 3)
            {
                int whichStat = rand() % 4 + 1;

                if(whichStat == 1)
                {
                    cout << "Your health increases!\n";
                    gc->player.increaseMaxHealth(1);
                }

                else if(whichStat == 2)
                {
                    cout << "Your strength increases!\n";
                    gc->player.increaseStrength(1);
                }

                else if(whichStat == 3)
                {
                    cout << "Your dexterity increases!\n";
                    gc->player.increaseDexterity(1);
                }

                else if(whichStat == 4)
                {
                    cout << "Your mind increases!\n";
                    gc->player.increaseMind(1);
                }
            }

            else 
            {
                cout << "Everything grow stronger!\n";
                    gc->player.increaseMaxHealth(1);
                    gc->player.increaseStrength(1);
                    gc->player.increaseDexterity(1);
                    gc->player.increaseMind(1);
            }
        }

        else if(curCoinAmt < 2000)
        {
            int chanceEncounter = (rand() % 100 + 1) + gc->player.getLuck();

            if(chanceEncounter < 96)
            {
                cout << "You watch as your coin floats down the well, with nothing in return.\n";
            }

            else if(chanceEncounter >= 96 && chanceEncounter < 99)
            {
                int whichStat = rand() % 4 + 1;

                if(whichStat == 1)
                {
                    cout << "Your health increases!\n";
                    gc->player.increaseMaxHealth(1);
                }

                else if(whichStat == 2)
                {
                    cout << "Your strength increases!\n";
                    gc->player.increaseStrength(1);
                }

                else if(whichStat == 3)
                {
                    cout << "Your dexterity increases!\n";
                    gc->player.increaseDexterity(1);
                }

                else if(whichStat == 4)
                {
                    cout << "Your mind increases!\n";
                    gc->player.increaseMind(1);
                }
            }

            else 
            {
                cout << "Everything grow stronger!\n";
                    gc->player.increaseMaxHealth(1);
                    gc->player.increaseStrength(1);
                    gc->player.increaseDexterity(1);
                    gc->player.increaseMind(1);
            }
        }
    }

    else if(curCoinAmt >= 5025)
    {
        cout << "The well once full of water is now replaced with Silver Novas.\n";
    }

    else
    {
        cout << "You stare at the water wishing you had a coin.\n";
    }


    data["coinAmt"] = curCoinAmt;
    ofstream outFile(currentJson);
    outFile << data.dump(4);
    outFile.close();

    Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
    Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());

    gc->colors.pauseTerminal(3);
    gc->colors.clearScreen();
};

void Actions::fight()
{
    gc->player.increaseHealth(gc->player.getMaxHealth());
    vector<vector<Enemy>> forest = EnemyFactory::loadRegionEnemy("Forest");

    Combat forestCombat(gc, forest, "Forest");

    forestCombat.determineEnemy();
    //forestCombat.printGui();

    forestCombat.newCombatTest();

    cout << gc->colors.YELLOW << "You survived the encounter!\n" << gc->colors.DEFAULT;

    Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
    Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());
    Saving::saveInventory("playerData/playerInventorySave.json", gc->player);
};

void Actions::addHealthPots()
{
    gc->player.increaseHealthPotionCount(potionsToAdd);
}

void Actions::addManaPots()
{
    gc->player.increaseManaPotionCount(potionsToAdd);
}

