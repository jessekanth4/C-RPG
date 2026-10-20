#include "skills.h"

#include "input.h"

#include <iostream>

void Character::learnSkill(const std::string& skill) {
    for (const std::string& knownSkill : learnedSkills) {
        if (knownSkill == skill) {
            std::cout << "You already know " << skill << ".\n";
            return;
        }
    }

    learnedSkills.push_back(skill);
    std::cout << "Learned skill: " << skill << "!\n";
}

void Character::displayLearnedSkills() const {
    std::cout << "\nLearned skills:\n";

    if (learnedSkills.empty()) {
        std::cout << "No learnable skills yet.\n";
        return;
    }

    for (const std::string& skill : learnedSkills) {
        std::cout << "- " << skill << "\n";
    }
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
