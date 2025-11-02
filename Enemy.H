#ifndef ENEMY_H
#define ENEMY_H

#include "attacksEffects.H"

#include <string>
    using std::string;

class Player;

class Enemy
{
    
    public:
        Enemy(string thisRegion="none", string thisName="?", string enemyType="?", 
              double phyRes=0, double magRes=0, bool isBoss=false, int health=1, 
              int strength=1, int dexterity=1, int minExp=1, int maxExp=5, 
              int level=1, int dropChn = 1, int minNov = 1, int maxNov = 1);
        
        void takeDamage(int damage);
        void dealDamage(Player& target, int damage);

    //getters
        string getRegion();
        string getName();
        string getType();
        int getHp();
        int getMaxHp();
        int getStrength();
        int getDexterity();
        int getLevel() {return level;};

        double getPhysRes() {return physiRes;};
        double getMagiRes() {return magiRes;};

        int getDropChance() {return dropChance;};
        CraftingMaterials getDrop() {return material;};
        int getMaxNovas() {return maxNovas;};
        int getMinNovas() {return minNovas;};

        bool getBound() {return bound;};
        bool getCounter() {return counter;};
        int getDotDuration() {return dotDuration;};

        int getMinExp();
        int getMaxExp();

        void debuffs();

        void displaySelf();

        Attacks getAtk();

    //setters
        void setName(string newName);
        void setMaterial(CraftingMaterials c) {material = c;};

        void setBind(bool isBound) {bound = isBound;};
        void setCounter(bool isCounter) {counter = isCounter;};
        void setDOT(bool isDot) {DOT = isDot;};
        void setWeakened(bool isWeakened) {weakened = isWeakened;};
        void setDotDuration(int duration) {dotDuration = duration;};
        void setAttack(vector<Attacks> atk) {attacks = atk;};
        void addAtks(Attacks atk) {attacks.push_back(atk);};
    
    private:
        //Enemy Info
            string region;
            string name;
            string type;
            bool boss;
        
        //stats
            int hp;
            int maxHp;
            int strength;
            int dexterity;
            double magiRes;
            double physiRes;

        //leveling
            int minExp, maxExp, level;

        //status effects
            bool bound = false;
            bool counter = false;
            bool weakened;
            bool DOT; //damage of time
            int dotDuration;

        //drop chances
            int dropChance;
            int minNovas;
            int maxNovas;
            CraftingMaterials material;
            vector<Attacks> attacks;

};

#endif