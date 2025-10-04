#ifndef ATTACKEFFECTS_H
#define ATTACKEFFECTS_H

#include "Player.H"
#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <fstream>
    using std::ifstream;
#include <iostream>
    using std::cout;

#include "Enemy.H"
#include "include/json.hpp"
    using json = nlohmann::json;

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

        
    }
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

        // for(size_t i = 0; i < attackArray.size(); i++)
        // {
        //     Attacks atk;
        //     atk.id = attackArray[i]["ID"];
        //     atk.name = attackArray[i]["Name"];

        //     for(size_t k = 0; k < attackArray[i]["Effects"].size(); k++)
        //     {
        //         string effectID = attackArray[i]["Effects"][k];

        //         for(size_t l = 0; l < effectsArray.size(); l++)
        //         {
        //             if(effects[l].id == effectID)
        //             {
        //                 atk.thisEffects.push_back(effects[l]);
        //                 break;
        //             }
        //         }
        //     }

        //     attacks.push_back(atk);
        // }

        return attacks;
    };

   
};

#endif