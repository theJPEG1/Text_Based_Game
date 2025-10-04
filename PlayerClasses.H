#ifndef PLAYERCLASSES_H
#define PLAYERCLASSES_H

#include <string>
    using std::string;

class PlayerClasses
{
    public:
        PlayerClasses(string cName, int hpMod, int strMod, int dexMod, int mindMod);

    //getters
        string getClassName(string newName);
        int getHpModi(int newHpM);
        int getStrModi(int newStM);
        int getDexModi(int newDeM);
        int getMindModi(int newMiM);
    //setters
        void setClassName();
        void setHpModi();
        void setStrModi();
        void setDexModi();
        void setMindModi();
        
    private:
        string className;
        int hpModifier;
        int strModifier;
        int dexModifier;
        int mindModifier;
};

#endif