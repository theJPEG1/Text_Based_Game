#include "Player.H"
#include "Enemy.H"
#include "attacksEffects.H"

/**
 * @brief constructs the Effects action map
 */
Effects::Effects()
{
    actionMap["-"] = [this](Enemy& e, Player& p){ damage(e, p); };
    actionMap["<-"] = [this](Enemy& e, Player& p){ damageSelf(e, p); };
    actionMap["+"] = [this](Enemy& e, Player& p){ healing(e, p); };
    actionMap["#"] = [this](Enemy& e, Player& p){ freeze(e, p); };
    actionMap["&"] = [this](Enemy& e, Player& p){ bind(e, p); };
    actionMap["->"] = [this](Enemy& e, Player& p){ effectCounter(e, p); };
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
    actionMap["-"]  = [this](Enemy& e, Player& p){ damage(e, p); };
    actionMap["<-"] = [this](Enemy& e, Player& p){ damageSelf(e, p); };
    actionMap["+"]  = [this](Enemy& e, Player& p){ healing(e, p); };
    actionMap["#"]  = [this](Enemy& e, Player& p){ freeze(e, p); };
    actionMap["&"]  = [this](Enemy& e, Player& p){ bind(e, p); };
    actionMap["->"] = [this](Enemy& e, Player& p){ effectCounter(e, p); };
}


/**
 * @brief Uses the action map to determine what effect to apply
 * 
 * @param target Enemy to apply effect agains
 * @param p Player to grab stats and also target
 */
void Effects::handleEffects(Enemy& target, Player& p)
{
    actionMap.find(this->id)->second(target, p);
};

/**
 * @brief Uses the effect base damage and player strength/mind to calculate damage
 * 
 * @param target Enemy to target
 * @param p Player to reference
 */
void Effects::damage(Enemy& target, Player& p)
{
    cout << damageToDo << " | " << baseDmg << "\n";
    this->damageToDo = this->baseDmg;
    cout << damageToDo << "\n";

    if((rand() % 100) - p.getLuck() < critChance)
    {
        cout << "\nCRIT\n";
        damageToDo *= 2;
        cout << damageToDo << "\n";
    }

    if(effectType == "magical")
    {
        if(p.getMind() >= 10)
        {
            damageToDo *= (static_cast<double>(p.getMind()) / 10.0);
            cout << damageToDo << "\n";
        }

        if(target.getMagiRes() > 0)
        {
            damageToDo *= target.getMagiRes();
            cout << damageToDo << "\n";
        }
    } 

    else if(effectType == "physical")
    {
        if(p.getStrength() >= 10)
        {
            damageToDo *= (static_cast<double>(p.getStrength()) / 10.0);
            cout << damageToDo << "\n";
        }

        if(target.getPhysRes() > 0)
        {
            damageToDo *= target.getPhysRes();
            cout << damageToDo << "\n";
        }
    }

    cout <<"\nYou hit " << target.getName() << target.getType() << " for "  << damageToDo << " Damage\n";
    p.dealDamage(target, damageToDo);
};

/**
 * @brief Uses the effect base damage and player strength/mind to calculate damage
 * 
 * @param target does nothing here
 * @param p Player to target
 */
void Effects::damageSelf(Enemy& target, Player& p)
{
    target.takeDamage(0); //avoids warning message

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
            damageToDo *= static_cast<double>(p.getMind() / 10);
        }
    } 

    else if(effectType == "physical")
    {
        if(p.getStrength() >= 10)
        {
            damageToDo *= static_cast<double>(p.getStrength() / 10);
        }
    }

    cout <<"\nYou hit yourself for "  << (damageToDo / 2) << " Damage\n";
    p.takeDamage(damageToDo / 2);
};

/**
 * @brief Uses the effect base healing and player strength/mind to calculate healing
 * 
 * @param target does nothing here
 * @param p Player to reference
 */
void Effects::healing(Enemy& target, Player& p)
{
    target.takeDamage(0); // avoids warning message

    damageToDo = healingAmt;

    if(effectType == "magical")
    {
        if(p.getMind() >= 10)
        {
            damageToDo *= static_cast<double>(p.getMind() / 10);
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
            damageToDo *= static_cast<double>(p.getStrength() / 10);
        }

        if(target.getPhysRes() > 0)
        {
            damageToDo *= target.getPhysRes();
        }
    }

    cout << "\nYou healed for " << damageToDo << " Health!\n";
    p.increaseHealth(damageToDo);
};


/**
 * @brief Uses the effect freeze chance to freeze an enemy
 * 
 * @param target Enemy to target
 * @param p Does nothing here
 */
void Effects::freeze(Enemy& target, Player& p)
{
    p.takeDamage(0); // avoid warning message

    if((rand() % 100) - p.getLuck() < freezeChance)
    {
        cout << "\nFrozen!\n";
        target.setBind(true);
    }

    else {cout << "\nNo Freeze\n";}
};

/**
 * @brief Uses the effect bind chance to bind an enemy
 * 
 * @param target Enemy to target
 * @param p Does nothing here
 */
void Effects::bind(Enemy& target, Player& p)
{
    p.takeDamage(0); // avoid wanring message

    if((rand() % 100) - p.getLuck() < bindChance)
    {
        cout << "\nBound!\n";
        target.setBind(true);
    }

    else {cout << "\nNo Bind\n";}
};

/**
 * @brief Uses the effect counter to counter the next attack
 * 
 * @param target Enemy to target
 * @param p Does nothing here
 */
void Effects::effectCounter(Enemy& target, Player& p)
{
    p.takeDamage(0); // avoids warning message
    
    cout << "\nYour next attack will be countered!\n";
    target.setCounter(true);
};
