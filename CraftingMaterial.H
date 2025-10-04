#ifndef CRAFTINGMATERIAL_H
#define CRAFTINGMATERIAL_H

#include <string>
    using std::string;

class CraftingMaterial
{
    public:
        CraftingMaterial(string matName = "", string materialUse = "", int inventory = 0, int rarity= 0, int cost=0);//weapon crafting
        CraftingMaterial(string matName, string materialUse, int inventory, int rarity, int cost, string spellEffect);//spell crafting
    
    //getters
        string getName() {return name;};
        string getType() {return type;};
        int getInventoryAmount() {return inventoryAmount;};
        string getEffect() {return effect;};

    //setters
        void setInventoryAmount(int addMore) {inventoryAmount += addMore;};

    private:
        string name, type;
        int inventoryAmount, rarityValue, price;
        
        //spell specifics
        string effect;



};

#endif