#include <iostream>
#include <string>
#include <vector>

#include "character.h"
#include "input.h"
#include "inventory.h"
#include "map.h"
#include "skills.h"

int main() {
    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    if (playerName.empty()) {
        playerName = "Player";
    }

    std::cout << "\nChoose a starting class:\n"
              << "1. Class1\n"
              << "2. Class2\n"
              << "3. ClassCombo\n";

    int classChoice;

    do {
        classChoice = getNumber("Choice: ");

        if (classChoice < 1 || classChoice > 3) {
            std::cout << "Please choose 1, 2, or 3.\n";
        }
    } while (classChoice < 1 || classChoice > 3);

    // The class types are placeholders; their gameplay differences come later.
    Class1 class1(playerName);
    Class2 class2(playerName);
    ClassCombo classCombo(playerName);
    Character* player = nullptr;

    if (classChoice == 1) {
        player = &class1;
    } else if (classChoice == 2) {
        player = &class2;
    } else {
        player = &classCombo;
    }

    const std::vector<Item> weapons = {
        {"Sword", 10, 1},
        {"Axe", 12, 1},
        {"Bow", 8, 5}
    };

    std::size_t currentArea = 0; // Start at Home.
    bool running = true;

    while (running) {
        std::cout << "\n=== Main Menu ===\n"
                  << "1. Receive a weapon\n"
                  << "2. Check inventory\n"
                  << "3. Learn a skill\n"
                  << "4. Check learned skills\n"
                  << "5. Show character info\n"
                  << "6. Open map\n"
                  << "0. Quit\n";

        switch (getNumber("Choice: ")) {
        case 1:
            giveWeapon(*player, weapons);
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
            mapMenu(currentArea);
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
