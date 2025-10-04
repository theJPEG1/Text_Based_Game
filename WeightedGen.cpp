#include "WeightedGen.H"
#include "Enemy.H"

#include <string>
    using std::string;
#include <map>
    using std::map;
#include <vector>
    using std::vector;

#include <iostream>

WeightedGen::WeightedGen()
{
    enemyGen[1] = level1;
    enemyGen[2] = level2;
    enemyGen[3] = level3;
    enemyGen[4] = level4;
    enemyGen[5] = level5;
};

/**
 * @brief       Finds out what enemy you're going to fight.
 *
 * @param        playerLevel   Level of the player as the key.
 * @param        enemiesToUse  A vector of enemies
 * 
 * @return      An enemy from the vector
 *
**/
Enemy WeightedGen::generateEnemy(int playerLevel, vector<Enemy> enemiesToUse)// low to high
{
    Enemy determinedEnemy;
    int enemyIndex = 0;

    double rarityChance = rand() % 100 + 1;

    //low to high are the chances
    if(playerLevel > 5 && enemiesToUse.at(0).getRegion() == "Forest")
    {   
        if(rarityChance > enemyGen[5].at(0))
        {
            //0-2
            enemyIndex = rand() % 2;
            determinedEnemy = enemiesToUse.at(enemyIndex);
        }

        else if(rarityChance < enemyGen[5].at(0) && rarityChance >= enemyGen[5].at(1))
        {
            //3-4
            enemyIndex = (rand() % 2) + 2;
            determinedEnemy = enemiesToUse.at(enemyIndex);
            
        }

        else if(rarityChance < enemyGen[5].at(1) && rarityChance >= enemyGen[5].at(2))
        {
            //5-6
            enemyIndex = (rand() % 2) + 4;
            determinedEnemy = enemiesToUse.at(enemyIndex);
            
        }

        else if(rarityChance < enemyGen[5].at(2) && rarityChance >= enemyGen[5].at(3))
        {
            //7
            determinedEnemy = enemiesToUse.at(7);
        }

        else if(rarityChance < enemyGen[5].at(3) && rarityChance >= enemyGen[5].at(4))
        {
            //8-10
            enemyIndex = (rand() % 2) + 8;
            determinedEnemy = enemiesToUse.at(enemyIndex);
        }
    }

    else 
    {
        if(rarityChance >= enemyGen.find(playerLevel)->second.at(0))
        {
            //0-2
            enemyIndex = rand() % 2;
            determinedEnemy = enemiesToUse.at(enemyIndex);
        }

        else if(rarityChance < enemyGen.find(playerLevel)->second.at(0) && rarityChance >= enemyGen.find(playerLevel)->second.at(1))
        {
            //3-4
            enemyIndex = (rand() % 2) + 2;
            determinedEnemy = enemiesToUse.at(enemyIndex);
            
        }

        else if(rarityChance < enemyGen.find(playerLevel)->second.at(1) && rarityChance >= enemyGen.find(playerLevel)->second.at(2))
        {
            //5-6
            enemyIndex = (rand() % 2) + 4;
            determinedEnemy = enemiesToUse.at(enemyIndex);
            
        }

        else if(rarityChance < enemyGen.find(playerLevel)->second.at(2) && rarityChance >= enemyGen.find(playerLevel)->second.at(3))
        {
            //7
            determinedEnemy = enemiesToUse.at(7);
        }

        else if(rarityChance < enemyGen.find(playerLevel)->second.at(3))
        {
            //8-10
            enemyIndex = (rand() % 2) + 8;
            determinedEnemy = enemiesToUse.at(enemyIndex);
        }
    }

    return determinedEnemy;
};

/**
 * @brief       Compares playerDex and enemyDex to determine a dodge.
 *
 * @param        playerDex   Player's dexterity.
 * @param        enemyDex    Enemie's dexterity
 * @param        turn        Whos turn it is
 * 
 * @return      True if dodge, else false
 *
**/
bool WeightedGen::dodgeChance(int playerDex, int enemyDex, string turn) //true if player > enemy
{
    bool didDodge;
    
    int playerDexRoll = rand() % playerDex;
    int enemyDexRoll = rand() % enemyDex;

    if(turn == "PLAYER")
    {
        if(playerDexRoll > enemyDexRoll) //hit enemy
        {
            didDodge = false;
        }

        else //enemy dodged
        {
            didDodge = true;
        }
    }

    else //enemy
    {
        if(playerDexRoll > enemyDexRoll) //dodged enemy
        {
            didDodge = true;
        }

        else //hit by enemy
        {
            didDodge = false;
        }
    }

    return didDodge;
};

/**
 * @brief       Compares playerDex and enemyDex to determine a dodge.
 *
 * @param        playerDex   Player's dexterity.
 * @param        enemyDex    Enemie's dexterity
 * @param        turn        Whos turn it is
 * @param        modifier    - or + modifier (-1, 1)
 * 
 * @return      True if dodge, else false
 *
**/
bool WeightedGen::dodgeChance(int playerDex, int enemyDex, double modifier, string turn) //true if player > enemy
{

    bool didDodge;
    int playerDexRoll = (rand() % playerDex) + modifier;
    int enemyDexRoll = rand() % enemyDex;

    if(turn == "PLAYER")
    {
        if(playerDexRoll > enemyDexRoll) //hit enemy
        {
            didDodge = false;
        }

        else //enemy dodged
        {
            didDodge = true;
        }
    }

    else //enemy
    {
        if(playerDexRoll > enemyDexRoll) //dodged enemy
        {
            didDodge = true;
        }

        else //hit by enemy
        {
            didDodge = false;
        }
    }

    return didDodge;
};

/**
 * @brief       Uses an object strength stat to determine damage.
 *
 * @param        strengthStat   Strength stat of the object
 * 
 * @return      A number between 1 and strengthStat
 *
**/
int WeightedGen::determineDamage(int strengthStat)
{
    return (rand() % strengthStat) + 1;
};

/**
 * @brief       Uses an object strength stat to determine damage.
 *
 * @param        strengthStat   Strength stat of the object
 * @param        modifier       - or + modifier (-1, 1)
 * 
 * @return      A number between 1 and strengthStat with a minimum of (strengthStat / 3)
 *
**/
int WeightedGen::determineDamage(int strengthStat, double modifier)
{
    modifier *= static_cast<int>(strengthStat * 1.5) - strengthStat;
    int lowestDamage = strengthStat / 3;

    int damage = ((rand() % strengthStat) + modifier) + 1;

    if(damage < lowestDamage)
    {
        damage = lowestDamage;
    }

    return damage;
};