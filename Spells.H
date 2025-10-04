#ifndef SPELLS_H
#define SPELLS_H

#include <string>
    using std::string;
#include <vector>
    using std::vector;

#include "Enemy.H"
#include "CraftingMaterial.H"

class Spells
{
    public:
        Spells(string name = "?", int cost = 0, string description = "No Description");
        Spells(string name, int cost, string description, 
               bool hasBind , bool hasDot , bool hasUndoDot ,
               bool hasSiphon , bool hasWeakness , bool hasCounter ,
               bool hasShield , bool hasSplatter , bool hasMulticast );//custom spells

        static Spells craftedSpell(CraftingMaterial material1, CraftingMaterial material2, CraftingMaterial material3);

        void cast(Enemy& target, int playerMana, int& healed, vector<Spells> playerSpells);

        void displaySpell();

        //getters
            string getName() {return spellName;};
            int getManaCost() {return manaCost;};
            string getDescription() {return spellDescription;};

        //setters
            void setName(string newName);
            void setManaCost(int cost);
    private:
        string spellName;
        int manaCost;
        string spellDescription;

        //spells attributes
        bool bind, DOT, undoDOt, siphon, weak, counter, shield, splatter, multiCast;
    /*
        Spells in the Game:

        Damaging:
            "Fireball", 10, "A Ball of fire that does damage."
            "Ice Shard", 15, "A Shard of Ice that does damage."
            "Siphon", 20, "A spell that turns enemy hp into your own."
            "Mage's Last Stand", 0 "Wait.. These are just brass knuckles.."
            "Lightning Blast", 25, "A bolt of lightning that does damage to you and the enemy"
            "Vine Bind", 15, "A spell that does a small amount of damage and a chance to bind the enemy for a turn.""   
            "Counter", 30, "A spell that allows you to reverse the next enemy attack back on them."
            "Fire Splatter", 25, "A spell with high crit that does small damage to each enemy in the que."
            "Magic Punch", 10, "A punch imbued with magic that does damage."
        
        Buffing:
            "Knights Shield", 30, "A spell that Allows you to block the next two Enemy attacks."
        
        Debuffing:
            "Weakness", 20, "A spell that lowers the enemies strength for 3 turns."

        Special:
            "???", 60, "Casts two random spells from your spell book"
            "THE Last Stand", 0, "A blast of energy that leaves you with one hp and destroyes all enemies in the que." 
            "Push Back", 20, "Pushes the enemy back in the que by one spot."

        Crafted Spells Effects
            Bind
            DOT
            undo DOT
            Siphon
            Weakness
            Counter
            Shield
            Splatter 
            Multi cast
    */
};

#endif