#ifndef ATTACKEFFECTS_H
#define ATTACKEFFECTS_H

#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <fstream>
    using std::ifstream;
    using std::ofstream;
#include <iostream>
    using std::cout;
    using std::cin;
#include <unordered_map>
    using std::unordered_map;
#include <map>
    using std::map;

#include "include/json.hpp"
    using json = nlohmann::json;
    using ordered_json = nlohmann::ordered_json;

class Player;  // forward declare
class Enemy;

struct Effects
{
    /*
        Symbols and meanings
        -  Damage              V
        <- Self Damage         V
        +  Healing             V
        @  Freeze              V
        &  Bind                V
        -> Counter             V
        #  Multicast

        |> Push Back
        *  Splatter
        0  Shield
        

        Not effects jut modifiers
        ^  Dexterity up
        v  Dexterity down

    */
    unordered_map<std::string, std::function<void(Enemy&, Player&, string turn)>> actionMap;

    string         id = "";
    string       name = "";
    string effectType = "";

    int    baseDmg = 0;
    int    dexModi = 0;
    int bindChance = 0;
    int critChance = 0;
    int healingAmt = 0;

    int         shield = 0; //not done. Apply in combat
    int       multCast = 0;
    int   freezeChance = 0;
    int splatterAmount = 0; //not done (not on high importance)
    

    bool    counter = false; 
    bool   pushBack = false; //not done (not on high importance)
    bool selfDamage = false;

    double damageToDo = 0;

    Effects();
    Effects(const Effects& other);

    void rebuildActionMap();

    void handleEffects(Enemy& target, Player& p, string turn);

    void damage(Enemy& target, Player& p, string turn);
    void damageSelf(Enemy& target, Player& p, string turn);
    void healing(Enemy& target, Player& p, string turn);
    void freeze(Enemy& target, Player& p, string turn);
    void bind(Enemy& target, Player& p, string turn);
    void effectCounter(Enemy& target, Player& p, string turn);


    Effects operator+=(Effects effect)
    {
        this->baseDmg += effect.baseDmg;
        this->dexModi += effect.dexModi;
        this->selfDamage = effect.selfDamage;
        this->bindChance += effect.bindChance;
        this->critChance += effect.critChance;
        this->healingAmt += effect.healingAmt;

        return (*this);
    };

    Effects& operator=(const Effects& other)
    {
        this->id = other.id;
        this->name = other.name;
        this->effectType = other.effectType;
        this->baseDmg = other.baseDmg;
        this->dexModi = other.dexModi;
        this->bindChance = other.bindChance;
        this->critChance = other.critChance;
        this->healingAmt = other.healingAmt;
        this->shield = other.shield;
        this->multCast = other.multCast;
        this->freezeChance = other.freezeChance;
        this->splatterAmount = other.splatterAmount;
        this->counter = other.counter;
        this->pushBack = other.pushBack;
        this->selfDamage = other.selfDamage;
        this->damageToDo = other.damageToDo;

        // Rebuild actionMap
        actionMap.clear();
        this->actionMap["-"]  = [this](Enemy& e, Player& p, string turn){ damage(e, p, turn); };
        this->actionMap["<-"] = [this](Enemy& e, Player& p, string turn){ damageSelf(e, p, turn); };
        this->actionMap["+"]  = [this](Enemy& e, Player& p, string turn){ healing(e, p, turn); };
        this->actionMap["#"]  = [this](Enemy& e, Player& p, string turn){ freeze(e, p, turn); };
        this->actionMap["&"]  = [this](Enemy& e, Player& p, string turn){ bind(e, p, turn); };
        this->actionMap["->"] = [this](Enemy& e, Player& p, string turn){ effectCounter(e, p, turn); };
        
        return (*this);
    }

};

struct CraftingMaterials
{
    string id = "";
    string name = "";
    int rarity = 1;
    int price = 1;
    vector<Effects> matEffects;

    vector<CraftingMaterials> loadCraftingMaterialss(const std::string& craftingFile)
    {
        ifstream fileIn(craftingFile);
        json j;
        fileIn >> j;

        json CraftingArray = j["Crafting Materials"];

        vector<CraftingMaterials> materials;

        for(size_t i = 0; i < CraftingArray.size(); i++)
        {
            CraftingMaterials craftMat;

            craftMat.id = CraftingArray[i]["ID"];

            craftMat.name = CraftingArray[i]["Name"];

            craftMat.rarity = CraftingArray[i]["Rarity"];

            craftMat.price = CraftingArray[i]["Cost"];

            for(size_t o = 0; o < CraftingArray[i]["Effects"].size(); o++)
            {   
                Effects e;
                
                e.id = CraftingArray[i]["Effects"][o]["ID"];

                e.effectType = CraftingArray[i]["Effects"][o]["type"];
                
                //include new effects and evetything!!!!
                if(!CraftingArray[i]["Effects"][o]["type"].is_null())
                {
                    e.effectType = CraftingArray[i]["Effects"][o]["type"];
                }

                if(!CraftingArray[i]["Effects"][o]["baseDmg"].is_null())
                {
                    e.baseDmg = CraftingArray[i]["Effects"][o]["baseDmg"];
                }

                if(!CraftingArray[i]["Effects"][o]["dexModi"].is_null())
                {
                    e.dexModi = CraftingArray[i]["Effects"][o]["dexModi"];
                }

                if(!CraftingArray[i]["Effects"][o]["bindChance"].is_null())
                {
                    e.bindChance = CraftingArray[i]["Effects"][o]["bindChance"];
                }

                if(!CraftingArray[i]["Effects"][o]["critChance"].is_null())
                {
                   e.critChance = CraftingArray[i]["Effects"][o]["critChance"];
                }

                if(!CraftingArray[i]["Effects"][o]["selfDamage"].is_null())
                {
                    e.selfDamage = CraftingArray[i]["Effects"][o]["selfDamage"];
                }

                if(!CraftingArray[i]["Effects"][o]["baseHealing"].is_null())
                {   
                    e.healingAmt = CraftingArray[i]["Effects"][o]["baseHealing"];
                }
                
                if(!CraftingArray[i]["Effects"][o]["freezeChance"].is_null())
                {   
                    e.freezeChance = CraftingArray[i]["Effects"][o]["freezeChance"];
                }

                if(!CraftingArray[i]["Effects"][o]["pushBack"].is_null())
                {   
                    e.pushBack = CraftingArray[i]["Effects"][o]["pushBack"];
                }

                if(!CraftingArray[i]["Effects"][o]["enemyJump"].is_null())
                {   
                    e.splatterAmount = CraftingArray[i]["Effects"][o]["enemyJump"];
                }

                if(!CraftingArray[i]["Effects"][o]["counter"].is_null())
                {   
                    e.counter = CraftingArray[i]["Effects"][o]["counter"];
                }

                if(!CraftingArray[i]["Effects"][o]["shieldDuration"].is_null())
                {   
                    e.shield = CraftingArray[i]["Effects"][o]["shieldDuration"];
                }

                if(!CraftingArray[i]["Effects"][o]["spellCount"].is_null())
                {   
                    e.multCast = CraftingArray[i]["Effects"][o]["spellCount"];
                }


            craftMat.matEffects.push_back(e);
            }

            materials.push_back(craftMat);
        }

        return materials;
    };

    // Add this operator to enable sorting
    bool operator<(const CraftingMaterials& other) const 
    {
        return name < other.name;
    };

};

struct Attacks
{
    string id;
    string name;
    string type;
    int manacost;
    vector<Effects> thisEffects;

    vector<Attacks> loadAttacks(const std::string& attacksFile)
    {
        ifstream fileIn(attacksFile);
        json j;
        fileIn >> j;

        json attackArray = j["Attacks"];

        vector<Attacks> attacks;

        for(size_t i = 0; i < attackArray.size(); i++)
        {
            Attacks atk;

            atk.id = attackArray[i]["ID"];

            atk.name = attackArray[i]["Name"];

            atk.type = attackArray[i]["type"];

            if(!attackArray[i]["Mana"].is_null())
            {
                atk.manacost = attackArray[i]["Mana"];
            }

            for(size_t o = 0; o < attackArray[i]["Effects"].size(); o++)
            {   
                Effects e;
                
                e.id = attackArray[i]["Effects"][o]["ID"];

                e.effectType = attackArray[i]["Effects"][o]["type"];

                if(!attackArray[i]["Effects"][o]["baseDmg"].is_null())
                {
                    e.baseDmg = attackArray[i]["Effects"][o]["baseDmg"];
                }

                if(!attackArray[i]["Effects"][o]["dexModi"].is_null())
                {
                    e.dexModi = attackArray[i]["Effects"][o]["dexModi"];
                }

                if(!attackArray[i]["Effects"][o]["bindChance"].is_null())
                {
                    e.bindChance = attackArray[i]["Effects"][o]["bindChance"];
                }

                if(!attackArray[i]["Effects"][o]["critChance"].is_null())
                {
                   e.critChance = attackArray[i]["Effects"][o]["critChance"];
                }

                if(!attackArray[i]["Effects"][o]["selfDamage"].is_null())
                {
                    e.selfDamage = attackArray[i]["Effects"][o]["selfDamage"];
                }

                if(!attackArray[i]["Effects"][o]["baseHealing"].is_null())
                {   
                    e.healingAmt = attackArray[i]["Effects"][o]["baseHealing"];
                }

                if(!attackArray[i]["Effects"][o]["freezeChance"].is_null())
                {   
                    e.freezeChance = attackArray[i]["Effects"][o]["freezeChance"];
                }

                if(!attackArray[i]["Effects"][o]["pushBack"].is_null())
                {   
                    e.pushBack = attackArray[i]["Effects"][o]["pushBack"];
                }

                if(!attackArray[i]["Effects"][o]["enemyJump"].is_null())
                {   
                    e.splatterAmount = attackArray[i]["Effects"][o]["enemyJump"];
                }

                if(!attackArray[i]["Effects"][o]["counter"].is_null())
                {   
                    e.counter = attackArray[i]["Effects"][o]["counter"];
                }

                if(!attackArray[i]["Effects"][o]["shieldDuration"].is_null())
                {   
                    e.shield = attackArray[i]["Effects"][o]["shieldDuration"];
                }

                if(!attackArray[i]["Effects"][o]["spellCount"].is_null())
                {   
                    e.multCast = attackArray[i]["Effects"][o]["spellCount"];
                }

                atk.thisEffects.push_back(e);

               
            }

            attacks.push_back(atk);
        }
        return attacks;
    };

    static Attacks createAttack(CraftingMaterials mat1, CraftingMaterials mat2, CraftingMaterials mat3)
    {
        //check if weapon or spell
        //load in spell inventory
        // allow for 5 or 3 materials depedng on weapon or spell, and put them in a vectoe
        

        vector<CraftingMaterials> mats;

        mats.push_back(mat1);
        mats.push_back(mat2);
        mats.push_back(mat3);

        //physical attack
        Attacks atk;
        

        vector<Effects> customEffects;

        for(size_t i = 0; i < mats.size(); i++)
        {
            for(size_t k = 0; k < mats.at(i).matEffects.size(); k++)
            {
                if(customEffects.empty())
                {
                    customEffects.push_back(mats.at(i).matEffects.at(k));
                }

                else
                {
                    for(size_t j = 0; j < customEffects.size(); j++)
                    {
                        //combine like effects
                        if(mats.at(i).matEffects.at(k).id == customEffects.at(j).id)
                        {
                            customEffects.at(j) += mats.at(i).matEffects.at(k);
                        }

                        else
                        {
                             customEffects.push_back(mats.at(i).matEffects.at(k));
                        }   
                    }
                }
            }
        }

        atk.thisEffects = customEffects;

        atk.thisEffects.at(0).baseDmg += mat1.rarity;
        atk.thisEffects.at(0).baseDmg += mat2.rarity;
        atk.thisEffects.at(0).baseDmg += mat3.rarity;


        //allow player to name it.
        atk.type = "attack";
        string weaponName;
        cout << "\nName Your Weapon: ";

        getline(cin, atk.id);
        atk.name = atk.id;

        return atk;
    };
};



#endif