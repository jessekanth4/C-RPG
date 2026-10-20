#include "map.h"
#include "input.h"
#include <iostream>

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

void mapMenu(std::size_t& currentArea)
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
            currentArea = static_cast<std::size_t>(area.connections[choice - 1]);
            std::cout << "Travelled to " << worldMap[currentArea].name << ".\n";
        }
    }
}