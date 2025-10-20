#include "Player.H"
#include "PrettyColors.H"
#include "Enemy.H"

#include <iostream>
    using std::cout;
    using std::cin;

#include "Enemy.H"

PrettyColors color;
PrettyColors colors;

/**
 * @brief Constructs a Player object with initial stats and inventory.
 * @param hp Initial health points
 * @param maxHp Initial max health points
 * @param str Initial strength stat
 * @param dex Initial dexterity stat
 * @param mind Initial mind stat
 * @param name Player's name
 * @param playerLevel Starting level
 * @param curXp Starting experience points
 * @param xpToNextLevel XP required for next level
 */
Player::Player(int hp, int maxHp, int str, int dex, int mind, string name, int playerLevel, int curXp, int xpToNextLevel)
{
    maxHealthPoints = maxHp;
    dexterityStat = dex;
    strengthStat = str;
    playerName = name;
    healthPoints = hp;
    mindStat = mind;
    
    this->xpToNextLevel = xpToNextLevel;
    level = playerLevel;
    currentXp = curXp;
    
    mana = mind * 5;
    maxMana = mana;
    
    dexterityPotionCount = 1;
    strengthPotionCount = 2;
    healthPotionCount = 3;
    manaPotionCount = 3;
};

/**
 * @brief Levels up the player, increases stats, and allows stat allocation.
 */
void Player::levelUp()
{
    PrettyColors colors;
    currentXp -= xpToNextLevel;
    xpToNextLevel *= 1.5;
    maxHealthPoints += 2;
    dexterityStat += 2;
    strengthStat += 2;
    mindStat += 2;
    level += 1;

    bool healthAllocated    = false;
    bool strengthAllocated  = false;
    bool dexterityAllocated = false;
    bool mindAllocated      = false;

    int allocationPoints  = 6;
    int pointsToSend      = 0;

    cout << colors.DEFAULT << "You have leveled up!\n";

    while (allocationPoints >= 1)
    {
        if(!healthAllocated)
        {
            cout << "You have " << allocationPoints << " Points left for allocation.\n";
            cout << "There are 4 stats: " << colors.CYAN << "Health | " << 
                colors.RED << "Strength | " << colors.GREEN << "Dexterity | " << colors.MAGENTA << "Mind |" << colors.DEFAULT << "\n"; 
            cout << "How many points towards " << colors.CYAN << "Health: ";
            cin >> pointsToSend;

            if(allocationPoints >= pointsToSend && pointsToSend >= 0 && allocationPoints > 0)
            {
                healthAllocated = true;
                maxHealthPoints += pointsToSend;
                allocationPoints -= pointsToSend;
                cout << colors.DEFAULT;

                colors.clearScreen();
            }

            else
            {
                cout << "\n" << colors.RED << "! INVALID INPUT !\n" << colors.DEFAULT;
            }
        }

        if(!strengthAllocated)
        {
            cout << "You have " << allocationPoints << " Points left for allocation.\n";
            cout << "There are 4 stats: " << colors.CYAN << "Health | " << 
                colors.RED << "Strength | " << colors.GREEN << "Dexterity | " << colors.MAGENTA << "Mind |" << colors.DEFAULT; 
            cout << "\nHow many points towards " << colors.RED << "Strength: ";
            cin >> pointsToSend;

            if(allocationPoints >= pointsToSend && pointsToSend >= 0 && allocationPoints > 0)
            {
                strengthAllocated = true;
                strengthStat += pointsToSend;
                allocationPoints -= pointsToSend;
                cout << colors.DEFAULT;

                colors.clearScreen();
            }

            else
            {
                cout << "\n" << colors.RED << "! INVALID INPUT !\n" << colors.DEFAULT;
            }
        }

        if(!dexterityAllocated)
        {
            cout << "You have " << allocationPoints << " Points left for allocation.\n";
            cout << "There are 4 stats: " << colors.CYAN << "Health | " << 
                colors.RED << "Strength | " << colors.GREEN << "Dexterity | " << colors.MAGENTA << "Mind |" << colors.DEFAULT; 
            cout << "\nHow many points towards " << colors.GREEN << "Dexterity: ";
            cin >> pointsToSend;

            if(allocationPoints >= pointsToSend && pointsToSend >= 0 && allocationPoints > 0)
            {
                dexterityAllocated = true;
                dexterityAllocated += pointsToSend;
                allocationPoints -= pointsToSend;
                cout << colors.DEFAULT;

                colors.clearScreen();
            }

            else
            {
                cout << "\n" << colors.RED << "! INVALID INPUT !\n" << colors.DEFAULT;
            }
        }

        if(!mindAllocated)
        {
            mindAllocated = true;
            mindStat += allocationPoints;
            allocationPoints -= allocationPoints;
        }
    }

    mana = mindStat * 5;

    maxMana = mana;
    healthPoints = maxHealthPoints;

    // cout << color.YELLOW << "\nYou leveled up to Level " << level << "!\n"
    //      << color.CYAN << "+ " << healthIncrease << " Max Health\n"
    //      << color.RED << "+ " << strengthIncrease << " Strength\n"
    //      << color.GREEN << "+ " << dexterityIncrease << " Dexterity\n"
    //      << color.MAGENTA << "+ " << mindIncrease << " Mind\n" << color.DEFAULT;

    color.pauseTerminal(5);
    color.clearScreen();
};

/**
 * @brief Displays the player's current stats in the terminal.
 */
void Player::displayStats()
{
    cout << color.YELLOW << "Name: " << playerName << "\n"
         << color.CYAN << "Health: " << healthPoints << "/" << maxHealthPoints << "\n"
         << color.RED << "Damage: " << "1-" << strengthStat << "\n"
         << color.GREEN << "Dexterity: " << dexterityStat << "\n"
         << color.MAGENTA << "Mind: " << mindStat << color.DEFAULT << "\n"
         << color.MAGENTA << "Mana: " << mana << "/" << maxMana << color.DEFAULT << "\n";

    color.pauseTerminal(5);
    color.clearScreen();
};

// void Player::displaySpells()
// {
//     if(!spellBook.empty())
//     {
//         for(size_t i = 0; i < spellBook.size(); i++)
//         {
//             spellBook.at(i).displaySpell();
//         }
//     }

//     else
//     {
//         cout << color.RED << "\n!SPELL BOOK IS EMPTY!\n" << color.DEFAULT;
//     }
// };

/**
 * @brief Reduces player's health by the given damage amount.
 * @param damage Amount of damage to take
 */
void Player::takeDamage(int damage)
{
    healthPoints -= damage;
};

/**
 * @brief Deals damage to an enemy target.
 * @param target Reference to the enemy
 * @param damage Amount of damage to deal
 */
void Player::dealDamage(Enemy& target, int damage)
{
    target.takeDamage(damage);
};

// Getters
/**
 * @brief Returns a matieral from either the spell inventory or weapon inventoory.
 * 
 * SPELLMAT |--| WEAPONMAT
 * 
 * @param matName Name of mateiral to find
 * @param invType Type of inventory to use
 * 
 * @return A crafing material for a spell or a weapon
 */
// CraftingMaterial Player::getMaterial(string matName, string invType)
// {
//     CraftingMaterial matReturn;

//     if(invType == "SPELLMAT")
//     {
//         for(size_t i = 0; i < spellMatInventory.size(); i++)
//         {
//             if(spellMatInventory.at(i).getName() == matName)
//             {
//                 matReturn = spellMatInventory.at(i);
//             }
//         }
//     }

//     else if(invType == "WEAPONMAT")
//     {
//         for(size_t i = 0; i < weaponMatInventory.size(); i++)
//         {
//             if(weaponMatInventory.at(i).getName() == matName)
//             {
//                 matReturn = weaponMatInventory.at(i);
//             }
//         }
//     }

//     return matReturn;
// };

// Spells Player::getSpell(string name)
// {
//     Spells spell;

//     if(!spellBook.empty())
//     {
//         for (size_t i = 0; i < spellBook.size(); i++)
//         {
//             if(spellBook[i].getName() == name)
//             {
//                 spell = spellBook[i];
//             }
//         }
//     }

//     else
//     {
//         cout << color.RED << "\n!SPELL BOOK IS EMPTY!\n" << color.DEFAULT;
//     }

//     return spell;
// }

// Setters
/**
 * @brief Sets the player's health points.
 * @param newHp New health points value
 */
void Player::setHealth(int newHp)
{
    healthPoints += newHp;

    if(healthPoints > maxHealthPoints)
    {
        healthPoints = maxHealthPoints;
    }
};

/**
 * @brief Sets the player's mana points.
 * @param newMana New mana points value
 */
void Player::setMana(int newMana)
{
    mana += newMana;
    if(mana > maxMana)
    {
        mana = maxMana;
    }
};


// void Player::setCombatBook(int index, Spells newSpell)
// {
//     combatBook.at(index) = newSpell;
// };

// void Player::addSpell(Spells newSpell)
// {
//     bool spellExists = false;

//     if(!spellBook.empty())
//     {
//         for(size_t i = 0; i < spellBook.size(); i++)
//         {
//             if(spellBook.at(i).getName() == newSpell.getName())
//             {
//                 spellExists = true;
//             }
//         }

//         if(!spellExists)
//         {
//             spellBook.push_back(newSpell);
//         }
//     }

//     else
//     {
//         spellBook.push_back(newSpell);
//     }
// };

// void Player::addToInventory(CraftingMaterial material, int amount, string type)
// {
//     bool foundItem = false;
//     int index = 0;

//     if(type == "SPELL")
//     {   
//         if(spellMatInventory.size() == 0)
//         {
//             spellMatInventory.at(index).setInventoryAmount(amount);
//         }

//         else
//         {
//             for(size_t i = 0; i < spellMatInventory.size(); i++)
//             {
//                 if(spellMatInventory.at(i).getName() == material.getName() && !foundItem)
//                 {
//                     foundItem = true;
//                     index = i;
//                 }
//             }

//             if(foundItem)
//             {
//                 spellMatInventory.at(index).setInventoryAmount(amount);
//             }

//             else 
//             {
//                 spellMatInventory.push_back(material);
//             }
//         }
        
//     }

//     else if(type == "WEAPON")
//     {
        
//         if(weaponMatInventory.size() == 0)
//         {
//             weaponMatInventory.at(index).setInventoryAmount(amount);
//         }

//         else
//         {
//             for(size_t i = 0; i < weaponMatInventory.size(); i++)
//             {
//                 if(weaponMatInventory.at(i).getName() == material.getName() && !foundItem)
//                 {
//                     foundItem = true;
//                     index = i;
//                 }
//             }

//             if(foundItem)
//             {
//                 weaponMatInventory.at(index).setInventoryAmount(amount);
//             }

//             else 
//             {
//                 weaponMatInventory.push_back(material);
//             }
//         }
//     }
// };