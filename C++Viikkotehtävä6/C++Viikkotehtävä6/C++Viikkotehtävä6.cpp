#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Item {
    std::string name;
    int damage;
    int range;
};

// Starting character types. Their differences can be designed later.
class Character {
public:
    explicit Character(const std::string& name) : name(name) {}
    virtual ~Character() = default;

    virtual std::string getClassName() const = 0;

    void displayInfo() const {
        std::cout << "\nCharacter: " << name << "\n"
                  << "Class: " << getClassName() << "\n";
    }

    void learnSkill(const std::string& skill) {
        for (const std::string& knownSkill : learnedSkills) {
            if (knownSkill == skill) {
                std::cout << "You already know " << skill << ".\n";
                return;
            }
        }

        learnedSkills.push_back(skill);
        std::cout << "Learned skill: " << skill << "!\n";
    }

    void displayLearnedSkills() const {
        std::cout << "\nLearned skills:\n";
        if (learnedSkills.empty()) {
            std::cout << "No learnable skills yet.\n";
            return;
        }

        for (const std::string& skill : learnedSkills) {
            std::cout << "- " << skill << "\n";
        }
    }

    void addItem(const Item& item) {
        inventory.push_back(item);
        std::cout << "Received: " << item.name << "\n";
    }

    void displayInventory() const {
        std::cout << "\nInventory:\n";
        if (inventory.empty()) {
            std::cout << "Your inventory is empty.\n";
            return;
        }

        for (std::size_t i = 0; i < inventory.size(); ++i) {
            const Item& item = inventory[i];
            std::cout << i + 1 << ". " << item.name
                      << " | Damage: " << item.damage
                      << " | Range: " << item.range << "\n";
        }
    }

private:
    std::string name;
    std::vector<std::string> learnedSkills;
    std::vector<Item> inventory;
};

class Class1 : public Character {
public:
    using Character::Character;
    std::string getClassName() const override { return "Class1"; }
};

class Class2 : public Character {
public:
    using Character::Character;
    std::string getClassName() const override { return "Class2"; }
};

class ClassCombo : public Character {
public:
    using Character::Character;
    std::string getClassName() const override { return "ClassCombo"; }
};

int getNumber(const std::string& prompt) {
    int choice;
    while (true) {
        std::cout << prompt;
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        std::cout << "Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


struct Area {
    std::string name;
    std::vector<int> connections;
};

const std::vector<Area> worldMap = {
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

void mapMenu(std::size_t& currentArea) {
    bool mapOpen = true;

    while (mapOpen) {
        const Area& area = worldMap[currentArea];
        std::cout << "\n=== Map ===\n"
                  << "Current location: " << area.name << "\n"
                  << "Where would you like to go?\n";

        for (std::size_t i = 0; i < area.connections.size(); ++i) {
            const int destination = area.connections[i];
            std::cout << i + 1 << ". " << worldMap[destination].name << "\n";
        }
        std::cout << "0. Return to main menu\n";

        const int choice = getNumber("Choice: ");
        if (choice == 0) {
            mapOpen = false;
        } else if (choice < 1 || choice > static_cast<int>(area.connections.size())) {
            std::cout << "That is not a valid destination.\n";
        } else {
            currentArea = static_cast<std::size_t>(area.connections[choice - 1]);
            std::cout << "Travelled to " << worldMap[currentArea].name << ".\n";
        }
    }
}

void giveWeapon(Character& player, const std::vector<Item>& weapons) {
    std::cout << "\nChoose a weapon to receive:\n";
    for (std::size_t i = 0; i < weapons.size(); ++i) {
        std::cout << i + 1 << ". " << weapons[i].name
                  << " (Damage: " << weapons[i].damage
                  << ", Range: " << weapons[i].range << ")\n";
    }
    std::cout << "0. Cancel\n";

    const int choice = getNumber("Choice: ");
    if (choice == 0) {
        return;
    }
    if (choice < 1 || choice > static_cast<int>(weapons.size())) {
        std::cout << "That is not a valid weapon number.\n";
        return;
    }

    player.addItem(weapons[choice - 1]);
}

void learnSkill(Character& player) {
    std::cout << "\nChoose a skill to learn:\n"
              << "1. Swimming\n"
              << "2. Climbing\n"
              << "0. Cancel\n";

    const int choice = getNumber("Choice: ");
    switch (choice) {
    case 1:
        player.learnSkill("Swimming");
        break;
    case 2:
        player.learnSkill("Climbing");
        break;
    case 0:
        break;
    default:
        std::cout << "That is not a valid skill number.\n";
        break;
    }
}

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
