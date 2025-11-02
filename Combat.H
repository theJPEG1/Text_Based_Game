#ifndef COMBAT_H
#define COMBAT_H

#include "Enemy.H"
#include "WeightedGen.H"
#include "GameState.H"

#include <vector>
    using std::vector;
#include <random>
#include <string>
    using std::string;
#include <iostream>
    using std::cin;
#include <map>
    using std::map;

class Combat
{
    public:
        Combat(GameState& gameState, vector<vector<Enemy>> currentRegionEnemy, string currentRegion);
        void determineEnemy();
        void printGui();

        void newCombatTest();

    private:
        

    private:
        GameState gs;
        vector<vector<Enemy>> regionToUse;
        string region;
        Enemy curEnemy;
        WeightedGen gen;
        PrettyColors color;

        //action field
        void handleAttack(int& lowestDamage, int strengthBuff, int dexBuff, string type);
        void handleAttack(Attacks multSpell);
        void handlePotion(string type);
        void handleEnemyAttack(int dexBuff = 0);

        void handleAttack(int actionIndex);
};

#endif
