#include "inventory.h"
#include "input.h"
#include <iostream>

//Add a weapon to the character's inventory. (Debug, not used in final game)
void Character::addItem(const Item& item)
{
    inventory.push_back(item);
    std::cout << "Received: " << item.name << "\n";
}

//List all weapons the player has collected, including their stats.
void Character::displayInventory() const
{
    std::cout << "\nInventory:\n";

    if (inventory.empty())
    {
        std::cout << "Your inventory is empty.\n";
        return;
    }

    for (std::size_t i = 0; i < inventory.size(); ++i)
    {
        const Item& item = inventory[i];
        std::cout << i + 1 << ". " << item.name
                  << " | Damage: " << item.damage
                  << " | Range: " << item.range << "\n";
    }
}

//Show the weapon at the current location if it has not already been taken.
void displayWeaponAtLocation(const std::vector<WorldWeapon>& worldWeapons, std::size_t currentArea)
{
    for (const WorldWeapon& weapon : worldWeapons)
    {
        if (weapon.area == currentArea && weapon.available)
        {
            std::cout << "\nWeapon here: " << weapon.item.name
                      << " (Damage: " << weapon.item.damage
                      << ", Range: " << weapon.item.range << ")\n";
            return;
        }
    }
}

//Give the weapon to the player and mark it as "taken" so it cannot be collected again.
void takeWeaponAtLocation(Character& player, std::vector<WorldWeapon>& worldWeapons, std::size_t currentArea)
{
    for (WorldWeapon& weapon : worldWeapons)
    {
        if (weapon.area == currentArea && weapon.available)
        {
            player.addItem(weapon.item);
            weapon.available = false;
            return;
        }
    }

    std::cout << "There is no weapon here to take.\n";
}
