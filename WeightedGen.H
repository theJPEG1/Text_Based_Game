#ifndef WEIGHTEDGEN_H
#define WEIGHTEDGEN_H

#include "Enemy.H"
#include <string>
    using std::string;
#include <map>
    using std::map;
#include <vector>
    using std::vector;

class WeightedGen
{
    
    public:
        WeightedGen();
        Enemy generateEnemy(int playerLevel, vector<vector<Enemy>> enemiesToUse);

        bool dodgeChance(int playerDex, int enemyDex, string turn);
        bool dodgeChance(int playerDex, int enemyDex, double modifier, string turn);
        int determineDamage(int strengthStat);
        int determineDamage(int strengthStat, double modifier);

    private:
        vector<int> level1 {50, 10, 5, 1, 0};
        vector<int> level2 {75, 15, 5, 2, 0};
        vector<int> level3 {95, 80, 20, 5, 0};
        vector<int> level4 {98, 95, 85, 25, 0};
        vector<int> level5 {98, 95, 90, 50, 0};
        map <int, vector<int>> enemyGen;

        /*
            Rules for the vectors above:
            The values inside are going to be the percent chance out of 100
            I will uses vector level3 as an example
            
                Level 1 Enemy : 100 - 95 = 5% chance
                Level 2 Enemy : 95  - 80 = 15% chance
                Level 3 Enemy : 80  - 20 = 60% chance
                Level 4 Enemy : 20  - 5  = 15% chance
                Level 5 Enemy : 5   - 0  = 5% chance
        */
};

#endif