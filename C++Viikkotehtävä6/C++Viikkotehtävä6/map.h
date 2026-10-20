#pragma once

#include <cstddef>
#include <vector>

#include "combat.h"

// The map handles travel and checks whether an enemy guards the destination.
void mapMenu(std::size_t& currentArea, Character& player, std::vector<Enemy>& enemies, int& playerHealth);
