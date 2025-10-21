#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
    using std::string;
#include <iostream>
    using std::cout;
    using std::cin;
#include <fstream>
    using std::ifstream;
#include <unordered_map>
    using std::unordered_map;
#include <map>
    using std::map;
#include <vector>
    using std::vector;

#include "include/json.hpp"
    using json = nlohmann::json;
#include "Player.H"
#include "PrettyColors.H"
#include "attacksEffects.H"

//every Actions possible (Location)
class Actions
{
    private:
        unordered_map<std::string, std::function<void()>> actionMap;
        map <string, CraftingMaterials> materials;
        map <string, Attacks> playerAttacks;

        Player player;
        PrettyColors color;
        string currentJson;

        int potionsToAdd;
    
    public:
        /*
            @brief Creates an action map that uses keys to load functions

            @param p The player object used to run the game
        */
        Actions(Player& p);

        void loadCraftingMats(string fileLocation);
        void loadAllAttacks(string fileLocation);

        /*
         *   @brief Loads in an area using a json file
         *
         *   @param jsonToRead The file location to read to
        */
        void loadAreaFromJson(string jsonToRead);

        void buyItems();
        void craftItems();

        //misc to make things run smootehr
        void addHealthPots();
        void addManaPots();

    

};

#endif