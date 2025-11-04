#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Player.H"

struct GameState
{
    GameState() = default;
    GameState(Player& p, map<string, CraftingMaterials>& allMaterials, map<string, Attacks>& allAttacks)
    {
        player = p;
        mats = allMaterials;
        atks = allAttacks;
    };

    Player player;
    map<string, CraftingMaterials> mats;
    map<string, Attacks> atks;
    PrettyColors colors;
    WeightedGen gen;
    //vector<Quest> quests;
};

#endif