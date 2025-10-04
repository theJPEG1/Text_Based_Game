#ifndef SAVING_H
#define SAVING_H

#include "Player.H"
#include "include/json.hpp"
    using json = nlohmann::json;
    
#include "attacksEffects.H"

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
};

#endif