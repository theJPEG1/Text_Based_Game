#include "Player.H"



/**
 * @brief Constructs a Player object.
 * @param name Name of the Player
 * @param monthBorn The month the player was born
 * @param timeBorn Time player was born
 * @param dayBorn The day th eplayer was born
 * @param hp Health Points
 * @param str Strength Stat
 * @param dex Dexterity Stats
 * @param mind Mind Stat
 * @param luck Luck Stat
 */
Player::Player(string name, string monthBorn, string timeBorn, int dayBorn, 
               int hp, int str, int dex, int mind)
    {
        //Player info
            playerName = name;
            month = monthBorn;
            day = dayBorn;
            time = timeBorn;

        //player stats
            healthPoints = hp;
            maxHealthPoints = healthPoints;
            dexterityStat = dex;
            strengthStat = str;
            mindStat = mind;
            mana = mind * 5;
            maxMana = mana;
            luck = 1;

        //player level
            this->xpToNextLevel = 50;
            level = 1;
            currentXp = 0;

        //player inventory
            healthPotionCount = 3;
            manaPotionCount = 3;
    };

/**
 * @brief Constructs a Player object from a file.
 * @param name Name of the Player
 * @param monthBorn The month the player was born
 * @param dayBorn The day th eplayer was born
 * @param timeBorn Time player was born
 * @param hp Health Points
 * @param str Strength Stat
 * @param dex Dexterity Stats
 * @param mind Mind Stat
 * @param luck Luck Stat
 * @param playerLevel The level the player is at
 * @param curExp Amount of exp player has
 * @param xpToLevel How much xp until the next level
 */    
Player::Player(string name, string monthBorn, int dayBorn, string timeBorn, 
               int hp, int maxHp, int str, int dex, int mind, int luck,
               int playerLevel, int curExp, int xpToLevel)
       {
        //Player info
            playerName = name;
            month = monthBorn;
            day = dayBorn;
            time = timeBorn;
        //player stats
            healthPoints = hp;
            maxHealthPoints = maxHp;
            dexterityStat = dex;
            strengthStat = str;
            mindStat = mind;
            mana = mind * 5;
            maxMana = mana;
            this->luck = luck;

        //player level
            this->xpToNextLevel = xpToLevel;
            level = playerLevel;
            currentXp = curExp;

        //player inventory
            healthPotionCount = 3;
            manaPotionCount = 3;
    };        

void Player::printGuildCard()
{
    cout << colors.YELLOW << playerName <<"\n   Born on " << month << " " << day << ", during the " << time <<"\n"
         << colors.DEFAULT
         << colors.CYAN << "Health: " << healthPoints << "/" << maxHealthPoints << "\n"
         << colors.RED << "Stregnth: " << strengthStat << "\n"
         << colors.GREEN << "Dexterity: " << dexterityStat << "\n"
         << colors.MAGENTA << "Mind: " << mindStat << "\n"
         << "   Mana: " << mana << "/" << maxMana << "\n"
         << colors.YELLOW << "Level: " << level << "\n"
         << "   XP: " << currentXp << "/" << xpToNextLevel << colors.DEFAULT << "\n";
};

/**
 * @brief Levels up the player, increases stats, and allows stat allocation.
 */
void Player::levelUp()
{
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

    colors.pauseTerminal(5);
    colors.clearScreen();
};

/**
    @brief Returns a random spell attack from your list of spells
**/
Attacks Player::getRandAttack()
{
    int spellIndex = rand() % spellList.size();

    return spellList.at(spellIndex);
};

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

// Setters
/**
 * @brief + or - to player health.
 * @param newHp points to + or - towards hp
 */
void Player::increaseHealth(int newHp)
{
    healthPoints += newHp;

    if(healthPoints > maxHealthPoints)
    {
        healthPoints = maxHealthPoints;
    }
};

/**
 * @brief + or - to player mana.
 * @param newMana points to + or - towards mana
 **/
void Player::increaseMana(int newMana)
{
    mana += newMana;
    if(mana > maxMana)
    {
        mana = maxMana;
    }
};


/**
 * @brief + or - to player mind and recalculates mana
 * @param newMana points to + or - towards mind
 **/
void Player::increaseMind(int amt)
{
    mindStat += amt;
    mana = mindStat * 5;
    maxMana = mana;
}

/**
 * @brief Adds a material to the players inventory
 * 
 * @param material Material to look
 * @param amount How many to increase by
 */
void Player::addToInventory(CraftingMaterials material, int amount)
{
    inventory[material] += amount;
};

/**
 * @brief Prints threw your inventory based off rarity
 * 
 * @param rarity max rarity to print
 */
void Player::printInventory(int rarity)
{
    int count = 0;
    for (const auto& [material, amount] : inventory) 
    {
        if(material.rarity <= rarity)
        {
            if (amount > 0) 
            {
                cout << material.name;

                for (size_t i = 0; i < material.matEffects.size(); i++)
                {
                    if(i == 0)
                    {
                        cout << " (";
                    }

                    if(i == material.matEffects.size())
                    {
                        cout << material.matEffects.at(i).id;    
                    }

                    else 
                    {
                        cout << material.matEffects.at(i).id << " ";
                    }
                    
                    
                }

                cout << ") : " << amount << "   ";

                
                
                if(material.name.length() <= 35)
                {
                    cout << "\t";
                }

                if(material.name.length() <= 20)
                {
                    cout << "\t";
                }

                if(material.name.length() <= 10)
                {
                    cout << "\t";
                }
                

                count++;

                if (count % 3 == 0) 
                {
                    std::cout << "\n";
                }
            }
        }
    }
};