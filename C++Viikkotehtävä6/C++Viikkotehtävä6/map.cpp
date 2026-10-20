#include "map.h"
#include "combat.h"
#include "character.h"
#include "input.h"
#include <iostream>

// Home = 0
// Forest path = 1
// Grassland path = 2
// Cliffs = 3
// Forest edge = 4
// Junction = 5
// Deep forest = 6
// Town = 7
// Shore = 8

// Each area lists the other areas that can be reached from it.
const std::vector<Area> worldMap =
{
    {"Home", {1, 2, 3}},
    {"Forest path", {0, 4}},
    {"Grassland path", {0, 5}},
    {"Cliffs", {0}},
    {"Forest edge", {1, 6, 8}},
    {"Junction", {2, 7, 8}},
    {"Deep forest", {4}},
    {"Town", {5}},
    {"Shore", {4, 5}}
};

void mapMenu(std::size_t& currentArea, Character& player, std::vector<Enemy>& enemies, int& playerHealth)
{
    bool mapOpen = true;

    while (mapOpen)
    {
        const Area& area = worldMap[currentArea];

        std::cout << "\n=== Map ===\n"
                  << "Current location: " << area.name << "\n"
                  << "Where would you like to go?\n";

        // Show only destinations connected to the current location.
        for (std::size_t i = 0; i < area.connections.size(); ++i)
        {
            const int destination = area.connections[i];
            std::cout << i + 1 << ". " << worldMap[destination].name << "\n";
        }

        std::cout << "0. Return to main menu\n";
        const int choice = getNumber("Choice: ");

        if (choice == 0)
        {
            mapOpen = false;
        }
        else if (choice < 1 || choice > static_cast<int>(area.connections.size()))
        {
            std::cout << "That is not a valid destination.\n";
        }
        else
        {
            const std::size_t destination = static_cast<std::size_t>(area.connections[choice - 1]);
            Enemy* guardingEnemy = nullptr;

            // Check whether an undefeated enemy guards the destination.
            for (Enemy& enemy : enemies)
            {
                if (enemy.area == destination && !enemy.defeated)
                {
                    guardingEnemy = &enemy;
                    break;
                }
            }

            // The player must defeat the enemy before entering its area.
            if (guardingEnemy != nullptr)
            {
                const CombatResult result = fightEnemy(player, *guardingEnemy, playerHealth);

                if (result == CombatResult::Victory)
                {
                    currentArea = destination;
                    std::cout << "You can now enter " << worldMap[currentArea].name << ".\n";
                }
                else if (result == CombatResult::PlayerDied)
                {
                    currentArea = 0;
                    std::cout << "You are back at Home.\n";
                }
                // If the player escaped, the current location does not change.
            }
            else
            {
                currentArea = destination;
                std::cout << "Travelled to " << worldMap[currentArea].name << ".\n";
            }
        }
    }
}