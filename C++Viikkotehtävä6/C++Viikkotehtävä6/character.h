#pragma once

#include <string>
#include <vector>

struct Item {
    std::string name;
    int damage;
    int range;
};

class Character {
public:
    explicit Character(const std::string& name);
    virtual ~Character() = default;

    virtual std::string getClassName() const = 0;

    void displayInfo() const;

    // Skill functions are implemented in skills.cpp.
    void learnSkill(const std::string& skill);
    void displayLearnedSkills() const;

    // Inventory functions are implemented in inventory.cpp.
    void addItem(const Item& item);
    void displayInventory() const;
    int getStrongestWeaponDamage() const;

private:
    std::string name;
    std::vector<std::string> learnedSkills;
    std::vector<Item> inventory;
};

class Class1 : public Character {
public:
    using Character::Character;
    std::string getClassName() const override;
};

class Class2 : public Character {
public:
    using Character::Character;
    std::string getClassName() const override;
};

class ClassCombo : public Character {
public:
    using Character::Character;
    std::string getClassName() const override;
};
