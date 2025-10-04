#ifndef COMBAT_H
#define COMBAT_H

#include "Player.H"
#include "Enemy.H"
#include "PrettyColors.H"
#include "WeightedGen.H"

#include <vector>
    using std::vector;
#include <string>
    using std::string;
#include <map>
    using std::map;

class Combat
{
    public:
        Combat(Player& thisPlayer, vector<Enemy> currentRegionEnemy, string currentRegion);
        void determineEnemy();
        void printGui();

        void newCombatTest();

    private:
        

    private:
        Player& player;
        vector<Enemy> regionToUse;
        string region;
        Enemy curEnemy;
        map <string, vector<string>> enemyNameMap;

        //names of arrays find a awy to load this or many another object or smothing
        vector<string> slimeNames {"Glorp", "Goop", "Wiggles", "Gummy", "Oozeburt", "Glippy", "Plop", "Yogurt", "Jonathan"};
        vector<string> squirelNames {"Sandy Cheecks", "Nutter", "Peanut", "Snickers", "Big Cheecks", "Ratatoskr", "Twitch", "Craig"};
        vector<string> bunnyNames {"Snowball", "Thumper", "Peter", "Cotton Tail", "Fluffer", "Flopsy", "Buster", "Joe"};
        vector<string> wolfNames {"Hati", "Sköll", "Scar", "Dire", "White Fang", "Night Eyes", "Fenrir", "Carl"};
        vector<string> boarNames {"Tusk", "Snouts", "Broken Tusk", "Princess", "Pork Chop", "Suey", "Gullinbursti", "Bert"};
        vector<string> bearNames {"Claw", "Grizzler", "Ursa", "Pooh", "Maw", "Oreius", "Bear", "Harold"};
        vector<string> sprigNames {"Lila", "Sunflor", "Lily", "Daffolin", "Dander", "Sprif", "Spore", "Sharron"};
        vector<string> stumpNames {"Wood", "Iron Wood", "Walnut Wood", "Stone Wood", "Tree", "Decay Wood", "Short", "Steven"};
        vector<string> noNames {"?", "??", "???", "????", "?????"};
        vector<string> dragonNames {"Feykro", "Laas", "Sil", "Strunmah", "Graag"};

        //action field
        void handleAttack(WeightedGen& gen, PrettyColors& color, int& lowestDamage, int strengthBuff, int dexBuff, string type);
        void handlePotion(PrettyColors& color, string type);
        void handleEnemyAttack(WeightedGen& gen, PrettyColors& color, int dexBuff = 0);

        void handleAttack(WeightedGen& gen, PrettyColors& color, int actionIndex);
};

#endif
