#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
    using std::string;
#include <iostream>
    using std::cout;
    using std::cin;
    using std::getline;
#include <fstream>
    using std::ifstream;
#include <unordered_map>
    using std::unordered_map;
#include <map>
    using std::map;
#include <vector>
    using std::vector;
#include <cstdlib>

#include "include/json.hpp"
    using json = nlohmann::json;
#include "attacksEffects.h"
#include "EnemyFactory.h"
#include "Combat.h"
#include "Saving.h"

#include "GameState.h"

//every Actions possible (Location)
class Actions
{
    protected:
        GameState* gc = nullptr;

    private:
        unordered_map<std::string, std::function<void()>> actionMap;

        vector<string> effects =
        {
            "(-): Damage",
            "(<-): Self Damage",
            "(+): Healing",
            "(@): Freeze",
            "(&): Bind",
            "(->): Counter",
            "(#): Multicast",
            "(|>): Push Back",
            "(*): Splatter",
            "(0): Shield",
        };

        string currentJson;

        
        
        int potionsToAdd;

        int swimDepth = 0;
    
    public:
        /**
            @brief Creates an action map that uses keys to load functions

            @param p The player object used to run the game
        */
        Actions() = default;
        Actions(GameState* gameState);

        /**
         *   @brief Loads in an area using a json file
         *
         *   @param jsonToRead The file location to read to
        */
        string loadAreaFromJson(string jsonToRead);

        //ElderWell Methods
            //shopping and blacksmiths
                void buyItems();
                void craftItems();
                void sellItems();
                void rumors();
            //guild center
                void viewGuildCard();
                void viewInventory();
                void viewQuests();
                void printEffectList();
            //town center
                void wellTalk();
                void tossInACoin();
            //tavern
                void keyAsk();
                void drunkenTalk();
                void barKeepTalk();
                void buyRoom();
            //quests
                //well quest
                    void wellSwim();
                    void wellKey();
                    void seduceWellDoor();

        //Elderwell Foreset Methods
            void fight();
            void efEncounter();
            void efForage();
            
            void efHorseCartPil();
            void efHorseCartHelp();

            void fairyRelease();

            void makeCamp();
            void pillageCamp();

            void healWolf();
            void killWolf();

            void pickRose();
        

        //misc to make things run smootehr
            void addHealthPots();
            void addManaPots();

            void saveQuit();
};

#endif
