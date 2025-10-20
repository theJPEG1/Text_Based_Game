#include "Saving.H"
#include "Player.H"
#include "include/json.hpp"
    using json = nlohmann::json;
    using ordered_json = nlohmann::ordered_json;
#include "PrettyColors.H"
#include "attacksEffects.H"

#include <fstream>
    using std::ofstream;   
#include <string>
    using std::string; 
#include <iostream>
    using std::cout;

void Saving::saveToFile(Player& playerToSave, const string& statsFile, const string& combatMagicFile)
{
    PrettyColors color;
    ofstream statsF;
    ofstream combatF;


    if(!statsF || !combatF)
    {
        cout << color.RED << "Error opening file.\n" << color.DEFAULT;
        exit(1);
    }

    statsF.open(statsFile);
    combatF.open(combatMagicFile);

    ordered_json playerStats;
    playerStats["name"] = playerToSave.getName();
    playerStats["hp"] = playerToSave.getHealth();
    playerStats["maxHp"] = playerToSave.getMaxHealth();
    playerStats["strength"] = playerToSave.getStrength();
    playerStats["dexterity"] = playerToSave.getDexterity();
    playerStats["mind"] = playerToSave.getMind();
    playerStats["level"] = playerToSave.getLevel();
    playerStats["xp"] = playerToSave.getExperience();
    playerStats["xpToNextLevel"] = playerToSave.getXpToNextLevel();
    playerStats["healthPotions"] = playerToSave.getHealthPotionCount();
    playerStats["manaPotions"] = playerToSave.getManaPotionCount();
    playerStats["strengthPotions"] = playerToSave.getStrengthPotionCount();
    playerStats["dexterityPotions"] = playerToSave.getDexterityPotionCount();


    json j;
    ordered_json playerCombatAttacks;

    playerCombatAttacks["Attack IDs"][0]["ID"] = playerToSave.getAllCombat().at(0).id;
    playerCombatAttacks["Attack IDs"][1]["ID"] = playerToSave.getAllCombat().at(1).id;
    playerCombatAttacks["Attack IDs"][2]["ID"] = playerToSave.getAllCombat().at(2).id;
    playerCombatAttacks["Attack IDs"][3]["ID"] = playerToSave.getAllCombat().at(3).id;
    playerCombatAttacks["Attack IDs"][4]["ID"] = playerToSave.getAllCombat().at(4).id;
    playerCombatAttacks["Attack IDs"][5]["ID"] = playerToSave.getAllCombat().at(5).id;
    playerCombatAttacks["Attack IDs"][6]["ID"] = playerToSave.getAllCombat().at(6).id;
    playerCombatAttacks["Attack IDs"][7]["ID"] = playerToSave.getAllCombat().at(7).id;
    

    statsF << playerStats;
    combatF << playerCombatAttacks;

    std::ofstream outStats(statsFile);
    outStats << playerStats.dump(3);

    std::ofstream outAttacks(combatMagicFile);
    outAttacks << playerCombatAttacks.dump(3);

    statsF.close();
    combatF.close();

   
};

void Saving::saveAttacks(const std::string& filename, vector<Attacks> atks)
{
    PrettyColors color;
    ofstream out;

    ordered_json attackArray = ordered_json::array();
    out.open(filename);

    for(size_t i = 0; i < atks.size(); i++)
    {
        ordered_json attackObj;

        attackObj["ID"] = atks.at(i).id;
        attackObj["Name"] = atks.at(i).name;
        attackObj["type"] = atks.at(i).type;

        ordered_json effectsArray = ordered_json::array();
        for(size_t o = 0; o < atks.at(i).thisEffects.size(); o++)
        {
            ordered_json effectObj;
            effectObj["ID"] = atks.at(i).thisEffects.at(o).id;
            effectObj["type"] = atks.at(i).thisEffects.at(o).effectType; 

            if(atks.at(i).thisEffects.at(o).baseDmg != 0)
            {
                effectObj["baseDmg"] = atks.at(i).thisEffects.at(o).baseDmg;
            }

            if(atks.at(i).thisEffects.at(o).dexModi != 0)
            {
                effectObj["dexModi"] = atks.at(i).thisEffects.at(o).dexModi;;
            }

            if(atks.at(i).thisEffects.at(o).bindChance != 0)
            {
               effectObj["bindChance"] = atks.at(i).thisEffects.at(o).bindChance;;
            }

            if(atks.at(i).thisEffects.at(o).critChance != 0)
            {
                effectObj["critChance"] = atks.at(i).thisEffects.at(o).critChance;;
            }

            if(atks.at(i).thisEffects.at(o).selfDamage != 0)
            {
                effectObj["selfDamage"] = atks.at(i).thisEffects.at(o).selfDamage;;
            }

            if(atks.at(i).thisEffects.at(o).healingAmt != 0)
            {   
                effectObj["baseHealing"] = atks.at(i).thisEffects.at(o).healingAmt;;
            }

            effectsArray.push_back(effectObj);
        }

        attackObj["Effects"] = effectsArray;
        attackArray.push_back(attackObj);

    }

    ordered_json playerStats;
    playerStats["Attacks"] = attackArray;

    out << playerStats.dump(3);
    out.close();

};
