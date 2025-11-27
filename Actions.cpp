#include "Actions.h"

Actions::Actions(GameState* gameState)
{
    gc = gameState;

    actionMap["buyItems"] = std::bind(&Actions::buyItems, this);
    actionMap["craftItems"] = std::bind(&Actions::craftItems, this);
    actionMap["hearRumor"] = std::bind(&Actions::rumors, this);;
    actionMap["sellItems"] = std::bind(&Actions::sellItems, this);
    actionMap["viewGuildCard"] = std::bind(&Actions::viewGuildCard, this);
    actionMap["viewInventory"] = std::bind(&Actions::viewInventory, this);
    actionMap["viewQuests"] = std::bind(&Actions::viewQuests, this);
    
    actionMap["effectView"] = std::bind(&Actions::printEffectList, this);
    actionMap["wellTalk"] = std::bind(&Actions::wellTalk, this);
    actionMap["tossInACoin"] = std::bind(&Actions::tossInACoin, this);

    actionMap["barKeepTalk"] = std::bind(&Actions::barKeepTalk, this);
    actionMap["drunkenTalk"] = std::bind(&Actions::drunkenTalk, this);
    actionMap["buyRoom"] = std::bind(&Actions::buyRoom, this);

    actionMap["swimming"] = std::bind(&Actions::wellSwim, this);
    actionMap["seduceDoor"] = std::bind(&Actions::seduceWellDoor, this);
    actionMap["wellKey"] = std::bind(&Actions::wellKey, this);

    actionMap["keyAsk"] = std::bind(&Actions::keyAsk, this);

    actionMap["fight"] = std::bind(&Actions::fight, this);

    actionMap["healthPotion"] = std::bind(&Actions::addHealthPots, this);
    actionMap["manaPotion"] = std::bind(&Actions::addManaPots, this);

    actionMap["saveQuit"] = std::bind(&Actions::saveQuit, this);  

    actionMap["efEncounter"] = std::bind(&Actions::efEncounter, this);
    actionMap["efForage"] = std::bind(&Actions::efForage, this);

    actionMap["efHorseCartPil"] = std::bind(&Actions::efHorseCartPil, this);
    actionMap["efHorseCartHelp"] = std::bind(&Actions::efHorseCartHelp, this);
    actionMap["fairyRelease"] = std::bind(&Actions::fairyRelease, this);

    actionMap["makeCamp"] = std::bind(&Actions::makeCamp, this);
    actionMap["pillageCamp"] = std::bind(&Actions::pillageCamp, this);

    actionMap["healWolf"] = std::bind(&Actions::healWolf, this);
    actionMap["killWolf"] = std::bind(&Actions::killWolf, this);

    actionMap["pickRose"] = std::bind(&Actions::pickRose, this);


};

string Actions::loadAreaFromJson(string jsonToLoad)
{
    string returnVal = "";
    vector<string> locationsExtras;
    swimDepth = 0;
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

    size_t append = 0;
    while(static_cast<size_t>(keyboardInput) <= 0 || static_cast<size_t>(keyboardInput) > actions.size())
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
            cout <<  "[" << i + 1 << "] " << actionPrint;

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

            append = i + 1;

        }

        json questActions;
        unordered_map<std::string, std::function<void()>> questActionMap;

        if(!data["questEffect"].is_null())
        {
            //we have a quest that effects the options!
            //print out those options

            for(size_t i = 0; i < data["questEffect"].size(); i++)
            {
                string idToCheck = data["questEffect"][i]["questID"];

                string targetQuest = data["questEffect"][i]["target"];

                if(!data["questEffect"][i]["appendedActions"].is_null())
                {
                    for(size_t l = 0; l < data["questEffect"][i]["appendedActions"].size(); l++)
                    {
                        locationsExtras.push_back(data["questEffect"][i]["appendedActions"][l]["appendName"]);
                    }
                }

                if(gc->player.hasQuest(idToCheck))
                {
                    ifstream questFile(targetQuest);

                    if (!questFile.is_open()) 
                    {
                        cout << "Failed to open " << targetQuest << "\n";
                    }

                    json qData;
                    questFile >> qData;

                    for(size_t j = 0; j < locationsExtras.size(); j++)
                    {
                        questActions = qData[locationsExtras.at(j)];
                    
                        for(size_t k = 0; k < questActions.size(); k++)
                        {
                            append++;
                            string actionPrint = questActions[k]["actionDescription"];
                            cout <<  "[" << append << "] " << actionPrint;
                        }
                    }   

                    

                    questFile.close();
                }
            }
        }

        

        cout << "\n-> ";

        cin >> keyboardInput;
        string actionToCheck;

        if(static_cast<size_t>(keyboardInput-1) < actions.size())
        {
            actionToCheck = actions[keyboardInput-1]["target"];
        }

        else
        {
            actionToCheck = questActions[(keyboardInput-1) - actions.size()]["target"];
        }

        if(actionToCheck.substr(actionToCheck.length() - 5, 5) == ".json")
        {
            file.close();
            //loadAreaFromJson(actionToCheck);
            returnVal = actionToCheck;

        }

        else
        {
            file.close();
            if(actionMap.find(actionToCheck) != actionMap.end())
            {  
                actionMap.find(actionToCheck)->second();
                returnVal = jsonToLoad;
            }

            //check the new appended library
            else
            {
                

                if(questActionMap.find(actionToCheck) != questActionMap.end())
                {
                    //load the new one
                }
            }
        }

        //cout << returnVal;
    }

    
    gc->colors.clearScreen();
    
    return returnVal;
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

    while(static_cast<size_t>(keyboardInput <= 0) || static_cast<size_t>(keyboardInput) > inventory.size())
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

    loadAreaFromJson(currentJson);

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
    cin.ignore();
    

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
        int weaponCost = (crafting.at(0).price) + (crafting.at(1).price) + (crafting.at(2).price);
        cout << "It will cost " << weaponCost << " Novas!\n"
             << "you have " << gc->player.getNovas() << " Novas,\n"
             << "Craft or BACK?";
        cout << "\n-> ";
        getline(cin, keyboardString);

        if(keyboardString == "Craft")
        {
            if(gc->player.getNovas() >= weaponCost)
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
                    gc->player.addToInventory(crafting.at(i), -1);
                }

            
                Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
                Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());
                Saving::saveInventory("playerData/playerInventorySave.json", gc->player);
            }

            else
            {
                cout << "\nYou don't have enough novas!\n";
            }
        }

        else if(keyboardString != "BACK")
        {
            cout << gc->colors.RED << "\n! INVALID INPUT !\n" << gc->colors.DEFAULT;
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
    //add a way for rumors to appear from the json file not hard coded
    cout << "I heard of this wicked fast rabbit in the woods. Go find em and kill it!\n";

    Quest lightningRabbit("Quests/lightningRabbit.json");
    gc->player.addQuest(lightningRabbit);
    
    gc->colors.pauseTerminal(2);
};

void Actions::viewGuildCard()
{
    gc->colors.clearScreen();
    gc->player.printGuildCard();
    cout << "\n";
    gc->colors.pauseTerminal(2);
};

void Actions::viewInventory()
{
    gc->colors.clearScreen();
    gc->player.printInventory(1000);
    cout << "\n";
    gc->colors.pauseTerminal(2);
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
    gc->colors.pauseTerminal(2);
};

void Actions::viewQuests()
{
    gc->colors.clearScreen();
    gc->player.printQuests();
    cout << "\n";

    gc->colors.pauseTerminal(3);
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
        "This well is a curse on the town. People come and throw coins expecting riches.\nI know better!\n",

            // New well / village rumors
        "Some say the blacksmith has a secret stash of cursed weapons.\nPersonally, I avoid him.\n",
        "The wind sometimes carries whispers from the plains.\nI swear I heard my own name once.\n",
        "Old Marlen at the guild keeps muttering about monsters in the cornfields.\nShe scares the children, I tell you.\n",
        "People say the innkeeper's stew can make you dream of things you shouldn't.\nI haven't tried it yet.\n", // boss rush!

        // Temple rumors
        "They say an ancient temple lies hidden in the forest.\nNo one who went looking has ever come back the same.\n",
        
        // Red herrings / humorous gossip
        "I heard that a traveling bard sold a song that can make goats levitate.\nI haven't seen it work.\n",
        "The windmill at the edge of town sometimes turns backwards.\nThey say it's bad luck, but it seems fine to me.\n",
        "Some say the town well sometimes laughs at fools.\nOthers think it's just the echo.\n",
        "I swear the crows are plotting something.\nEvery time I walk by, they stare.\n",
        "Look! These Rabbits!\nThey are plotting our deaths!\nI tell you, one shot fire!"
    };

    //better message logic so i can skew things
    string message = wellTalks.at(rand() % wellTalks.size());

    if(message == wellTalks.at(3))
    {
        QuestObjective q(false);

        Quest wellQuest("Quests/tcnWell.json");
        wellQuest.addObjective(q);
        gc->player.addQuest(wellQuest);
    }

    //logic to add as a quest

    cout << message;

    gc->colors.pauseTerminal(3);
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
    if(gc->player.getHealth() <= 0)
    {
        cout << " You are too weak to fight!\n";
    }
    
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

void Actions::keyAsk()
{
    if(gc->player.hasQuest("bottomOfTheWell"))
    {
        Quest* q = gc->player.getQuest("bottomOfTheWell");
        
        if(q == nullptr)
        {
            cout << "nullptr\n";
        }

        else
        {
            if(!q->getObjective().hasItem)
            {
                cout << "heres the key!\n";
                q->getObjective().hasItem = true;
                q->setMessageIndex(2);
            }
        }
    }

    gc->colors.pauseTerminal(1);
}

void Actions::drunkenTalk()
{
    gc->colors.clearScreen();

    if(gc->player.hasQuest("forestTempleQuest"))
    {
        vector<string> drunkardTalks =
        {
            "I tell ya, the chickens in Elderwell… they plot against the moon, I swear!\n",
            "LLRLRR!\n I tell you my goat keeps telling me its in the woods.\n",
            "You can't trust the bread here… it whispers secrets if you listen too hard.\n",
            "The mayor is a frog in disguise. Don't tell anyone I said that.\n",
            "I once saw a goat recite poetry. It was better than the bard last week.\n",
            "The stars, they move sideways sometimes… don't ask me why, I'm just a simple man.\n",
            "I tried talking to the well… it answered back. Or maybe that was my reflection.\n",
            "Rivers sometimes walk, you know. I saw one cross the plains once, slowly… like it had places to go.\n",
            "The wind steals things from your pockets, but only when you're not looking… mostly spoons.\n",
            "I keep telling folks… the trees can hear you, but only when you sing off-key.\n",
            "There's a rock outside that winks at people. It's rude but honest.\n",
            "If you hear laughter in the forest, it's probably just the shadows having tea. Or maybe not.\n",
            "Left, left, right, left, right, right… that's how you find the forest temple. Trust me, I think.\n",
        };

        int place = rand() % drunkardTalks.size();
        cout << drunkardTalks.at(place);

        if(place == 12)
        {
            gc->player.getQuest("forestTempleQuest")->setMessageIndex(gc->player.getQuest("forestTempleQuest")->getQuestIndex() + 1);
        }
       
    }

    else
    {
        vector<string> drunkardTalks =
        {
            "I tell ya, the chickens in Elderwell... they plot against the moon, I swear!\n",
            "You can't trust the bread here... it whispers secrets if you listen too hard.\n",
            "The mayor is a frog in disguise. Don't tell anyone I said that.\n",
            "I once saw a goat recite poetry. It was better than the bard last week.\n",
            "The stars, they move sideways sometimes... don't ask me why, I'm just a simple man.\n",
            "I tried talking to the well... it answered back. Or maybe that was my reflection.\n",
            "Rivers sometimes walk, you know. I saw one cross the plains once, slowly... like it had places to go.\n",
            "The wind steals things from your pockets, but only when you're not looking... mostly spoons.\n",
            "I keep telling folks... the trees can hear you, but only when you sing off-key.\n",
            "There's a rock outside that winks at people. It's rude but honest.\n",
            "If you hear laughter in the forest, it's probably just the shadows having tea. Or maybe not.\n"
        };

        int place = rand() % drunkardTalks.size();
        cout << drunkardTalks.at(place);
    }

    gc->colors.pauseTerminal(3);
};

void Actions::barKeepTalk()
{
    gc->colors.clearScreen();
    
    if(!gc->player.hasQuest("forestTempleQuest"))
    {   
        cout << "People in this town never stop talking about the temple in the forest.\nI've never seen an adventurer come back from it."
             << "\nAnd people that just check it out say they see things out there.";
        Quest templeQuest("Quests/fTempleQuest.json");
        gc->player.addQuest(templeQuest);
    }

    else
    {
        vector<string> innkeeperTalks = 
        {
            "The forest isn't just trees, you know. Some of those old oaks remember things that no one else does.\n",
            "Back in my youth, the river ran red one morning. They blamed the fish, but I think it was something older.\n",
            "The guild used to be a small group of hunters, not adventurers. Times change, but old habits linger.\n",
            "Some nights you can hear chanting from the forest temple, even if the villagers say it's just the wind.\n",
            "The town well used to be part of an old boundary marker for lands long forgotten.\n",
            "Before the forest was called Eldergrove, folks said it was cursed, and no one dared enter.\n",
            "I heard a story about a wandering merchant who traded gold for memories. Never saw him again.\n",
            "There's a cave under the hill outside town. They say it's home to a very grumpy old wizard.\n", //the first place to craft spells
            "The temple in the woods isn't marked on any map. Some believe it chooses who may find it.\n",
            "The wind carries voices from the mountains to the north, but only if you stand very still.\n",
            "Our crops are usually safe, but every few years, something strange comes from the forest at night.\n",
            "People say the stars over these plains align differently than anywhere else in the kingdom.\n",
            "At night, when Thorin lights the forge, he makes it burn hotter than his brother.\n Must be something about skill.\n",
            "Yes, I do have a special soup, but I wont sell it to you!\n"
        };

        int place = rand() % innkeeperTalks.size();
        cout << innkeeperTalks.at(place);
    }

    gc->colors.pauseTerminal(3);
};

void Actions::buyRoom()
{
    cout << "The room heals you completely!\n";
    gc->player.increaseHealth(gc->player.getMaxHealth());
    gc->colors.pauseTerminal(1);
};

void Actions::wellSwim()
{
    if(gc->player.getHealth() <= 0)
    {
        gc->colors.clearScreen();
        cout << "Your health is to low to dive any furthur";
    }

    else
    {
        gc->colors.clearScreen();

        swimDepth++;

        if(swimDepth < 10)
        {
            gc->player.takeDamage(swimDepth);
            cout << "You lost " << swimDepth << " health! ";
            cout << gc->colors.CYAN << gc->player.getHealth() << "/" << gc->player.getMaxHealth() << gc->colors.DEFAULT;
        }

        else
        {
            gc->player.getQuest("bottomOfTheWell")->setMessageIndex(gc->player.getQuest("bottomOfTheWell")->getQuestIndex() + 1);
            loadAreaFromJson("Locations/Town1Well/bottomOfWell.json");

            //if the quest messages hasnt be increased then increase it
        }
    }
};

void Actions::wellKey()
{
    Quest* q = gc->player.getQuest("bottomOfTheWell");
    
    if(q->getObjective().hasItem)
    {
        cout << "You unlocked the door!\n";
    }

    else
    {
        cout << "You press on the doors lock, but without a key it wont open!\n";
    }
};

void Actions::seduceWellDoor()
{
    gc->colors.clearScreen();

    vector<string> options =
    {
        "Your attempts to seduce the door are unsucessful.\n",
        "The door turns a bright red but doesn't budge\n",
        "You hear snickering behind the door as you try to seduce it\n",
        "The door stands there, just being a door\n",
        "You start to hear a sad tiny violin playing from seemingly no where\n",
        "What are you doing? You beging to ask yourself\n",
        "You think you see the handle blush, but it might\'ve been the lighting.\n",
        "The door remains unimpressed by you.\n",
        "You wink at the door. The door does not wink back.\n",
        "You swear the hinges sighed, but it might\'ve been your pride escaping.\n",
        "You try to whisper but bubbles just escape your mouth.\n",
        "You caress the woodgrain lovingly. Splinters remind you of your mistakes.\n",
        "The door looks at you, or it would if it had eyes, which it doesn\'t.\n",
        "You feel your dignity leave you.\n",
        "The door remains steadfast, an unfeeling guardian of boundaries and rejection.\n",
        "You\'re pretty sure this isn\'t how locks work.\n",
        "A bubles of awkwardness fills the air.\n",
        "Somewhere, your ancestors sigh in disappointment.\n",
        "You hear the narrator mutter, \'Really? The door?\'\n",
        "The door says nothing, but somehow, you can tell it\'s not interested.\n"
    };


    double seduceChance = (rand() % 100) / 100.0;

    if(seduceChance != 0.01)
    {
        int place = rand() % options.size();
        cout << options.at(place);

        if(place == 11)
        {
            cout << "You take " << gc->colors.RED << "1 Damage!\n" << gc->colors.DEFAULT;

            gc->player.takeDamage(1);
        }
    }

    else
    {
        cout << "YOU SEDUCED A DOOR?!\n";
    }

    gc->colors.pauseTerminal(3);
};

void Actions::addHealthPots()
{
    gc->player.increaseHealthPotionCount(potionsToAdd);
}

void Actions::addManaPots()
{
    gc->player.increaseManaPotionCount(potionsToAdd);
}

void Actions::saveQuit()
{
    cout << "Saving Player!\n";
    Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
    gc->colors.pauseTerminal(1);

    cout << "Saving Attacks!\n";
    Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());
    gc->colors.pauseTerminal(1);

    cout << "Saving Inventory!\n";
    Saving::saveInventory("playerData/playerInventorySave.json", gc->player);
    gc->colors.pauseTerminal(1);

    gc->inGame = false;

    exit(0);
};

void Actions::efEncounter()
{
    /*
        | encounter table |
            Fight Enemies            (2-5 enemies)
            lumberjack               (Sell, Buy) Better price sell wood
            Not abandoned tent       (friendly or unfriendly)
            Adventuring party        (in distress or not)
            Ghost encounters         (at night only)
            Broken Horse cart        (Help, Pillage)                       30%     25%     Done
            Captured Fairy           (Release, leave)                      20%     20%     Done
            Abandonded Tent          (Pillage, Leave)                      15%     10%     Done
            Injured Wolf             (Kill, Help)                          10%     10%     Done
            Rose Guarden             (Pick flowers, leave)                 10%     10%     Done
            Sword Pedestal           (Pull, leave)                         10%     10%     Inprogress
            Temple                   (Enter, Leave) special logic           5%     15%     Inprogress
    */

    gc->colors.clearScreen();
    
    int encounterChance = rand() % 101;

    if(gc->player.hasQuest("forestTempleQuest"))
    {
        if(encounterChance > 75)
        {
            loadAreaFromJson("Locations/ElderwellForest/horseCart.json");
        }

        else if(encounterChance <= 75 && encounterChance > 55)
        {
            loadAreaFromJson("Locations/ElderwellForest/capturedFairy.json");
        }

        else if(encounterChance <= 55 && encounterChance > 45)
        {
            loadAreaFromJson("Locations/ElderwellForest/abandonedTent.json");
        }

        else if(encounterChance <= 45 && encounterChance > 35)
        {
            loadAreaFromJson("Locations/ElderwellForest/InjuredWolf.json");
        }

        else if(encounterChance <= 35 && encounterChance > 25)
        {
            loadAreaFromJson("Locations/ElderwellForest/roseGuarden.json");
        }

        else if(encounterChance <= 25 && encounterChance > 15)
        {
            loadAreaFromJson("Locations/ElderwellForest/SwordPullEncounter/swordPedastal.json");

        }

        else
        {       
            loadAreaFromJson("Locations/ElderwellForest/forestTemplePath.json");
        }
    }
 
    else //fix encounter chances
    {
        if(encounterChance > 70)
        {
            loadAreaFromJson("Locations/ElderwellForest/horseCart.json");
        }

        else if(encounterChance <= 70 && encounterChance > 50)
        {
            loadAreaFromJson("Locations/ElderwellForest/capturedFairy.json");
        }

        else if(encounterChance <= 50 && encounterChance > 35)
        {
            loadAreaFromJson("Locations/ElderwellForest/abandonedTent.json");
        }

        else if(encounterChance <= 35 && encounterChance > 25)
        {
            loadAreaFromJson("Locations/ElderwellForest/InjuredWolf.json");
        }

        else if(encounterChance <= 25 && encounterChance > 15)
        {
            loadAreaFromJson("Locations/ElderwellForest/roseGuarden.json");
        }

        else if(encounterChance <= 15 && encounterChance > 5)
        {
            loadAreaFromJson("Locations/ElderwellForest/SwordPullEncounter/swordPedastal.json");
        }

        else
        {       
            loadAreaFromJson("Locations/ElderwellForest/forestTemplePath.json");
        }
    }


};

void Actions::efForage()
{
    gc->colors.clearScreen();
    
    int forageChance = rand() % 101;
    /*
        | Forage Table |
        Leaf            35%
        Grass           35%
        Wood            10%
        Stone Wood      10%
        Stone            5%
        Iron Wood        2%
        Wolf Fang        2%
        Dragon Scale     1%
    */

    int randomAmt = 0;
    CraftingMaterials matPrint;

    if(forageChance > 65)
    {
        randomAmt = (rand() % 20) + 1;
        matPrint = gc->mats.find("grass")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }

    else if(forageChance <= 65 && forageChance > 30)
    {   
        randomAmt = (rand() % 20) + 1;
        matPrint = matPrint = gc->mats.find("leaf")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }

    else if(forageChance <= 30 && forageChance > 20)
    {
        randomAmt = (rand() % 5) + 1;
        matPrint = gc->mats.find("wood")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }


    else if(forageChance <= 20 && forageChance > 10)
    {
        randomAmt = (rand() % 3) + 1;
        matPrint = gc->mats.find("stoneWood")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }


    else if(forageChance <= 10 && forageChance > 5)
    {
        randomAmt = (rand() % 3) + 1;
        matPrint = gc->mats.find("stone")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }


    else if(forageChance <= 5 && forageChance > 3)
    {
        randomAmt = (rand() % 2) + 1;
        matPrint = gc->mats.find("ironWood")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }


    else if(forageChance <= 3 && forageChance > 1)
    {
        randomAmt = (rand() % 2) + 1;
        matPrint = gc->mats.find("wolfFang")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }

    else
    {
        randomAmt = 1;
        matPrint = gc->mats.find("fDragonScale")->second;
        gc->player.addToInventory(matPrint, randomAmt);
    }

    cout << "You were able to forage " << randomAmt << " " << matPrint.name << "\n";
    gc->colors.pauseTerminal(3);
};

void Actions::efHorseCartPil()
{
    //ElderwellHorseCarriage

    int enemyAmt = rand() % 2 + 1;
    bool ran = false;

    if(gc->player.getHealth() <= 0)
    {
        cout << " You are too weak to fight!\n";
        gc->colors.pauseTerminal(3);
    }

    else
    {
        
        while(enemyAmt > 0 && gc->player.getHealth() >= 0)
        {
            vector<vector<Enemy>> horseCart = EnemyFactory::loadRegionEnemy("ElderwellHorseCarriage");

            Combat forestCombat(gc, horseCart, "ElderwellHorseCarriage");

            forestCombat.determineEnemy();
            //forestCombat.printGui();

            forestCombat.newCombatTest();

            if(forestCombat.getCurEnemy().getHp() > 0)
            {
                ran = true;
            }

            Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
            Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());
            Saving::saveInventory("playerData/playerInventorySave.json", gc->player);

            enemyAmt--;
            gc->colors.pauseTerminal(2);
        }
    }

    if(enemyAmt <= 0 && !ran)
    {
        int woodAmt = rand() % 3 + 1;
        int novaAmt = rand() % 15;
        int healthPotAmt = rand() % 3;

        cout << "You obtained " << woodAmt << " wood";

        if(novaAmt > 0)
        {
            cout << ", " << novaAmt << " Novas";
        }

        if(healthPotAmt > 0)
        {
            cout << ", and " << healthPotAmt << " Health Potions!\n";
        }

        gc->player.addToInventory(gc->mats.find("wood")->second, woodAmt);
        gc->player.increaseNovas(novaAmt);
        gc->player.increaseHealthPotionCount(healthPotAmt);

        Saving::saveInventory("playerData/playerInventorySave.json", gc->player);

        gc->colors.pauseTerminal(3);
    }
};

void Actions::efHorseCartHelp()
{
    cout << "We need " << gc->colors.YELLOW << "5 Wood and 10 Leaves " 
         << gc->colors.DEFAULT << " to fix the cart!\n";

    if(gc->player.getInventoryAmount(gc->mats.find("wood")->second) >= 5
       && gc->player.getInventoryAmount(gc->mats.find("leaf")->second) >= 10)
    {
        gc->player.addToInventory(gc->mats.find("wood")->second, -5);
        gc->player.addToInventory(gc->mats.find("leaf")->second, -10);

        int novaAmt = rand() % 20 + 10;
        int expAmt = rand() % 20 + 5;

        cout << "You got " << gc->colors.YELLOW << novaAmt << " Novas and "
             << expAmt << " Experience.\n" << gc->colors.DEFAULT;

        gc->player.increaseNovas(novaAmt);
        gc->player.increaseExperience(expAmt);

        if(gc->player.getExperience() >= gc->player.getXpToNextLevel())
        {
            gc->player.levelUp();
        }
    }

    else
    {
        cout << "You don't have what you need to fix it.\n";
    }

    gc->colors.pauseTerminal(3);
};

void Actions::fairyRelease()
{
    int enemyAmt = rand() % 3 + 1;

    if(gc->player.getHealth() <= 0)
    {
        cout << " You are too weak to fight!\n";
        gc->colors.pauseTerminal(3);
    }

    else
    {
        bool ran = false;

        while(enemyAmt > 0 && gc->player.getHealth() >= 0)
        {
            vector<vector<Enemy>> fairyCaptors = EnemyFactory::loadRegionEnemy("ElderwellFairyCapture");
            
            Combat fairyCombat(gc, fairyCaptors, "ElderwellFairyCapture");
            
            fairyCombat.determineEnemy();

            //forestCombat.printGui();

            fairyCombat.newCombatTest();

            if(fairyCombat.getCurEnemy().getHp() > 0)
            {
                ran = true;
            }

            Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
            Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());
            Saving::saveInventory("playerData/playerInventorySave.json", gc->player);

            enemyAmt--;
            gc->colors.pauseTerminal(2);
        }

        if(enemyAmt <= 0 && !ran)
        {
            gc->colors.clearScreen();
            cout << "Thank you for saving me! Take some pixie dust as a reward!\n";

            int pDustAmt = rand() % 3 + 1;
            cout << "You obtained " << gc->colors.YELLOW << pDustAmt << " Pixie Dust.\n" << gc->colors.DEFAULT;

            gc->player.addToInventory(gc->mats.find("pixieDust")->second, pDustAmt);
            Saving::saveInventory("playerData/playerInventorySave.json", gc->player);
            gc->colors.pauseTerminal(3);
        }
    }
};

void Actions::makeCamp()
{
    int healthHealed = gc->player.getMaxHealth() / 3;
    cout << "You turn the abandond campsite into a new one with a fire\n";
    cout << "You healed for " << gc->colors.CYAN << healthHealed  << " Health\n" << gc->colors.DEFAULT;

    gc->player.increaseHealth(healthHealed);

    gc->colors.pauseTerminal(2);
};

void Actions::pillageCamp()
{
    int enemyChance = rand() % 100;

    if(enemyChance >= 80)
    {
        if(gc->player.getHealth() <= 0)
        {
            cout << " You are too weak to fight!\n";
        }

        else
        {
            vector<vector<Enemy>> forest = EnemyFactory::loadRegionEnemy("Forest");

            Combat forestCombat(gc, forest, "Forest");

            forestCombat.determineEnemy();
            //forestCombat.printGui();

            cout << "A " << forestCombat.getCurEnemy().getType() << " jumped out from the tent!\n";
            gc->colors.pauseTerminal(2);

            forestCombat.newCombatTest();

            Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
            Saving::saveAttacks("playerData/PlayerAction/customAttacks.json", gc->player.getCustomAtks());
            Saving::saveInventory("playerData/playerInventorySave.json", gc->player);
        }
    }

    else
    {
        int novaAmt = rand() % 15;
        int healthPotAmt = rand() % 2;
        int manPotAmt = rand() % 2;

        if(novaAmt <= 0 && healthPotAmt <= 0 && manPotAmt <= 0)
        {
            cout << "Everything except for the tent was wiped clean from the camp!\n";
        }

        else
        {
            cout << "You found ";
        }

        if(novaAmt > 0)
        {
            cout << novaAmt << " Novas " << gc->colors.DEFAULT;
        }

        if(healthPotAmt > 0)
        {
            cout << gc->colors.CYAN << healthPotAmt << " Health Potions " << gc->colors.DEFAULT;
        }

        if(manPotAmt > 0)
        {
            cout << gc->colors.MAGENTA << manPotAmt << " Mana Potinos " << gc->colors.DEFAULT;
        }

        gc->player.increaseNovas(novaAmt);
        gc->player.increaseHealthPotionCount(healthPotAmt);
        gc->player.increaseManaPotionCount(manPotAmt);

        Saving::saveToFile(gc->player, "playerData/playerStatsSave.json", "playerData/playerCombatBook.json");
        gc->colors.pauseTerminal(2);
    }

};

void Actions::healWolf()
{
    if(gc->player.getHealthPotionCount() > 0)
    {
        cout << "The wolf stands back up and spits out a fang before running into the woods.\n";
        gc->player.increaseHealthPotionCount(-1);
        gc->player.addToInventory(gc->mats.find("wolfFang")->second, 1);
        Saving::saveInventory("playerData/playerInventorySave.json", gc->player);

        gc->colors.pauseTerminal(2);
    }
};

void Actions::killWolf()
{
    cout << "Aftering killing the wolf you obtained its fang, hide, and tail.\n";
    gc->player.addToInventory(gc->mats.find("wolfFang")->second, 1);
    gc->player.addToInventory(gc->mats.find("wolfHide")->second, 1);
    gc->player.addToInventory(gc->mats.find("wolfTail")->second, 1);
    Saving::saveInventory("playerData/playerInventorySave.json", gc->player);

    gc->colors.pauseTerminal(3);
};

void Actions::pickRose()
{
    if(gc->player.getHealth() > 3)
    {
        cout << "You took " << gc->colors.RED << "2 Damage " << gc->colors.DEFAULT << "as you picked the rose.\n";

        gc->player.addToInventory(gc->mats.find("rose")->second, 1);
        gc->player.takeDamage(2);
    }

    else
    {
        cout << "You feel like the thorns might kill you.\n";
    }

    gc->colors.pauseTerminal(3);
};
