#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.H"
#include <vector>
    using std::vector;

class EnemyFactory
{
    public:
        static Enemy createEnemy(string thisRegion, string thisName, string enemyType, double phyRes, double magRes, bool isBoss, int health, int strength, int dexterity, int minExp, int maxExp);
        static vector<vector<Enemy>> loadRegionEnemy(string regionToLoad /*File to read from*/);
};


#endif