#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"
#include "attacksEffects.h"
#include "include/json.hpp"
    using json = nlohmann::json;


#include <string>
    using std::string;
#include <fstream>
    using std::ifstream;
#include <vector>
    using std::vector;
#include <vector>
    using std::vector;

class EnemyFactory
{
    public:
        static Enemy createEnemy(string thisRegion, string thisName, string enemyType, 
                                 double phyRes, double magRes, bool isBoss, 
                                 int health, int strength, int dexterity, 
                                 int minExp, int maxExp, int dropChn,
                                 int minNov, int maxNov);
        static vector<vector<Enemy>> loadRegionEnemy(string regionToLoad /*File to read from*/);

    private:
         
};


#endif
