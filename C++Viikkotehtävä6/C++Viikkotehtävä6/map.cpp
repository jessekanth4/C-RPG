#include "map.h"
#include "input.h"
#include <iostream>
#include <random>

//Home = 0
//Forest path = 1
//Grassland path = 2
//Cliffs = 3
//Forest edge = 4
//Junction = 5
//Deep forest = 6
//Town = 7
//Shore = 8
//Each area has numbers corresponding to the areas it connects to
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

        // Display only destinations connected to the current location.
        for (std::size_t i = 0; i < area.connections.size(); ++i)
        {
            const int destination = area.connections[i];
            std::cout << i + 1 << ". " << worldMap[destination].name << "\n";
        }

        std::cout << "0. Return to main menu\n";
        const int choice = getNumber("Choice: ");

        // Handle leaving the map, invalid choices, or moving to a connected area.
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

            for (Enemy& enemy : enemies)
            {
                if (enemy.area == destination && !enemy.defeated)
                {
                    guardingEnemy = &enemy;
                    break;
                }
            }

            if (guardingEnemy == nullptr)
            {
                currentArea = destination;
                std::cout << "Travelled to " << worldMap[currentArea].name << ".\n";
                continue;
            }

            std::cout << "\nA " << guardingEnemy->name << " blocks the way!\n";
            bool combatFinished = false;

            while (!combatFinished)
            {
                std::cout << "\nYour health: " << playerHealth << "/30\n"
                          << guardingEnemy->name << " health: " << guardingEnemy->health
                          << "/" << guardingEnemy->maxHealth << "\n"
                          << "1. Fight\n"
                          << "2. Run\n";

                const int combatChoice = getNumber("Choice: ");

                if (combatChoice == 2)
                {
                    playerHealth = 30;
                    guardingEnemy->health = guardingEnemy->maxHealth;
                    std::cout << "You escaped. Both you and the enemy recovered.\n";
                    combatFinished = true;
                }
                else if (combatChoice != 1)
                {
                    std::cout << "Choose 1 to fight or 2 to run.\n";
                }
                else
                {
                    // Each side rolls 3-9; the roll is multiplied by weapon damage or base attack.
                    static std::random_device seed;
                    static std::mt19937 generator(seed());
                    static std::uniform_int_distribution<int> attackRoll(3, 9);

                    const int playerRoll = attackRoll(generator);
                    const int playerDamage = playerRoll * player.getStrongestWeaponDamage();
                    guardingEnemy->health -= playerDamage;

                    std::cout << "You rolled " << playerRoll << " and dealt "
                              << playerDamage << " damage.\n";

                    if (guardingEnemy->health <= 0)
                    {
                        guardingEnemy->health = 0;
                        guardingEnemy->defeated = true;
                        currentArea = destination;
                        std::cout << "You defeated the " << guardingEnemy->name
                                  << "! You can now enter " << worldMap[currentArea].name << ".\n";
                        combatFinished = true;
                    }
                    else
                    {
                        const int enemyRoll = attackRoll(generator);
                        const int enemyDamage = enemyRoll * guardingEnemy->baseAttack;
                        playerHealth -= enemyDamage;

                        std::cout << "The " << guardingEnemy->name << " rolled " << enemyRoll
                                  << " and dealt " << enemyDamage << " damage.\n";

                        if (playerHealth <= 0)
                        {
                            playerHealth = 30;
                            guardingEnemy->health = guardingEnemy->maxHealth;
                            currentArea = 0;
                            std::cout << "You were defeated and returned Home. Both you and the enemy recovered.\n";
                            combatFinished = true;
                        }
                    }
                }
            }
        }
    }
}