#include "Player.h"
#include "Enemy.h"
#include "attacksEffects.h"

PrettyColors color;

/**
 * @brief constructs the Effects action map
 */
Effects::Effects()
{
    rebuildActionMap();
};

/**
 * @brief Copy constructor for Effects and rebuilds map
 * 
 * @param other The Effect to copy
 */
Effects::Effects(const Effects& other)
{
    id = other.id;
    name = other.name;
    effectType = other.effectType;
    baseDmg = other.baseDmg;
    dexModi = other.dexModi;
    bindChance = other.bindChance;
    critChance = other.critChance;
    healingAmt = other.healingAmt;
    shield = other.shield;
    multCast = other.multCast;
    freezeChance = other.freezeChance;
    splatterAmount = other.splatterAmount;
    counter = other.counter;
    pushBack = other.pushBack;
    selfDamage = other.selfDamage;
    damageToDo = other.damageToDo;

    // Rebuild actionMap so lambdas capture the *new* this
    rebuildActionMap();
}

void Effects::rebuildActionMap()
{
    actionMap.clear();     // ensure we start clean

    actionMap["-"]  = [this](Enemy& e, Player& p, string turn){ damage(e, p, turn); };
    actionMap["<-"] = [this](Enemy& e, Player& p, string turn){ damageSelf(e, p, turn); };
    actionMap["+"]  = [this](Enemy& e, Player& p, string turn){ healing(e, p, turn); };
    actionMap["@"]  = [this](Enemy& e, Player& p, string turn){ freeze(e, p, turn); };
    actionMap["&"]  = [this](Enemy& e, Player& p, string turn){ bind(e, p, turn); };
    actionMap["->"] = [this](Enemy& e, Player& p, string turn){ effectCounter(e, p, turn); };
}



/**
 * @brief Uses the action map to determine what effect to apply
 * 
 * @param target Enemy to apply effect agains
 * @param p Player to grab stats and also target
 */
void Effects::handleEffects(Enemy& target, Player& p, string turn)
{
    if(actionMap.find(this->id) == actionMap.end())
    {
        cout << "ID NOT EXIST\n";
    }

    else
    {
        actionMap.find(this->id)->second(target, p, turn);
    }
};

/**
 * @brief Uses the effect base damage and player strength/mind to calculate damage
 * 
 * @param target Enemy to target
 * @param p Player to reference
 */
void Effects::damage(Enemy& target, Player& p, string turn)
{
    this->damageToDo = this->baseDmg;

    if(turn == "PLAYER")
    {
        if((rand() % 100) - p.getLuck() < critChance)
        {
            cout << color.YELLOW << "\nCRIT\n" << color.DEFAULT;
            damageToDo *= 2;
        }

        if(effectType == "magical")
        {
            if(p.getMind() >= 10)
            {
                damageToDo *= (static_cast<double>(p.getMind()) / 10.0);
            }

            if(target.getMagiRes() > 0)
            {
                damageToDo -= target.getMagiRes() * damageToDo;
            }
        } 

        else if(effectType == "physical")
        {
            if(p.getStrength() >= 10)
            {
                damageToDo *= (static_cast<double>(p.getStrength()) / 10.0);
            }

            if(target.getPhysRes() > 0)
            {
                damageToDo -= target.getPhysRes() * damageToDo;
            }
        }

        cout <<"\nYou hit " << target.getName() << target.getType() << " for "  
             << color.RED << static_cast<int>(damageToDo) << " Damage\n" << color.DEFAULT;

        p.dealDamage(target, static_cast<int>(damageToDo));
    }

    else
    {
        if((rand() % 100) < critChance)
        {
            cout << "\nCRIT\n";
            damageToDo *= 2;
        }

        
        if(baseDmg >= 5)
        {
            damageToDo *= static_cast<double>(target.getStrength() / 10.0);
        }

        cout <<"\nYou were hit for " << color.RED 
             << static_cast<int>(damageToDo) << " Damage\n" << color.DEFAULT;

        p.takeDamage(static_cast<int>(damageToDo));
    }
    
};

/**
 * @brief Uses the effect base damage and player strength/mind to calculate damage
 * 
 * @param target does nothing here
 * @param p Player to target
 */
void Effects::damageSelf(Enemy& target, Player& p, string turn)
{
    if(turn == "PLAYER")
    {
        damageToDo = baseDmg;

        if((rand() % 100) + p.getLuck() < critChance)
        {
            cout << "\nCRIT\n";
            damageToDo *= 2;
        }

        if(effectType == "magical")
        {
            if(p.getMind() >= 10)
            {
                damageToDo *= static_cast<double>(p.getMind() / 10.0);
            }
        } 

        else if(effectType == "physical")
        {
            if(p.getStrength() >= 10)
            {
                damageToDo *= static_cast<double>(p.getStrength() / 10.0);
            }
        }

        cout <<"\nYou hit yourself for " << color.RED 
             << static_cast<int>(damageToDo / 2) << " Damage\n" << color.DEFAULT;
        p.takeDamage(static_cast<int>(damageToDo / 2.0));
    }

    else
    {
        damageToDo = baseDmg;

        if((rand() % 100) < critChance)
        {
            cout << "\nCRIT\n";
            damageToDo *= 2;
        }

        
        if(baseDmg >= 5)
        {
            damageToDo *= static_cast<double>(target.getStrength() / 10.0);
        }
        

        cout <<"\n" << target.getType() << " hit itself for " << color.RED 
             << static_cast<int>(damageToDo / 2.0) << " Damage\n" << color.DEFAULT;
        target.takeDamage(static_cast<int>(damageToDo / 2.0));
    }

    
};

/**
 * @brief Uses the effect base healing and player strength/mind to calculate healing
 * 
 * @param target does nothing here
 * @param p Player to reference
 */
void Effects::healing(Enemy& target, Player& p, string turn)
{
    if(turn == "PLAYER")
    {
        damageToDo = healingAmt;

        if(effectType == "magical")
        {
            if(p.getMind() >= 10)
            {
                damageToDo *= static_cast<double>(p.getMind() / 10.0);
            }

            if(target.getMagiRes() > 0)
            {
                damageToDo *= target.getMagiRes();
            }
        } 

        else if(effectType == "physical")
        {
            if(p.getStrength() >= 10)
            {
                damageToDo *= static_cast<double>(p.getStrength() / 10.0);
            }

            if(target.getPhysRes() > 0)
            {
                damageToDo *= target.getPhysRes();
            }
        }

        cout << "\nYou healed for " << color.CYAN
             << static_cast<int>(damageToDo) << " Health!\n" << color.DEFAULT;
        p.increaseHealth(static_cast<int>(damageToDo));
    }

    else
    {
        damageToDo = healingAmt;

        if(baseDmg >= 5)
        {
            damageToDo *= static_cast<double>(target.getStrength() / 10.0);
        }

        cout <<"\n" << target.getType() << " healed itself for " << color.CYAN
             << static_cast<int>(damageToDo) << " Health!\n" << color.DEFAULT;
        target.takeDamage(-static_cast<int>(damageToDo));
    }
};


/**
 * @brief Uses the effect freeze chance to freeze an enemy
 * 
 * @param target Enemy to target
 * @param p Does nothing here
 */
void Effects::freeze(Enemy& target, Player& p, string turn)
{
    if(turn == "PLAYER")
    {
        if((rand() % 100) - p.getLuck() < freezeChance)
        {
            cout << color.BLUE << "\nFrozen!\n" << color.DEFAULT;
            target.setBind(true);
        }

        else 
        {
            cout << color.BLUE << "\nNo Freeze\n" 
                 << color.DEFAULT;
        }
    }
    
};

/**
 * @brief Uses the effect bind chance to bind an enemy
 * 
 * @param target Enemy to target
 * @param p Does nothing here
 */
void Effects::bind(Enemy& target, Player& p, string turn)
{
    if(turn == "PLAYER")
    {
        if((rand() % 100) - p.getLuck() < bindChance)
        {
            cout << color.GREEN << "\nBound!\n" << color.DEFAULT;
            target.setBind(true);
        }

        else 
        {
            cout << color.GREEN << "\nNo Bind\n" 
                 << color.DEFAULT;
        }
    }
};

/**
 * @brief Uses the effect counter to counter the next attack
 * 
 * @param target Enemy to target
 * @param p Does nothing here
 */
void Effects::effectCounter(Enemy& target, Player& p, string turn)
{
    p.takeDamage(0); // avoids warning

    if(turn == "PLAYER")
    {
        cout << "\nThe next attack will be countered!\n";
        target.setCounter(true);
    }
    
    
};

