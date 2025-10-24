
#ifndef PLAYER_H
#define PLAYER_H

#include "attacksEffects.H"
#include "PrettyColors.H"
#include "Enemy.H"

#include<string>
    using std::string;
#include <vector>
    using std::vector;
#include <map>
    using std::map;
#include <iostream>
    using std::cout;
    using std::cin;
#include <map>
    using std::map;

class Enemy;

class Player
{
    public:
        //Player(int hp=1, int maxHp =1, int str=1, int dex=1, int mind=1, string name="?", int playerLevel=1, int curXp = 1, int xpToNextLevel = 50);

        Player(string name, string monthBorn, string timeBorn, int dayBorn, 
               int hp, int str, int dex, int mind);

        Player(string name = "", string monthBorn = "", int dayBorn = 1, string timeBorn = "", 
               int hp = 1, int maxHp = 1, int str = 1, int dex = 1, int mind = 1, int luck = 1,
               int playerLevel = 1, int curExp = 1, int xpToLevel = 1);

    //PLAYER METHODS
        void takeDamage(int damage);
        void dealDamage(Enemy& target, int damage);

        void levelUp();
        
    //GETTERS
        //Player Information Setters
            string   getName()  {return playerName;};
            string  getMonth()       {return month;};
            string   getTime()        {return time;};
            int       getDay()         {return day;};

        //player stats getters
            int getMaxHealth()  {return maxHealthPoints;};
            int getDexterity()    {return dexterityStat;};
            int    getHealth()     {return healthPoints;};
            int  getStrength()     {return strengthStat;};
            int      getMind()         {return mindStat;};
            int   getMaxMana()          {return maxMana;};
            int      getMana()             {return mana;};
            int      getLuck()             {return luck;}; 
            
        //player level up getters
            int getXpToNextLevel()  {return xpToNextLevel;};
            int    getExperience()      {return currentXp;};
            int         getLevel()          {return level;};
        
        //Inventory Getters
            int getInventoryAmount(CraftingMaterials mat) {return inventory.find(mat)->second;};
            map<CraftingMaterials, int> getInventory() {return inventory;};
            int getDexterityPotionCount()   {return dexterityPotionCount;};
            int  getStrengthPotionCount()    {return strengthPotionCount;};
            int    getHealthPotionCount()      {return healthPotionCount;};
            int      getManaPotionCount()        {return manaPotionCount;};
            int                getNovas()                  {return novas;};
            

            //cpp Logic Below

            string getInventoryIdIndex(CraftingMaterials mat);

        // attack getters
            vector<Attacks>& getCustomAtks() {return customAtks;};
            vector<Attacks>& getAllAttacks() {return attackList;};
            vector<Attacks>&  getAllCombat()  {return allCombat;};
            vector<Attacks>&  getAllSpells()  {return spellList;};

            //cpp logic below

            Attacks getRandAttack();

        //Quest Getters  

    //SETTERS
        //Player Info Setters
            void    setName(string newName)     {playerName = newName;};

        //Player stat setters
            void   setMaxHealth(int newMax) {maxHealthPoints = newMax;};
            void   setDexterity(int newDex)   {dexterityStat = newDex;};        
            void    setStrength(int newStr)    {strengthStat = newStr;};
            
            void setMaxMana(int newMaxMana)     {maxMana = newMaxMana;};
            void       setHealth(int newHp)     {healthPoints = newHp;};
            void       setMind(int newMind)       {mindStat = newMind;};
            void       setMana(int newMana)           {mana = newMana;};
            
        //Attack setters
            void setSpecificSlot(Attacks newSlot, int index) {allCombat.at(index) = newSlot;};
            void        setAllCombat(vector<Attacks> combat)            {allCombat = combat;};

    //INCREASERS | ADDERS
        //Player Stats adders
            void increaseMaxHealth(int amt) {maxHealthPoints += amt;};
            void increaseDexterity(int amt)   {dexterityStat += amt;};
            void  increaseStrength(int amt)    {strengthStat += amt;};
            void      increaseLuck(int amt)            {luck += amt;};

            //cpp logic below

            void increaseHealth(int amt);
            void increaseMind(int amt);
            void increaseMana(int amt);

        //Player Inventory increasers
            void increaseHealthPotionCount(int newHealthPotionCount) {healthPotionCount += newHealthPotionCount;};  
            void     increaseManaPotionCount(int newManaPotionCount)     {manaPotionCount += newManaPotionCount;};
            void increaseNovas(int amount) {novas += amount;};
            void addToInventory(CraftingMaterials mat, int amount);
            void increaseExperience(int newXp)   {currentXp += newXp;};
        
        //Player attack increasers
            void addCustomAtk(Attacks atkToAdd) {customAtks.push_back(atkToAdd);};
            void addCombatSpells(Attacks atkToAdd) {spellList.push_back(atkToAdd);};
            void addCombatAttacks(Attacks atkToAdd) {attackList.push_back(atkToAdd);};

        //Player Quest adders
            void addQuest(string newQuest) {questLog.push_back(newQuest);};
    
    //MISC
        void printInventory(int rarity);

    private:
        //Player Information
            string playerName, month, time;
            int day;

        //Player stats
            int healthPoints, maxHealthPoints;
            int strengthStat;
            int dexterityStat;
            int mindStat, mana, maxMana;
            int luck; 

        //PLayer Level Up
            int level, currentXp, xpToNextLevel;

        //Player inventory things
            int healthPotionCount, manaPotionCount ,strengthPotionCount, dexterityPotionCount;
            int novas = 0;
            map <CraftingMaterials, int> inventory;

        //Player Attacks and spells
            vector<Attacks> attackList;
            vector<Attacks> spellList;

            vector<Attacks> customAtks;

            vector<Attacks> allCombat {8};
        
        //Player Questing
            vector<string> questLog;

        //misc
            PrettyColors colors;
};

#endif