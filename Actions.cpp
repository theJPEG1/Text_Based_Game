#include "Actions.H"

Actions::Actions(Player& p)
{
    player = p;

    actionMap["buyItems"] = std::bind(&Actions::buyItems, this);
    actionMap["craftItems"] = std::bind(&Actions::craftItems, this);
    actionMap["hearRumor"];
    actionMap["sellItems"] = std::bind(&Actions::sellItems, this);


    actionMap["healthPotion"] = std::bind(&Actions::addHealthPots, this);
    actionMap["manaPotion"] = std::bind(&Actions::addManaPots, this);
    

    loadCraftingMats("GameData/craftingMaterials.json");
    loadAllAttacks("playerData/PlayerAction/attacks.json");

    //incialize a map of crafting mats and of attakcs
    // Map <string id, craftingMats mat>
    // Map <string id, Attacks atk>
};

void Actions::loadCraftingMats(string fileLocation)
{
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss(fileLocation);

    for(size_t i = 0; i < cMats.size(); i++)
    {
        materials[cMats.at(i).id] = cMats.at(i);
    }
};

void Actions::loadAllAttacks(string fileLocation)
{
    Attacks load;

    vector<Attacks> attacksFile = load.loadAttacks(fileLocation);

    for(size_t i = 0; i < attacksFile.size(); i++)
    {
        playerAttacks[attacksFile.at(i).id] = attacksFile.at(i);
    }
};

void Actions::loadAreaFromJson(string jsonToLoad)
{
    color.clearScreen();

    ifstream file(jsonToLoad);

    if (!file.is_open()) {
        cout << "Failed to open " << jsonToLoad << "\n";
        return;
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
            cout << actionPrint << "\t";
            if(actionPrint.length() < 10)
            {
                cout << "\t";
            }
        }

        cout << "\n-> ";

        cin >> keyboardInput;

        string actionToCheck = actions[keyboardInput-1]["target"];

        cout << actionToCheck.substr(actionToCheck.length() - 5, 5);

        if(actionToCheck.substr(actionToCheck.length() - 5, 5) == ".json")
        {
            file.close();
            cout << actionToCheck << "\n";
            loadAreaFromJson("Locations/" + actionToCheck);
        }

        else
        {
            actionMap.find(actionToCheck)->second();
        }

        keyboardInput = 0;
        
    }

    file.close();
    color.clearScreen();
};

void Actions::buyItems()
{
    color.clearScreen();

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
        cout << "You have " << player.getNovas() << " Novas.\n";

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
            if(player.getNovas() >= inventory[keyboardInput - 1]["Cost"])
            {
                int cost = inventory[keyboardInput - 1]["Cost"];
                player.increaseNovas(-cost);

                string idToLocation = inventory[keyboardInput - 1]["ID"];

                if(type == "blacksmith")
                {
                    player.addCombatAttacks(playerAttacks.find(idToLocation)->second);
                    player.setSpecificSlot(playerAttacks.find(idToLocation)->second, 0);
                }

                else if(type == "shop")
                {
                    potionsToAdd = inventory[keyboardInput - 1]["Amt"];
                }
            }
        }
    }

    loadAreaFromJson("Locations/" + currentJson);

    color.clearScreen();
};

void Actions::craftItems()
{
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");

    color.clearScreen();

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
    player.printInventory(maxRare);

    vector <CraftingMaterials> crafting;

    int count = 0;
    bool matAdded = false;
    cout << "\nPick a material";
    

    while(count < 3)
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

    Attacks customAtk = customAtk.createAttack(crafting.at(0), crafting.at(1), crafting.at(2));
    
    player.addCustomAtk(customAtk);

    if(customAtk.type == "spell")
    {
        player.addCombatSpells(customAtk);
        player.setSpecificSlot(customAtk, 4);
    }

    else if(customAtk.type == "attack")
    {
        player.addCombatAttacks(customAtk);
        player.setSpecificSlot(customAtk, 0);
    }

    cout << "Custom attack created and Slotted\n";
}

void Actions::sellItems()
{
    CraftingMaterials cLoad;

    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");
    CraftingMaterials sellMat;

    color.clearScreen();

    ifstream file(currentJson);

    if (!file.is_open()) {
        cout << "Failed to open " << currentJson << "\n";
        return;
    }


    json data;
    file >> data;

    string sellMes = data["sellMessage"];

    cout << sellMes << "\n";

    player.printInventory(1000);

    cout << "What would you like to sell? (BACK to go back)\n-> ";

    string keyboardString = "";
    int keyboardInput = 0;
    bool matAdded = false;

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
            }
        }

        cout << "\n How many? That one is worth " << sellMat.price << " novas.";

        while(keyboardInput <= 0 && keyboardInput > player.getInventoryAmount(sellMat))
        {
            cout << "\n-> ";
            cin >> keyboardInput;

            if(keyboardInput > 0 && keyboardInput <= player.getInventoryAmount(sellMat))
            {
                player.addToInventory(sellMat, -keyboardInput);
                int novasToAdd = sellMat.price * keyboardInput;

                cout << "You made " << novasToAdd << " Novas!\n";
                player.increaseNovas(novasToAdd);
            }

            else
            {
                cout << "\n! INVALID AMOUNT !\n";
            }
        }
    }
    
    
};

void Actions::addHealthPots()
{
    player.increaseHealthPotionCount(potionsToAdd);
}

void Actions::addManaPots()
{
    player.increaseManaPotionCount(potionsToAdd);
}

