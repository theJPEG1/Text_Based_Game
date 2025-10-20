#include "Player.H"
#include "Enemy.H"
#include "Combat.H"
#include "PrettyColors.H"
#include "WeightedGen.H"
#include "attacksEffects.H"

#include <vector>
    using std::vector;
#include <random>
#include <string>
    using std::string;
#include <iostream>
    using std::cin;
#include <map>
    using std::map;

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
Combat::Combat(Player& thisPlayer, vector<vector<Enemy>> currentRegionEnemy, string currentRegion)
    : player(thisPlayer)
{
    regionToUse = currentRegionEnemy;
    region = currentRegion;

    enemyNameMap["Slime"] = slimeNames;
    enemyNameMap["Squirel"] = squirelNames;
    enemyNameMap["Rabbit"] = bunnyNames;
    enemyNameMap["Wolf"] = wolfNames;
    enemyNameMap["Boar"] = boarNames;
    enemyNameMap["Bear"] = bearNames;
    enemyNameMap["Sprig"] = sprigNames;
    enemyNameMap["Stump Golem"] = stumpNames;
    enemyNameMap["Fairy"] = noNames;

    enemyNameMap["Dragon"] = dragonNames;
        // index 0-4 is forest dragons
};

/**
 * @brief Randomly selects and sets the current enemy for combat.
 */
void Combat::determineEnemy()
{
    WeightedGen gen;
    
    curEnemy = gen.generateEnemy(player.getLevel(), regionToUse);

    curEnemy.setName(enemyNameMap.find(curEnemy.getType())->second.at(rand() % enemyNameMap.find(curEnemy.getType())->second.size()));
    
};

void Combat::newCombatTest()
{
    bool isFighting = true;
    bool ranAway = false;

    WeightedGen gen;
    PrettyColors color;
    int keyboardInput = 0;

// == Start Combat Logic ==
    while(isFighting)
    {
        cout << "You are fighting " << curEnemy.getName() << curEnemy.getType() << "\n\n"
             << "You have " << color.CYAN << player.getHealth() << "/" << player.getMaxHealth() << " Health\t" << color.DEFAULT
             << "You have " << color.MAGENTA << player.getMana() << "/" << player.getMaxMana() << " Mana\n" << color.DEFAULT;
        cout << "You can do " << color.RED << player.getStrength() << " Damage.\t" << color.DEFAULT << "\n\n";
             
    //== Display Enemy Info Based on Mind Stat ==
        if(player.getMind() >= 20 && player.getMind() < 30)
        {
            cout << curEnemy.getName() << " has " << color.CYAN << curEnemy.getHp() << "/" << curEnemy.getMaxHp() 
            << " Health" << color.DEFAULT;
        }

        else if(player.getMind() >= 30 && player.getMind() < 40) 
        {
            cout << curEnemy.getName() << " has " << color.CYAN << curEnemy.getHp() << "/" << curEnemy.getMaxHp() 
            << " Health.\t" << color.DEFAULT;
            cout << curEnemy.getName() << " Can do " << color.RED << "0-" << curEnemy.getStrength() << " Damage."
                 << color.DEFAULT;
        }

        else if(player.getMind() >= 40)
        {
            cout << curEnemy.getName() << " has " << color.CYAN << curEnemy.getHp() << "/" << curEnemy.getMaxHp() 
            << " Health\t" << color.DEFAULT;
            cout << curEnemy.getName() << " Can do " << color.RED << "0-" << curEnemy.getStrength() << " Damage. \n"
                 << color.DEFAULT;
            cout << curEnemy.getName() << " Has a " << color.GREEN << "0-" << curEnemy.getDexterity() << " Dodge."
                 << color.DEFAULT;
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

                    cout << "[" << i + 1 << "] " << player.getAllCombat().at(i).name << "\t";
                }
            }

            else 
            {
                choice = "spells";
                for(size_t i = 4; i < player.getAllCombat().size(); i++)
                {
                    if(i % 2 == 0)
                    {
                        cout << "\n";
                    }

                    cout << "[" << (i - 4) + 1 << "] " << player.getAllCombat().at(i).name << "\t";
                }
            }
            

            cout << "\n-> ";
            cin >> keyboardInput;

            cout <<"\n";

            if(keyboardInput == 1 || keyboardInput == 2 || keyboardInput == 3 || keyboardInput == 4)
            {
                if(choice == "attack")
                {
                    handleAttack(gen, color, keyboardInput - 1);

                    if(player.getAllCombat().at(keyboardInput -1).thisEffects.at(0).dexModi > 0)
                    {
                        handleEnemyAttack(gen, color, player.getAllCombat().at(keyboardInput -1).thisEffects.at(0).dexModi);
                    }

                    else
                    {
                        handleEnemyAttack(gen, color, 0);
                    }
                }

                else
                {
                    if(player.getMana() >= player.getAllCombat().at(keyboardInput + 3).manacost)
                    {
                        handleAttack(gen, color, keyboardInput + 3);

                        if(player.getAllCombat().at(keyboardInput + 3).thisEffects.at(0).dexModi > 0)
                        {
                            handleEnemyAttack(gen, color, player.getAllCombat().at(keyboardInput -1).thisEffects.at(0).dexModi);
                        }

                        else
                        {
                            handleEnemyAttack(gen, color, 0);
                        }

                        player.setMana(-player.getAllCombat().at(keyboardInput + 3).manacost);
                    }

                    else
                    {
                        cout << color.RED << "Not enough mana to cast " << player.getAllCombat().at(keyboardInput + 3).name  << "!\n" << color.DEFAULT;
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
            int potionHealAmount = player.getMaxHealth() / 3;
            int potionManaAmount = player.getMana() / 10;

            cout << color.CYAN << "\n[1] Health Potions: " << player.getHealthPotionCount() << " (+" << potionHealAmount << ")\t"
                 << color.MAGENTA << "[2] Mana Potions: " << player.getManaPotionCount() << " (+" << potionManaAmount << ")\n"
                 << color.DEFAULT;

            cout << "-> ";
            cin >> keyboardInput;

            if(keyboardInput == 1)
            {
                handlePotion(color, "HEALTH");
            }

            else if(keyboardInput == 2)
            {
                handlePotion(color, "MANA");
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
            cout << "\n You ran away from " << curEnemy.getName() << curEnemy.getType() << "\n";
        }

        else
        {
            cout << color.RED << "\nINVALID INPUT!\n" << color.DEFAULT;
        }

    // == End Combat Logic ==
    
        if(curEnemy.getHp() <= 0 || player.getHealth() <= 0)
        {
            isFighting = false;
        }

        player.setMana((player.getMind() / 10) + 5);

        keyboardInput = 0;
        color.pauseTerminal(3);
        color.clearScreen();
    }

    if(curEnemy.getHp() <= 0 && player.getHealth() > 0 && !ranAway)
    {
        cout << color.GREEN << "You defeated " << curEnemy.getName() << curEnemy.getType() << "!\n" << color.DEFAULT;
        int xpGained = rand() % (curEnemy.getMaxExp() - curEnemy.getMinExp() + 1) + curEnemy.getMinExp();

        cout << color.YELLOW << "You gained " << xpGained << " XP!\n";
        player.setExperience(xpGained);

        cout << player.getExperience() << "/" << player.getXpToNextLevel() << " XP to next level.\n" << color.DEFAULT;
    }

    if(player.getExperience() >= player.getXpToNextLevel())
    {
        player.levelUp();
    }
};



/**
 * @brief Handles attack and spell actions during combat.
 * @param gen Reference to WeightedGen for damage/dodge calculations.
 * @param color Reference to PrettyColors for output formatting.
 * @param actionIndex Index to use for an attack.
 */
void Combat::handleAttack(WeightedGen& gen, PrettyColors& color, int actionIndex)
{
    int damageToApply = 0;
    bool dodged;

    if(curEnemy.getBound()) //auto crit
    {
        dodged = false;

        if(actionIndex < 4) //phsical attack 
        {
            damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;
            

            player.getAllCombat().at(actionIndex).thisEffects.at(0).critChance = 101;

            for(size_t i = 0; i < player.getAllCombat().at(actionIndex).thisEffects.size(); i++)
            {
                player.getAllCombat().at(actionIndex).thisEffects.at(i).applyEffect(curEnemy);

                if(player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance > 0)
                {
                    if(rand() % 100 + 1 < player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance)
                    {
                        cout << "\nCRIT\n";
                        damageToApply *= 2;
                    }
                }


                if(player.getAllCombat().at(actionIndex).thisEffects.at(i).selfDamage)
                {
                    player.setHealth(-damageToApply / 2);
                }

                if(player.getAllCombat().at(actionIndex).thisEffects.at(i).healingAmt > 0)
                {
                    player.setHealth(damageToApply);
                }
            }

            damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;
            damageToApply *= player.getStrength() / 5;

            if(curEnemy.getPhysRes() != 0)
            {
                damageToApply *= curEnemy.getPhysRes();
            }
        }

        else //magical attacks
        {
            damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;

            player.getAllCombat().at(actionIndex).thisEffects.at(0).critChance = 101;

            for(size_t i = 0; i < player.getAllCombat().at(actionIndex).thisEffects.size(); i++)
            {
                player.getAllCombat().at(actionIndex).thisEffects.at(i).applyEffect(curEnemy);

                if(player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance > 0)
                {
                    if(rand() % 100 + 1 < player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance)
                    {
                        cout << "\nCRIT\n";
                        damageToApply *= 2;
                    }
                }

                if(player.getAllCombat().at(actionIndex).thisEffects.at(i).selfDamage)
                {
                    player.setHealth(-damageToApply / 2);
                }

                if(player.getAllCombat().at(actionIndex).thisEffects.at(i).healingAmt > 0)
                {
                    player.setHealth(damageToApply);
                }
            }

            damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;
            damageToApply *= player.getMind() / 5;

            if(curEnemy.getMagiRes() != 0)
            {
                damageToApply *= curEnemy.getMagiRes();
            }
        }
    }

    else
    {
        if(actionIndex < 4) //phsical attack 
        {
            if(player.getAllCombat().at(actionIndex).thisEffects.at(0).dexModi > 0)
            {
                dodged = gen.dodgeChance(player.getDexterity(), curEnemy.getDexterity(), player.getAllCombat().at(actionIndex).thisEffects.at(0).dexModi > 0, "PLAYER");
            }

            else
            {
                dodged = gen.dodgeChance(player.getDexterity(), curEnemy.getDexterity(), "PLAYER");
            }
            
            
            if(!dodged)//hit enemy
            {
                damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;

                for(size_t i = 0; i < player.getAllCombat().at(actionIndex).thisEffects.size(); i++)
                {
                    player.getAllCombat().at(actionIndex).thisEffects.at(i).applyEffect(curEnemy);

                    if(player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance > 0)
                    {
                        if(rand() % 100 + 1 < player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance)
                        {
                            cout << "\nCRIT\n";
                            damageToApply *= 2;
                        }
                    }

                     if(player.getAllCombat().at(actionIndex).thisEffects.at(i).selfDamage)
                    {
                        player.setHealth(-damageToApply / 2);
                    }

                    if(player.getAllCombat().at(actionIndex).thisEffects.at(i).healingAmt > 0)
                    {
                        player.setHealth(damageToApply);
                    }
                }

                damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;
                damageToApply *= player.getStrength() / 5;
            }
        }

        else //magical attacks
        {
            dodged = gen.dodgeChance(player.getDexterity(), curEnemy.getDexterity(), "PLAYER");

            if(!dodged)
            {
                damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;

                for(size_t i = 0; i < player.getAllCombat().at(actionIndex).thisEffects.size(); i++)
                {
                    player.getAllCombat().at(actionIndex).thisEffects.at(i).applyEffect(curEnemy);

                    if(player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance > 0)
                    {
                        if(rand() % 100 + 1 < player.getAllCombat().at(actionIndex).thisEffects.at(i).critChance)
                        {
                            cout << "\nCRIT\n";
                            damageToApply *= 2;
                        }
                    }

                    if(player.getAllCombat().at(actionIndex).thisEffects.at(i).selfDamage)
                    {
                        player.setHealth(-damageToApply / 2);
                    }

                    if(player.getAllCombat().at(actionIndex).thisEffects.at(i).healingAmt > 0)
                    {
                        player.setHealth(damageToApply);
                    }

                    

                    damageToApply = player.getAllCombat().at(actionIndex).thisEffects.at(0).baseDmg;
                    damageToApply *= player.getMind() / 5;
                }
            }
        }
    }

    if(!dodged)
    {
        cout <<"\nYou hit " << curEnemy.getName() << curEnemy.getType() << " for " << color.RED << damageToApply << " Damage\n" << color.DEFAULT;
        player.dealDamage(curEnemy, damageToApply);
    }

    else
    {
        cout << curEnemy.getName() << curEnemy.getType() << " dodged your attack!\n";
    }
    
};




/**
 * @brief Handles potion actions (health, mana, strength, dexterity) during combat.
 * @param color Reference to PrettyColors for output formatting.
 * @param type Type of potion: "HEALTH", "MANA", "STRENGTH", or "DEXTERITY".
 * @param buff Reference to the buff value to apply (for strength/dexterity potions).
 * @param potionDur Reference to the potion duration counter.
 */
void Combat::handlePotion(PrettyColors& color, string type)
{
    if(type == "HEALTH")
    {
        if(player.getHealthPotionCount() > 0)
        {
            int potionHealAmount = player.getMaxHealth() / 3;

            player.setHealth(potionHealAmount);

            cout << "\nYou drank a health potion and healed for " << potionHealAmount << " Health.\n" << color.DEFAULT;
            
            player.setHealthPotionCount(player.getHealthPotionCount() - 1);
        }

        else
        {
            cout << color.RED << "\nYou don't have any health potions!\n" << color.DEFAULT;
        }
    }

    else if(type == "MANA")
    {
        if(player.getManaPotionCount() > 0)
        {
            int potionManaAmount = player.getMana() / 5;

            player.setMana(potionManaAmount);
            cout << "\nYou drank a mana potion and restored " << potionManaAmount << " Mana.\n" << color.DEFAULT;
            
            player.setManaPotionCount(player.getManaPotionCount() - 1);
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

void Combat::handleEnemyAttack(WeightedGen& gen, PrettyColors& color, int dexBuff)
{
    if(curEnemy.getBound())
    {
        cout << curEnemy.getName() << " is bound and cannot attack this turn!\n";
        curEnemy.setBind(false);
    }

    else
    {
        bool dodged = gen.dodgeChance(player.getDexterity(), curEnemy.getDexterity(), dexBuff , "ENEMY");

        if(!dodged)
        {
            int enemyDamageRoll = gen.determineDamage(curEnemy.getStrength());

            if(curEnemy.getCounter())
            {
                cout << color.GREEN << "You countered the attack!\n" << color.DEFAULT;
                cout << "You hit " << curEnemy.getName() << curEnemy.getType() << " for " << color.RED << enemyDamageRoll << " Damage\n" << color.DEFAULT;
                player.dealDamage(curEnemy, enemyDamageRoll);
            }

            else
            {
                cout <<"You were hit for " << color.RED << enemyDamageRoll << " Damage\n" << color.DEFAULT;
                curEnemy.dealDamage(player, enemyDamageRoll);
            }
        }

        else
        {
            cout << "You dodged the attack.\n";
        }
    }  
}