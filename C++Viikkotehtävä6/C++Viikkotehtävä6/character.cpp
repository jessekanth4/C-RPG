#include "character.h"

#include <iostream>

Character::Character(const std::string& name) : name(name) {}

void Character::displayInfo() const {
    std::cout << "\nCharacter: " << name << "\n"
              << "Class: " << getClassName() << "\n";
}

std::string Class1::getClassName() const {
    return "Class1";
}

std::string Class2::getClassName() const {
    return "Class2";
}

std::string ClassCombo::getClassName() const {
    return "ClassCombo";
}
