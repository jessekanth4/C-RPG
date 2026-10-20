#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "character.h"
#include "combat.h"
#include "input.h"
#include "inventory.h"
#include "map.h"
#include "skills.h"

// Clears the console so each menu is easier to read.
void clearScreen()
{
    std::system("cls");
}

int main()
{
    // Ask for the character's name. Use a default if the player leaves it blank.
    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    if (playerName.empty())
    {
        playerName = "Player";
    }

    // Let the player choose one of the three currently available character classes.
    std::cout << "\nChoose a starting class:\n"
              << "1. Class1\n"
              << "2. Class2\n"
              << "3. ClassCombo\n";

    int classChoice;

    do
    {
        classChoice = getNumber("Choice: ");

        if (classChoice < 1 || classChoice > 3)
        {
            std::cout << "Please choose 1, 2, or 3.\n";
        }

    } while (classChoice < 1 || classChoice > 3);

    // Create the selected character. The class types are placeholders for now.
    Class1 class1(playerName);
    Class2 class2(playerName);
    ClassCombo classCombo(playerName);
    Character* player = nullptr;

    if (classChoice == 1)
    {
        player = &class1;
    }
    else if (classChoice == 2)
    {
        player = &class2;
    }
    else
    {
        player = &classCombo;
    }

    // Each weapon belongs to one map location and can only be taken once.
    std::vector<WorldWeapon> worldWeapons =
    {
        {3, {"Rock", 2, 3}, true},       // Cliffs
        {7, {"Sword", 10, 1}, true},     // Town
        {6, {"Axe", 12, 1}, true},       // Deep forest
        {4, {"Bow", 8, 5}, true}         // Forest edge
    };

    // Each enemy guards one location. Damage is the multiplier for its attack roll.
    std::vector<Enemy> enemies =
    {
        {"Rogue", 4, 1, 36, 36, false},          // Forest edge
        {"Tree monster", 6, 2, 55, 55, false},  // Deep forest
        {"Thief", 7, 2, 45, 45, false},         // Town
        {"Pirate", 8, 3, 70, 70, false}         // Shore
    };

    // The player starts at Home with full health.
    std::size_t currentArea = 0;
    int playerHealth = playerMaxHealth;
    bool running = true;

    while (running)
    {
        std::cout << "\n=== Main Menu ===\n"
                  << "1. Take weapon\n"
                  << "2. Check inventory\n"
                  << "3. Learn a skill\n"
                  << "4. Check learned skills\n"
                  << "5. Show character info\n"
                  << "6. Open map\n"
                  << "0. Quit\n";

        // Show the weapon at the current location, if one is still available.
        displayWeaponAtLocation(worldWeapons, currentArea);

        // Run the menu option selected by the player.
        switch (getNumber("Choice: "))
        {
        case 1:
            takeWeaponAtLocation(*player, worldWeapons, currentArea);
            break;
        case 2:
            player->displayInventory();
            break;
        case 3:
            learnSkill(*player);
            break;
        case 4:
            player->displayLearnedSkills();
            break;
        case 5:
            player->displayInfo();
            break;
        case 6:
            mapMenu(currentArea, *player, enemies, playerHealth);
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "That is not a valid menu option.\n";
            break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
