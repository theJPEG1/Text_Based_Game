#ifndef SAVING_H
#define SAVING_H

#include "Player.h"
#include "include/json.hpp"
    using json = nlohmann::json;
    
#include "attacksEffects.h"

#include <string>
    using std::string;
#include <fstream>
    using std::ofstream;
#include <vector>
    using std::vector;

class Saving
{
    public:
        static void saveToFile(Player& playerToSave, const std::string& filename, const string& combatMagicFile);
        static void saveAttacks(const std::string& filename, vector<Attacks> atks);
        static void saveInventory(const std::string& filename, Player& playerToSave);
};

#endif
