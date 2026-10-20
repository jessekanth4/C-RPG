#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "character.h"

struct Area {
    std::string name;
    std::vector<int> connections;
};

struct Enemy
{
    std::string name;
    std::size_t area;
    int baseAttack;
    int health;
    int maxHealth;
    bool defeated;
};

extern const std::vector<Area> worldMap;

void mapMenu(std::size_t& currentArea, Character& player, std::vector<Enemy>& enemies, int& playerHealth);
