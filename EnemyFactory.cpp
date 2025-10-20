#include "EnemyFactory.H"
#include "Enemy.H"
#include "include/json.hpp"
    using json = nlohmann::json;


#include <string>
    using std::string;
#include <fstream>
    using std::ifstream;
#include <vector>
    using std::vector;




/**
 * @brief       Constructs an enemy object.
 *
 * @param        thisRegion   The region the enemy belongs in.
 * @param        thisName     The name of the enemy.
 * @param        enemyType    The type of the enemy.
 * @param        health       The health of the enemy.
 * @param        strength     The strength of the enemy.
 * @param        dexterity    The dexterity of the enemy.
 * @param        minExp       The minimum experience the enemy gives when defeated.
 * @param        maxExp       The maximum experience the enemy gives when defeated.
 *
**/
Enemy EnemyFactory::createEnemy(string thisRegion, string thisName, string enemyType, double phyRes, double magRes, bool isBoss, int health, int strength, int dexterity, int minExp, int maxExp)
{
    Enemy newEnemy(thisRegion, thisName, enemyType, phyRes, magRes, isBoss, health, strength, dexterity, minExp, maxExp);

    return newEnemy;
};


vector<vector<Enemy>> EnemyFactory::loadRegionEnemy(string region)
{
    vector<vector<Enemy>> regionToReturn;

    vector<Enemy> en1;
    vector<Enemy> en2;
    vector<Enemy> en3;
    vector<Enemy> en4;
    vector<Enemy> en5;

    ifstream fileIn("EnemyData/Enemies.json");

    json enemies;
    fileIn >> enemies;

    for(size_t i = 0; i < enemies[region].size(); i++)
    {
        Enemy e
        ( 
            enemies[region][i]["Region"],
            enemies[region][i]["Name"],
            enemies[region][i]["EnemyType"],
            enemies[region][i]["PhysicalRes"],
            enemies[region][i]["MagicalRes"],
            enemies[region][i]["Boss"],
            enemies[region][i]["Health"],
            enemies[region][i]["Strength"],
            enemies[region][i]["Dexterity"],
            enemies[region][i]["MinExp"],
            enemies[region][i]["MaxExp"],
            enemies[region][i]["Level"]
        );

        switch(e.getLevel())
        {
            case 1:
            {
                en1.push_back(e);
                break;
            }

            case 2:
            {
                en2.push_back(e);
                break;
            }

            case 3:
            {
                en3.push_back(e);
                break;
            }

            case 4:
            {
                en4.push_back(e);
                break;
            }

            case 5:
            {
                en5.push_back(e);
                break;
            }
        }
    }

    regionToReturn.push_back(en1);
    regionToReturn.push_back(en2);
    regionToReturn.push_back(en3);
    regionToReturn.push_back(en4);
    regionToReturn.push_back(en5);

    return regionToReturn;
};