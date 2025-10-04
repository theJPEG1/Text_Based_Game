#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "Player.H"
#include <string>
    using std::string;  
#include <fstream>
    using std::ifstream;

class PlayerFactory
{
    public:
        static Player loadFromFile(const string& filename);
        static Player createPlayer();

};

#endif