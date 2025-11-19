#include "Quests.h"


/**
 * @brief Construct an empty Quest Objective
 */
QuestObjective::QuestObjective()
{
    collected = 0;
    collectedTotal = 0;
    hasItem = false;
};

/**
 * @brief Construct a new Quest Objective object
 * 
 * @param item Key item needed for the quest
 */
QuestObjective::QuestObjective(bool item)
{
    hasItem = item;
};

/**
 * @brief Construct a new Quest Objective object
 * 
 * @param itemToGet The item to find 
 * @param amt       how many of the item you need
 */
QuestObjective::QuestObjective(CraftingMaterials itemToGet, int amt)
{
    collectedTotal = amt;
    item = itemToGet;
}

