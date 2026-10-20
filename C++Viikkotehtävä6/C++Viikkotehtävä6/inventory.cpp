#include "inventory.h"
#include "input.h"
#include <iostream>

void Character::addItem(const Item& item)
{
    inventory.push_back(item);
    std::cout << "Received: " << item.name << "\n";
}

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

void giveWeapon(Character& player, const std::vector<Item>& weapons)
{
    std::cout << "\nChoose a weapon to receive:\n";

    for (std::size_t i = 0; i < weapons.size(); ++i)
    {
        std::cout << i + 1 << ". " << weapons[i].name
                  << " (Damage: " << weapons[i].damage
                  << ", Range: " << weapons[i].range << ")\n";
    }

    std::cout << "0. Cancel\n";
    const int choice = getNumber("Choice: ");

    if (choice == 0)
    {
        return;
    }

    if (choice < 1 || choice > static_cast<int>(weapons.size()))
    {
        std::cout << "That is not a valid weapon number.\n";
        return;
    }

    player.addItem(weapons[choice - 1]);
}