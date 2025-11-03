#include "Combat.H"

//time for funky math and a weird explaniation
/*  
    To find out if you hit your target
        First you roll your dexterity values like a dice
            pDex = rand() % player.getDexterity(); 
        Then we roll the enemys dexterity
            eDex = rand() % curEnemy.getDexterity();

        Player to Enemy
            if(pD >= eD) { Hit }
            else { Miss }

        Enemy to Player
            if(eD >= pD) { Hit }
            else { Miss }

    To determine Damage
        Player to Enemy
            pDam = rand() % player.getStrength();
        Enemy to Player
            eDam = rand() % enemy.getStrength();

    Types of Attack
        Heavy  [+Strength][-Dexterity]
        Light  [+Strength][-Dexterity]
        Normal   [Strength][Dexterity]
        
*/



/**
 * @brief Constructs a Combat object for a battle in a specific region.
 * @param thisPlayer Reference to the player participating in combat.
 * @param currentRegionEnemy Vector of enemies in the current region.
 * @param currentRegion Name of the current region.
 */
Combat::Combat(GameState& gameState, vector<vector<Enemy>> currentRegionEnemy, string currentRegion)
{
    gs = gameState;
    regionToUse = currentRegionEnemy;
    region = currentRegion;
};

/**
 * @brief Randomly selects and sets the current enemy for combat.
 */
void Combat::determineEnemy()
{   
    curEnemy = gen.generateEnemy(gs.player.getLevel(), regionToUse);
};

void Combat::newCombatTest()
{
    bool isFighting = true;
    bool ranAway = false;
    int keyboardInput = 0;

// == Start Combat Logic ==
    while(isFighting)
    {
        cout << "You are fighting " << curEnemy.getName() << curEnemy.getType() << "\n\n"
             << "You have " << color.CYAN << gs.player.getHealth() << "/" << gs.player.getMaxHealth() << " Health\t" << color.DEFAULT
             << "You have " << color.MAGENTA << gs.player.getMana() << "/" << gs.player.getMaxMana() << " Mana\n" << color.DEFAULT;

        if(gs.player.getStrength() >= 10)
        {
            cout << "You have " << color.RED << static_cast<double>(gs.player.getStrength() / 10.0) << " Physical Multiplier\n" << color.DEFAULT;
        }

        if(gs.player.getMind() >= 10)
        {
            cout << "You have " << color.MAGENTA << static_cast<double>(gs.player.getMind() / 10.0) << " Magical Multiplier\n" << color.DEFAULT;
        }
             
        cout << "\n";
    //== Display Enemy Info Based on Mind Stat ==
        if(gs.player.getMind() >= 20 && gs.player.getMind() < 30)
        {
            cout << curEnemy.getName() << " has " << color.CYAN << curEnemy.getHp() << "/" << curEnemy.getMaxHp() 
                 << " Health" << color.DEFAULT;
        }

        else if(gs.player.getMind() >= 30 && gs.player.getMind() < 40) 
        {
            cout << curEnemy.getName() << " has " << color.CYAN << curEnemy.getHp() << "/" << curEnemy.getMaxHp()
                 << " Health.\t" << color.DEFAULT;

            cout << curEnemy.getName() << " has " << color.RED << curEnemy.getPhysRes() << " Physical Resistance" << color.DEFAULT;
        }

        else if(gs.player.getMind() >= 40)
        {
            cout << curEnemy.getName() << " has " << color.CYAN << curEnemy.getHp() << "/" << curEnemy.getMaxHp()
                 << " Health.\t" << color.DEFAULT;

            cout << curEnemy.getName() << " has " << color.RED << curEnemy.getPhysRes() << " Physical Resistance\n" << color.DEFAULT;

            cout << curEnemy.getName() << " has " << color.MAGENTA << curEnemy.getMagiRes() << " Magical Resistance" << color.DEFAULT;
        }
    //== End Enemy Info ==

        cout << "\n\nWhat do you want to do\n"
             << "[1] Attack \t[2] Potion\n[3] Magic\t[4] Run\n-> ";

        cin >> keyboardInput;

    // == Begin Attack / Spell Action ==
        if(keyboardInput == 1 || keyboardInput == 3) 
        {
            string choice = "";
            if(keyboardInput == 1)
            {
                choice = "attack";
                for(size_t i = 0; i < 4; i++)
                {
                    if(i % 2 == 0)
                    {
                        cout << "\n";
                    }

                    cout << "[" << i + 1 << "] " << gs.player.getAllCombat().at(i).name << " (";

                    for(size_t k = 0; k < gs.player.getAllCombat().at(i).thisEffects.size(); k++)
                    {
                        if(k == 0)
                        {
                            cout << gs.player.getAllCombat().at(i).thisEffects.at(k).id;
                        }

                        else
                        {
                            cout << " " << gs.player.getAllCombat().at(i).thisEffects.at(k).id;
                        }
                        
                    }

                    cout << ")";

                    if(gs.player.getAllCombat().at(i).name.length() < 30 && gs.player.getAllCombat().at(i).name.length() > 17)
                    {
                        cout << "\t";
                    }

                    if(gs.player.getAllCombat().at(i).name.length() < 16)
                    {
                        cout << "\t";
                    }

                    if(gs.player.getAllCombat().at(i).name.length() < 8)
                    {
                        cout << "\t";
                    }
                }
            }

            else 
            {
                choice = "spells";
                for(size_t i = 4; i < gs.player.getAllCombat().size(); i++)
                {
                    if(i % 2 == 0)
                    {
                        cout << "\n";
                    }

                    cout << "[" << (i -4) + 1 << "] " << gs.player.getAllCombat().at(i).name << " (";

                    for(size_t k = 0; k < gs.player.getAllCombat().at(i).thisEffects.size(); k++)
                    {
                        if(k == 0)
                        {
                            cout << gs.player.getAllCombat().at(i).thisEffects.at(k).id;
                        }

                        else
                        {
                            cout << " " << gs.player.getAllCombat().at(i).thisEffects.at(k).id;
                        }
                    }

                    cout << ")";

                    if(gs.player.getAllCombat().at(i).name.length() < 30 && gs.player.getAllCombat().at(i).name.length() > 17)
                    {
                        cout << "\t";
                    }

                    if(gs.player.getAllCombat().at(i).name.length() < 16)
                    {
                        cout << "\t";
                    }

                    if(gs.player.getAllCombat().at(i).name.length() < 8)
                    {
                        cout << "\t";
                    }
                    
                }
            }
            

            cout << "\n-> ";
            cin >> keyboardInput;

            cout <<"\n";

            if(keyboardInput == 1 || keyboardInput == 2 || keyboardInput == 3 || keyboardInput == 4)
            {
                if(choice == "attack")
                {
                    handleAttack(keyboardInput - 1);

                    if(curEnemy.getHp() <= 0 || gs.player.getHealth() <= 0)
                    {
                        isFighting = false;
                    }

                    else if(gs.player.getAllCombat().at(keyboardInput -1).thisEffects.at(0).dexModi > 0)
                    {
                        handleEnemyAttack(gs.player.getAllCombat().at(keyboardInput -1).thisEffects.at(0).dexModi);
                    }

                    else
                    {
                        handleEnemyAttack(0);
                    }
                }

                else
                {
                    if(gs.player.getMana() >= gs.player.getAllCombat().at(keyboardInput + 3).manacost)
                    {
                        handleAttack(keyboardInput + 3);
                        
                        if(curEnemy.getHp() <= 0 || gs.player.getHealth() <= 0)
                        {
                            isFighting = false;
                        }

                        if(gs.player.getAllCombat().at(keyboardInput + 3).thisEffects.at(0).dexModi > 0)
                        {
                            handleEnemyAttack(gs.player.getAllCombat().at(keyboardInput -1).thisEffects.at(0).dexModi);
                        }

                        else
                        {
                            handleEnemyAttack(0);
                        }

                        gs.player.increaseMana(-gs.player.getAllCombat().at(keyboardInput + 3).manacost);
                    }

                    else
                    {
                        cout << color.RED << "Not enough mana to cast " << gs.player.getAllCombat().at(keyboardInput + 3).name  << "!\n" << color.DEFAULT;
                    }
                }
                
            }

            else
            {
                cout << color.RED << "\nINVALID INPUT!\n" << color.DEFAULT;
            }
        }
    // == End Attack / Spell Action ==

    // == Begin Potion Action
        else if(keyboardInput == 2)
        {
            int potionHealAmount = gs.player.getMaxHealth() / 3;
            int potionManaAmount = gs.player.getMana() / 10;

            cout << color.CYAN << "\n[1] Health Potions: " << gs.player.getHealthPotionCount() << " (+" << potionHealAmount << ")\t"
                 << color.MAGENTA << "[2] Mana Potions: " << gs.player.getManaPotionCount() << " (+" << potionManaAmount << ")\n"
                 << color.DEFAULT;

            cout << "-> ";
            cin >> keyboardInput;

            if(keyboardInput == 1)
            {
                handlePotion("HEALTH");
            }

            else if(keyboardInput == 2)
            {
                handlePotion("MANA");
            }

            else
            {
                cout << color.RED << "\nINVALID INPUT!\n" << color.DEFAULT;
            }
        }
    // == End Potion Action

    // == Begin Run Action ==
        else if(keyboardInput == 4)
        {
            ranAway = true;
            curEnemy.takeDamage(curEnemy.getMaxHp());
            cout << "\n You ran away from " << curEnemy.getName() << curEnemy.getType() << "\n";
        }

        else
        {
            cout << color.RED << "\nINVALID INPUT!\n" << color.DEFAULT;
        }

    // == End Combat Logic ==
    
        if(curEnemy.getHp() <= 0 || gs.player.getHealth() <= 0)
        {
            isFighting = false;
        }

        gs.player.increaseMana((gs.player.getMind() / 10) + 5);

        keyboardInput = 0;
        color.pauseTerminal(3);
        color.clearScreen();
    }

    if(curEnemy.getHp() <= 0 && gs.player.getHealth() > 0 && !ranAway)
    {
        cout << color.GREEN << "You defeated " << curEnemy.getName() << curEnemy.getType() << "!\n" << color.DEFAULT;
        int xpGained = rand() % (curEnemy.getMaxExp() - curEnemy.getMinExp() + 1) + curEnemy.getMinExp();

        cout << color.YELLOW << "You gained " << xpGained << " XP!\n";
        gs.player.increaseExperience(xpGained);

        cout << gs.player.getExperience() << "/" << gs.player.getXpToNextLevel() << " XP to next level.\n" << color.DEFAULT;

        int dropChance = rand() % 100;

        if(dropChance - gs.player.getLuck() < curEnemy.getDropChance())
        {
            gs.player.addToInventory(curEnemy.getDrop(), 1);
            cout << "It dropped " << curEnemy.getDrop().name;

            int novaAmount = (rand() % curEnemy.getMaxNovas()) + curEnemy.getMinNovas();
            gs.player.increaseNovas(novaAmount);
            cout << " Add " << novaAmount << " novas!";
        }

        cout << "\n";
    }

    if(gs.player.getExperience() >= gs.player.getXpToNextLevel())
    {
        gs.player.levelUp();
    }
};



/**
 * @brief Handles attack and spell actions during combat.
 * @param gen Reference to WeightedGen for damage/dodge calculations.
 * @param color Reference to PrettyColors for output formatting.
 * @param actionIndex Index to use for an attack.
 */
void Combat::handleAttack(int actionIndex)
{

    bool dodged;

    if(curEnemy.getBound()) //auto crit
    {
        int storeCrit = gs.player.getAllCombat().at(actionIndex).thisEffects.at(0).critChance;
        gs.player.getAllCombat().at(actionIndex).thisEffects.at(0).critChance = 101;

        for(size_t i = 0; i < gs.player.getAllCombat().at(actionIndex).thisEffects.size(); i++)
        {
            gs.player.getAllCombat().at(actionIndex).thisEffects.at(i).handleEffects(curEnemy, gs.player, "PLAYER");
        
            if(gs.player.getAllCombat().at(actionIndex).thisEffects.at(i).multCast > 0)
            {
                for(int i = 0; i < gs.player.getAllCombat().at(actionIndex).thisEffects.at(i).multCast; i++)
                {
                    handleAttack(gs.player.getRandAttack());
                }
            }
        }

        gs.player.getAllCombat().at(actionIndex).thisEffects.at(0).critChance = storeCrit;
    }

    else
    {
        if(gs.player.getAllCombat().at(actionIndex).thisEffects.at(0).dexModi > 0)
        {
            dodged = gen.dodgeChance(gs.player.getDexterity(), curEnemy.getDexterity(), gs.player.getAllCombat().at(actionIndex).thisEffects.at(0).dexModi > 0, "PLAYER");
        }

        else
        {
            dodged = gen.dodgeChance(gs.player.getDexterity(), curEnemy.getDexterity(), "PLAYER");
        }

        if(dodged)
        {
            for(size_t i = 0; i < gs.player.getAllCombat().at(actionIndex).thisEffects.size(); i++)
            {
                Effects& effectRef = gs.player.getAllCombat().at(actionIndex).thisEffects.at(i);
                effectRef.handleEffects(curEnemy, gs.player, "PLAYER");
        
                if(gs.player.getAllCombat().at(actionIndex).thisEffects.at(i).multCast > 0)
                {
                    for(int i = 0; i < gs.player.getAllCombat().at(actionIndex).thisEffects.at(i).multCast; i++)
                    {
                        handleAttack(gs.player.getRandAttack());
                    }
                }
            }
        }

        else
        {
            cout << curEnemy.getName() << curEnemy.getType() << " dodged your attack!\n";
        }
    }

    
    
};

void Combat::handleAttack(Attacks multSpell)
{
    if(multSpell.type == "spell")
    {
        cout << "\nYou casted " << multSpell.name << "!\n";

        for(size_t i = 0; i < multSpell.thisEffects.size(); i++)
        {
            multSpell.thisEffects.at(i).handleEffects(curEnemy, gs.player, "PLAYER");

            if(multSpell.thisEffects.at(i).multCast > 0)
            {
                for(int k = 0; k < multSpell.thisEffects.at(i).multCast; k++)
                {
                    handleAttack(gs.player.getRandAttack());
                }
            }
        }
    }
}


/**
 * @brief Handles potion actions (health, mana, strength, dexterity) during combat.
 * @param color Reference to PrettyColors for output formatting.
 * @param type Type of potion: "HEALTH", "MANA", "STRENGTH", or "DEXTERITY".
 * @param buff Reference to the buff value to apply (for strength/dexterity potions).
 * @param potionDur Reference to the potion duration counter.
 */
void Combat::handlePotion(string type)
{
    if(type == "HEALTH")
    {
        if(gs.player.getHealthPotionCount() > 0)
        {
            int potionHealAmount = gs.player.getMaxHealth() / 3;

            gs.player.increaseHealth(potionHealAmount);

            cout << "\nYou drank a health potion and healed for " << potionHealAmount << " Health.\n" << color.DEFAULT;
            
            gs.player.increaseHealthPotionCount(-1);
        }

        else
        {
            cout << color.RED << "\nYou don't have any health potions!\n" << color.DEFAULT;
        }
    }

    else if(type == "MANA")
    {
        if(gs.player.getManaPotionCount() > 0)
        {
            int potionManaAmount = gs.player.getMana() / 5;

            gs.player.increaseMana(potionManaAmount);
            cout << "\nYou drank a mana potion and restored " << potionManaAmount << " Mana.\n" << color.DEFAULT;
            
            gs.player.increaseManaPotionCount(-1);
        }

        else
        {
            cout << color.RED << "\nYou don't have any mana potions!\n" << color.DEFAULT;
        }
    }

    else
    {
        cout << color.RED << "\nINVALID INPUT!\n" << color.DEFAULT;
    }
};

void Combat::handleEnemyAttack(int dexBuff)
{
    if(curEnemy.getBound())
    {
        cout << curEnemy.getName() << " cannot attack this turn!\n";
        curEnemy.setBind(false);
    }

    else
    {
        bool dodged = gen.dodgeChance(gs.player.getDexterity(), curEnemy.getDexterity(), dexBuff , "ENEMY");

        if(!dodged)
        {
            if(curEnemy.getCounter())
            {
            }

            else
            {
                for(size_t i = 0; i < curEnemy.getAtk().thisEffects.size(); i++)
                {
                    Effects& effectRef = curEnemy.getAtk().thisEffects.at(i);
                    effectRef.rebuildActionMap();
                    
                    if(effectRef.actionMap.find("-") == effectRef.actionMap.end())
                    {
                        cout << "ID NOT EXIST\n";
                    }

                    else
                    {
                        effectRef.handleEffects(curEnemy, gs.player, "ENEMY");
                    }    
                }
            }
        }

        else
        {
            cout << "You dodged the attack.\n";
        }
    }  
}