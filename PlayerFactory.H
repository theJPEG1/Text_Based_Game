#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "Player.H"
#include "PrettyColors.H"
#include "attacksEffects.H"
#include "include/json.hpp"
    using json = nlohmann::json;
    using ordered_json = nlohmann::ordered_json;

#include <string>
    using std::string;
#include <fstream>
    using std::ifstream;
    using std::ofstream;
#include <iostream>
    using std::cin;
    using std::cout;
#include <vector>
    using std::vector;
#include <map>
    using std::map;

class PlayerFactory
{
    public:
        static PrettyColors colors;
        static Player createPlayer();
        static Player loadFromFile(const string& filename);

    private:
    //functions to make life easier
        void static createPlayerBirthday(string& name, string& monthBorn, string& timeBorn, int& dayBorn);
        void static allocateStatPoints(int& healthValue, int& strengthValue, int& dexterityValue, int& mindValue);

        

};


#endif