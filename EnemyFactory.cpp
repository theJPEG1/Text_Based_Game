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


vector<Enemy> EnemyFactory::loadRegionEnemy(string region)
{
    vector<Enemy> regionToReturn;
    ifstream fileIn("EnemyData/Enemies.json");

    json enemies;
    fileIn >> enemies;

    for(size_t i = 0; i < enemies["Enemies"].size(); i++)
    {
        if(enemies["Enemies"][i]["Region"] == region)
        {
            Enemy e
            ( 
                enemies["Enemies"][i]["Region"],
                enemies["Enemies"][i]["Name"],
                enemies["Enemies"][i]["EnemyType"],
                enemies["Enemies"][i]["PhysicalRes"],
                enemies["Enemies"][i]["MagicalRes"],
                enemies["Enemies"][i]["Boss"],
                enemies["Enemies"][i]["Health"],
                enemies["Enemies"][i]["Strength"],
                enemies["Enemies"][i]["Dexterity"],
                enemies["Enemies"][i]["MinExp"],
                enemies["Enemies"][i]["MaxExp"]
            );

            regionToReturn.push_back(e);
        }
    }

    return regionToReturn;
};