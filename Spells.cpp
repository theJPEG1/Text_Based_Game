#include "Spells.H"
#include "Enemy.H"
#include <iostream>
    using std::cout;
    using std::cin;
#include <string>
    using std::string;
#include "PrettyColors.H"


Spells::Spells(string name, int cost, string description)
{
    spellName = name;
    manaCost = cost;
    spellDescription = description;
};

Spells::Spells(string name, int cost, string description, bool hasBind, bool hasDot, bool hasUndoDot, bool hasSiphon, bool hasWeakness, bool hasCounter, bool hasShield, bool hasSplatter, bool hasMulticast)
{
    spellName        = name;
    manaCost         = cost;
    spellDescription = description;

    bind             = hasBind;
    DOT              = hasDot;
    undoDOt          = hasUndoDot;
    siphon           = hasSiphon;
    weak             = hasWeakness;
    counter          = hasCounter;
    shield           = hasShield;
    splatter         = hasSplatter;
    multiCast        = hasMulticast;
};

void Spells::displaySpell()
{
    cout << spellName << ", Mana Cost: " << manaCost << ", " << spellDescription << "\n";
};

Spells Spells::craftedSpell(CraftingMaterial material1, CraftingMaterial material2, CraftingMaterial material3)
{
    bool bind = false, DOT = false, undoDOt = false, siphon = false, weak = false, counter = false, shield = false, splatter = false, multiCast = false;
    int cost = 10;

    string desc = "A spell that:";
    string mat1Effect = material1.getEffect();
    string mat2Effect = material2.getEffect();
    string mat3Effect = material3.getEffect();

    if(mat1Effect == "BIND" || mat2Effect == "BIND" || mat3Effect == "BIND")
    {
        bind = true;
        cost += 15;
        desc += " Binds";
    }

    if(mat1Effect == "DOT" || mat2Effect == "DOT" || mat3Effect == "DOT")
    {
        DOT = true;
        cost += 15;
        desc += " Damages over time";
    }

    if(mat1Effect == "UNDODOT" || mat2Effect == "UNDODOT" || mat3Effect == "UNDODOT")
    {
        undoDOt = true;
        cost += 15;
        desc += " Removes Ddmage over time";
    }

    if(mat1Effect == "SIPHON" || mat2Effect == "SIPHON" || mat3Effect == "SIPHON")
    {
        siphon = true;
        cost += 15;
        desc += " Siphons health";
    }

    if(mat1Effect == "WEAK" || mat2Effect == "WEAK" || mat3Effect == "WEAK")
    {
        weak = true;
        cost += 15;
        desc += " Weakens the enemy";
    }

    if(mat1Effect == "COUNTER" || mat2Effect == "COUNTER" || mat3Effect == "COUNTER")
    {
        counter = true;
        cost += 15;
        desc += " Counters attacks";
    }
    if(mat1Effect == "SHIELD" || mat2Effect == "SHIELD" || mat3Effect == "SHIELD")
    {
        shield = true;
        cost += 15;
        desc += " Shields you";
    }
    if(mat1Effect == "SPLATTER" || mat2Effect == "SPLATTER" || mat3Effect == "SPLATTER")
    {
        splatter = true;
        cost += 15;
        desc += " Splatters damage and effects to other enemies";
    }
    if(mat1Effect == "MULTICAST" || mat2Effect == "MULTICAST" || mat3Effect == "MULTICAST")
    {
        multiCast = true;
        cost += 15;
        desc += " Casts another spell at random";
    }

    desc += ".";

    Spells custom("Custom Spell", cost, desc, bind, DOT, undoDOt, siphon, weak, counter, shield, splatter, multiCast);

    return custom;
};

void Spells::cast(Enemy& target, int playerMind, int& healed, vector<Spells> playerSpells)
{
    PrettyColors color;

    if(spellName == "Fireball")
    {
        int damage = (rand() % playerMind + 1) + playerMind / 5;
        cout << color.MAGENTA << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage!\n" << color.DEFAULT;
        target.takeDamage(damage);
        target.setDOT(true);
    }

    else if(spellName == "Ice Shard")
    {
        int damage = (rand() % playerMind + 1) + playerMind / 7;
        cout << color.CYAN << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage!\n" << color.DEFAULT;
        target.takeDamage(damage);
        target.setDOT(false);
    }

    else if(spellName == "Siphon")
    {
        int damage = rand() % playerMind + 1;
        healed = damage;
        cout << color.GREEN << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage and heal for " << damage / 2 << " Health!\n" << color.DEFAULT;
        target.takeDamage(damage);
    }

    else if(spellName == "Lightning Bolt")
    {
        int damage = (rand() % playerMind + 1) + playerMind / 2;
        healed = -(damage / 4);
        cout << color.YELLOW << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage!\n"
             << color.RED << "You take " << damage / 2 << " Damage from the recoil!\n" << color.DEFAULT;
        target.takeDamage(damage);
    }

    else if(spellName == "Vine Bind")
    {
        int damage = rand() % playerMind + 1;
        cout << color.GREEN << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage!\n" << color.DEFAULT;
        int bindChance = rand() % 100 + 1;

        if(bindChance >= 50)
        {
            target.setBind(true);
            cout << color.GREEN << target.getName() << target.getType() << " is bound and cannot move next turn!\n" << color.DEFAULT;
        }
        else
        {
            cout << color.RED << target.getName() << target.getType() << " resisted the bind!\n" << color.DEFAULT;
        }

        target.takeDamage(damage);
    }

    else if(spellName == "Magic Punch")
    {
        int damage = (rand() % playerMind + 1) + playerMind / 10;
        cout << color.MAGENTA << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage!\n" << color.DEFAULT;
        target.takeDamage(damage);
    }

    else if(spellName == "Counter")
    {
        target.setCounter(true);
        cout << color.GREEN << target.getName() << target.getType() << " next attack will be countered!\n" << color.DEFAULT;
    }

    else if(spellName == "???")
    {
        int spell1 = rand() % playerSpells.size();
        int spell2 = rand() % playerSpells.size();

        playerSpells.at(spell1).cast(target, playerMind, healed, playerSpells);
        playerSpells.at(spell2).cast(target, playerMind, healed, playerSpells);
    }

    else if("Custom Spell")
    {
        int damage = rand() % playerMind + 1;

        cout << color.MAGENTA << "\nYou cast " << spellName << " on " << target.getName() << target.getType() << " for " << damage << " Damage!\n" << color.DEFAULT;

        if(bind)
        {
            int bindChance = rand() % 100 + 1;

            if(bindChance >= 50)
            {
                target.setBind(true);
                cout << color.GREEN << target.getName() << target.getType() << " is bound and cannot move next turn!\n" << color.DEFAULT;
            }
            else
            {
                cout << color.RED << target.getName() << target.getType() << " resisted the bind!\n" << color.DEFAULT;
            }
        }

        if(DOT)
        {

            target.setDOT(true);
        }

        if(undoDOt)
        {
            target.setDOT(false);
        }

        if(siphon)
        {
            healed = damage / 2;
            cout << "Stole " << damage / 2 << " Health! from " << color.DEFAULT << target.getName() << target.getType() <<  "\n";
        }

        if(weak)
        {
            target.setWeakened(true);
        }

        if(counter)
        {
            cout << color.GREEN << target.getName() << target.getType() << " next attack will be countered!\n" << color.DEFAULT;
            target.setCounter(true);
        }

        if(shield)
        {
            //not done yet
        }

        if(splatter)
        {
            //not done yet
        }

        if(multiCast)
        {
            int spell1 = rand() % playerSpells.size();

            playerSpells.at(spell1).cast(target, playerMind, healed, playerSpells);
        }

        target.takeDamage(damage);
    }   
};


void Spells::setName(string newName)
{
    spellName = newName;
};

void Spells::setManaCost(int cost)
{
    manaCost = cost;
};


