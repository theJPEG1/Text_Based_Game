
#ifndef PLAYER_H
#define PLAYER_H

#include "attacksEffects.H"

#include<string>
    using std::string;
#include <vector>
    using std::vector;

class Enemy;

class Player
{
    public:

        Player(int hp=1, int maxHp =1, int str=1, int dex=1, int mind=1, string name="?", int playerLevel=1, int curXp = 1, int xpToNextLevel = 50);

        void takeDamage(int damage);
        void dealDamage(Enemy& target, int damage);

        void levelUp();

    //display player's stuff
        void displayWeaponMat();
        void displaySpellMat();
        void displaySpells();
        void displayStats();
        
        
    //getters
        
    //player stats getters
        int getMaxHealth()  {return maxHealthPoints;};
        int getDexterity()    {return dexterityStat;};
        int    getHealth()     {return healthPoints;};
        int  getStrength()     {return strengthStat;};
        string   getName()       {return playerName;};
        int      getMind()         {return mindStat;};
        int   getMaxMana()          {return maxMana;};
        int      getMana()             {return mana;};
        
    //player level up getters
        int getXpToNextLevel()  {return xpToNextLevel;};
        int    getExperience()      {return currentXp;};
        int         getLevel()          {return level;};
       
    //Potion getters
        int getDexterityPotionCount()   {return dexterityPotionCount;};
        int  getStrengthPotionCount()    {return strengthPotionCount;};
        int    getHealthPotionCount()      {return healthPotionCount;};
        int      getManaPotionCount()        {return manaPotionCount;};

    //inventory getters
        // vector<CraftingMaterial> getWeaponMatInv() {return weaponMatInventory;};
        // vector<CraftingMaterial>  getSpellMatInv()  {return spellMatInventory;};

        // CraftingMaterial getMaterial(string materialName, string invType);

    //spell books getters
        // vector<Spells> getCombatBook()  {return combatBook;};
        // vector<Spells>  getSpellBook()   {return spellBook;};

        // Spells getSpell(string name);

    //setters
        void   setDexterity(int newDex) {dexterityStat = newDex;};        
        void    setStrength(int newStr)  {strengthStat = newStr;};
        void    setName(string newName)   {playerName = newName;};
        void setMaxMana(int newMaxMana)   {maxMana = newMaxMana;};
        void       setMind(int newMind)     {mindStat = newMind;};

        void setDexterityPotionCount(int newDexterityPotionCount)   {dexterityPotionCount = newDexterityPotionCount;};   
        void   setStrengthPotionCount(int newStrengthPotionCount)     {strengthPotionCount = newStrengthPotionCount;};
        void       setHealthPotionCount(int newHealthPotionCount)        {healthPotionCount += newHealthPotionCount;};  
        void           setManaPotionCount(int newManaPotionCount)             {manaPotionCount = newManaPotionCount;};

        void setExperience(int newXp)   {currentXp += newXp;};

        void    setHealth(int newHp);
        void    setMana(int newMana);

        // void setCombatBook(int index, Spells newSpell);
        // void                 addSpell(Spells newSpell);

        // void addToInventory(CraftingMaterial material, int amount, string type);

        void setEmptyInventory();

        void setCombatAttacks(vector<Attacks> atks) {combatAttacks = atks;};
        void setCombatSpells(vector<Attacks> spels) {combatSpells = spels;};
        void setAllCombat(vector<Attacks> combat) {allCombat = combat;};

        void addCustomAtk(Attacks atkToAdd) {customAtks.push_back(atkToAdd);};
        void addCombatSpells(Attacks atkToAdd) {spellList.push_back(atkToAdd);};

        void setSpecificSlot(Attacks newSlot, int index) {allCombat.at(index) = newSlot;};

        vector<Attacks>& getCombatAttacks() {return combatAttacks;};
        vector<Attacks>& getCombatSpells() {return combatSpells;};
        vector<Attacks>& getAllCombat() {return allCombat;};
        vector<Attacks>& getCustomAtks() {return customAtks;};
        
        Attacks getRandAttack();


    private:
        int healthPoints, maxHealthPoints, strengthStat, dexterityStat, mindStat, mana, maxMana;
        int healthPotionCount, manaPotionCount ,strengthPotionCount, dexterityPotionCount;
        int level, currentXp, xpToNextLevel;
        //weapon class
        string playerName;
        
        // vector<Spells> spellBook {};
        // vector<Spells> combatBook {4};
        // vector<CraftingMaterial> weaponMatInventory {};
        // vector<CraftingMaterial> spellMatInventory  {};

        vector<Attacks> attackList {};
        vector<Attacks> combatAttacks {4};
        vector<Attacks> spellList;
        vector<Attacks> combatSpells;

        vector<Attacks> customAtks;

        vector<Attacks> allCombat {8};


        
        

};

#endif