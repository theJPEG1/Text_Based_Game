#include "EnemyFactory.H"

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
Enemy EnemyFactory::createEnemy(string thisRegion, string thisName, string enemyType, 
                                 double phyRes, double magRes, bool isBoss, 
                                 int health, int strength, int dexterity, 
                                 int minExp, int maxExp, int dropChn,
                                 int minNov, int maxNov)
{
    Enemy newEnemy(thisRegion, thisName, enemyType, 
                   phyRes, magRes, isBoss, 
                   health, strength, dexterity, 
                   minExp, maxExp, 1, dropChn, minNov, maxNov);

    return newEnemy;
};


vector<vector<Enemy>> EnemyFactory::loadRegionEnemy(string region)
{
    CraftingMaterials cLoad;
    vector<CraftingMaterials> cMats = cLoad.loadCraftingMaterialss("GameData/craftingMaterials.json");

    Attacks atk;
    vector<Attacks> loadAtk = atk.loadAttacks("playerData/PlayerAction/attacks.json");

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
        string matType = enemies[region][i]["materialID"];
        string attackId1 = enemies[region][i]["attackID1"];
        string attackId2 = enemies[region][i]["attackID2"];
        string attackId3 = enemies[region][i]["attackID2"];

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
            enemies[region][i]["Level"],
            enemies[region][i]["dropChance"],
            enemies[region][i]["novasMin"],
            enemies[region][i]["novasMax"]
        );


        for(size_t k = 0; k < cMats.size(); k++)
        {
            if(matType == cMats.at(k).id)
            {
                e.setMaterial(cMats.at(k));
            }
        }

        for(size_t j = 0; j < loadAtk.size(); j++)
        {
            if(attackId1 == loadAtk.at(j).id || attackId2 == loadAtk.at(j).id || attackId3 == loadAtk.at(j).id)
            {
                e.addAtks(loadAtk.at(j));
            }
        }
        

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