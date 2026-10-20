#pragma once

#include <cstddef>
#include <vector>

#include "character.h"

// Connects a weapon to a map location. Each weapon can only be picked up once.
struct WorldWeapon
{
    std::size_t area;
    Item item;
    bool available;
};

// These functions show or collect the weapon at the player's current location.
void displayWeaponAtLocation(const std::vector<WorldWeapon>& worldWeapons, std::size_t currentArea);
void takeWeaponAtLocation(Character& player, std::vector<WorldWeapon>& worldWeapons, std::size_t currentArea);
