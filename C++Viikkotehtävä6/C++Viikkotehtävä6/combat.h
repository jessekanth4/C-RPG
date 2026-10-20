#pragma once

#include <cstddef>
#include <string>

#include "character.h"

// Stores an enemy and the location it guards.
struct Enemy
{
    std::string name;
    std::size_t area;
    int damage;
    int health;
    int maxHealth;
    bool defeated;
};

enum class CombatResult
{
    Victory,
    Escaped,
    PlayerDied
};

const int playerMaxHealth = 30;

// Starts a fight and returns how it ended.
CombatResult fightEnemy(Character& player, Enemy& enemy, int& playerHealth);
