#ifndef ATTACKEFFECTS_H
#define ATTACKEFFECTS_H

#include "Player.H"
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

#include "Enemy.H"
#include "include/json.hpp"
    using json = nlohmann::json;
    using ordered_json = nlohmann::ordered_json;

struct Effects
{
    string id = "";
    string name = "";
    string effectType = "";

    int baseDmg = 0;
    int dexModi = 0;
    bool selfDamage = 0;
    int bindChance = 0;
    int critChance = 0;
    int healingAmt = 0;


    void applyEffect(Enemy& target)
    {
        if(bindChance > 0)
        {
            if(rand() % 100 + 1 < bindChance)
            {
                cout << "";
                target.setBind(true);
            }

            else {cout << "\nNOBOUND\n";}
        }

        if(selfDamage)
        {
            selfDamage = baseDmg / 2;
        }

        
    };

    Effects operator+=(Effects effect)
    {
        this->baseDmg += effect.baseDmg;
        this->dexModi += effect.baseDmg;
        this->selfDamage = effect.selfDamage;
        this->bindChance += effect.bindChance;
        this->critChance += effect.critChance;
        this->healingAmt += effect.healingAmt;

        return (*this);
    };
};

struct CraftingMaterials
{
    string id;
    string name;
    int rarity;
    int price;
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

            craftMat.matEffects.push_back(e);
            }

            materials.push_back(craftMat);
        }

        return materials;
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

        bool foundEffect = false;

        //physical attack
        Attacks atk;
        

        vector<Effects> customEffects;

        for(size_t i = 0; i < mats.size(); i++)
        {
            cout << "| " << mats.at(i).id << " |\n";

            for(size_t k = 0; k < mats.at(i).matEffects.size(); k++)
            {
                cout << "| " << mats.at(i).matEffects.at(k).id << " |\n";

                if(customEffects.empty())
                {
                    cout << "\n Effects Vector is empty. Pushing " << mats.at(i).matEffects.at(k).id << "\n";
                    customEffects.push_back(mats.at(i).matEffects.at(k));
                }

                else
                {
                    cout << "\n Effects Vector is not empty. Attempting Pushing " << mats.at(i).matEffects.at(k).id<< "\n";

                    
        
                        for(size_t j = 0; j < customEffects.size(); j++)
                        {
                            //combine like effects
                            if(mats.at(i).matEffects.at(k).id == customEffects.at(j).id)
                            {
                                cout << "\n Effects exists in vector. Cp,bining " << mats.at(i).matEffects.at(k).id<< "\n";
                                customEffects.at(j) += mats.at(i).matEffects.at(k);
                                foundEffect = true;
                            }

                            else
                            {
                                cout << "\n Effects doesnt in vector. Pushing " << mats.at(i).matEffects.at(k).id<< "\n";
                                customEffects.push_back(mats.at(i).matEffects.at(k));
                                foundEffect = true;
                            }

                            
                        }
                    
                }
            }

            foundEffect = false;
        }

        atk.thisEffects = customEffects;

        atk.thisEffects.at(0).baseDmg += mat1.rarity;
        atk.thisEffects.at(0).baseDmg += mat2.rarity;
        atk.thisEffects.at(0).baseDmg += mat3.rarity;


        //allow player to name it.
        atk.type = "attack";
        string weaponName;
        cout << "Name Your Weapon: ";
        cin.ignore();

        getline(cin, atk.id);
        atk.name = atk.id;

        return atk;
    };
};



#endif