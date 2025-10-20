#ifndef ENEMY_H
#define ENEMY_H

#include <string>
    using std::string;

class Player;

class Enemy
{
    private:
        string region;
        string name;
        string type;
        int hp;
        int maxHp;
        int strength;
        int dexterity;
        bool boss;
        double magiRes;
        double physiRes;

        int minExp, maxExp, level;

        bool bound = false;
        bool counter = false;
        bool weakened;
        bool DOT; //damage of time
        int dotDuration;

    public:
        Enemy(string thisRegion="none", string thisName="?", string enemyType="?", 
              double phyRes=0, double magRes=0, bool isBoss=false, int health=1, 
              int strength=1, int dexterity=1, int minExp=1, int maxExp=5, 
              int level=1);
        
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

        bool getBound() {return bound;};
        bool getCounter() {return counter;};
        int getDotDuration() {return dotDuration;};

        int getMinExp();
        int getMaxExp();

        void debuffs();

        void displaySelf();

    //setters
        void setName(string newName);

        void setBind(bool isBound) {bound = isBound;};
        void setCounter(bool isCounter) {counter = isCounter;};
        void setDOT(bool isDot) {DOT = isDot;};
        void setWeakened(bool isWeakened) {weakened = isWeakened;};
        void setDotDuration(int duration) {dotDuration = duration;};
        
};

#endif