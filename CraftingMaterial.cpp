#include "CraftingMaterial.H"
#include <string>
    using std::string;

CraftingMaterial::CraftingMaterial(string matName, string materialUse, int inventory, int rarity, int cost)
{
    name = matName;
    type = materialUse;
    inventoryAmount = inventory;
    rarityValue = rarity;
    price = cost;
};

CraftingMaterial::CraftingMaterial(string matName, string materialUse, int inventory, int rarity, int cost, string spellEffect)
{
    name = matName;
    type = materialUse;
    inventoryAmount = inventory;
    rarityValue = rarity;
    price = cost;
    effect = spellEffect;
};

