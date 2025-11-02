#include "PrettyColors.H"
#include "Enemy.H"
#include "Player.H"

/**
 * @brief Constructs an Enemy object with specified stats and attributes.
 * @param thisRegion Region where the enemy is found.
 * @param thisName Enemy's name.
 * @param enemyType Type/category of the enemy.
 * @param health Initial health points.
 * @param strength Strength stat.
 * @param dexterity Dexterity stat.
 * @param minExp Minimum XP awarded on defeat.
 * @param maxExp Maximum XP awarded on defeat.
 */
Enemy::Enemy(string thisRegion, string thisName, string enemyType, 
             double phyRes, double magRes, bool isBoss, 
             int health, int strength, int dexterity, 
             int minExp, int maxExp, int level,
             int dropChn, int minNov, int maxNov)
{
    region = thisRegion;
    name = thisName;
    type = enemyType;
    hp = health;
    maxHp = hp;
    this->strength = strength;
    this->dexterity = dexterity;

    magiRes = magRes;
    physiRes = phyRes;

    dropChance = dropChn;
    minNovas = minNov;
    maxNovas = maxNov;

    this->minExp = minExp;
    this->maxExp = maxExp;
    this->level = level;
};


/**
 * @brief Reduces enemy's health by the given damage amount.
 * @param damage Amount of damage to take.
 */
void Enemy::takeDamage(int damage)
{
    if(hp - damage > maxHp)
    {
        hp = maxHp;
    }

    else
    {
        hp -= damage;
    }
    
};

/**
 * @brief Deals damage to a player target.
 * @param target Reference to the player.
 * @param damage Amount of damage to deal.
 */
void Enemy::dealDamage(Player& target, int damage)
{
    target.takeDamage(damage);
};

void Enemy::debuffs()
{
    if(DOT)
    {
        hp -= 2;
    }

    
    if(weakened)
    {
        strength -= 2;
    }
}

/**
 * @brief Displays the enemy's stats and attributes in the terminal.
 */
void Enemy::displaySelf()
{
    PrettyColors color;
    cout << color.YELLOW << "Region: " << region << "\n" << "Name: " << name << "\n"
         << "Type: " << type << "\n" 
         << color.CYAN << "Health: " << hp << "/" << maxHp << "\n"
         << color.RED << "Damage: " << "1-" << strength << "\n"
         << color.GREEN << "Dexterity: " << dexterity << "\n" << color.DEFAULT;
};

/**
 * @brief Gets the enemy's current health points.
 * @return Current health points.
 */
int Enemy::getHp()
{
    return hp;
};

/**
 * @brief Gets the enemy's maximum health points.
 * @return Maximum health points.
 */
int Enemy::getMaxHp()
{
    return maxHp;
};

/**
 * @brief Gets the enemy's name.
 * @return Enemy's name.
 */
string Enemy::getName()
{
    return name;
};

/**
 * @brief Gets the region where the enemy is found.
 * @return Enemy's region.
 */
string Enemy::getRegion()
{
    return region;
}

/**
 * @brief Gets the enemy's type/category.
 * @return Enemy's type.
 */
string Enemy::getType()
{
    return type;
};

/**
 * @brief Gets the enemy's dexterity stat.
 * @return Dexterity stat.
 */
int Enemy::getDexterity()
{
    return dexterity;
};

/**
 * @brief Gets the enemy's strength stat.
 * @return Strength stat.
 */
int Enemy::getStrength()
{
    return strength;
};

/**
 * @brief Gets the minimum XP awarded for defeating the enemy.
 * @return Minimum XP value.
 */
int Enemy::getMinExp()
{
    return minExp;
};

/**
 * @brief Gets the maximum XP awarded for defeating the enemy.
 * @return Maximum XP value.
 */
int Enemy::getMaxExp()
{
    return maxExp;
};

Attacks Enemy::getAtk()
{
    return attacks.at(rand() % attacks.size());
}

//setters
/**
 * @brief Sets the enemy's name.
 * @param newName New name for the enemy.
 */
void Enemy::setName(string newName)
{
    name = newName;
};