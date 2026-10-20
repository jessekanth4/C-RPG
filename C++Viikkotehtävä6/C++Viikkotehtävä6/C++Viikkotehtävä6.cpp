#include <iostream>
#include <limits>
#include <string>
#include <vector>

// All skills that a character can learn.
// Add new skill types here as the game grows.
enum class Skill
{
    Flying,
    Swimming,
    Melee,
    Ranged
};

// Returns the name of a skill for displaying it to the player.
std::string getSkillName(Skill skill)
{
    switch (skill)
    {
    case Skill::Flying:
        return "Flying";
    case Skill::Swimming:
        return "Swimming";
    case Skill::Melee:
        return "Melee";
    case Skill::Ranged:
        return "Ranged";
    default:
        return "Unknown skill";
    }
}

class Character
{
public:
    Character(const std::string& name) : name(name) {}

    void displayInfo() const
    {
        std::cout << "\nCharacter: " << name << "\n";
    }

    // Check whether the character already knows a skill.
    bool hasSkill(Skill skill) const
    {
        for (Skill learnedSkill : skills)
        {
            if (learnedSkill == skill)
            {
                return true;
            }
        }

        return false;
    }

    // Add a skill if the character does not already have it.
    void learnSkill(Skill skill)
    {
        if (hasSkill(skill))
        {
            std::cout << "You already have " << getSkillName(skill) << ".\n";
            return;
        }

        skills.push_back(skill);
        std::cout << "You learned " << getSkillName(skill) << "!\n";
    }

    void displaySkills() const
    {
        std::cout << "Your skills:\n";

        if (skills.empty())
        {
            std::cout << "  None yet\n";
            return;
        }

        for (Skill skill : skills)
        {
            std::cout << "  - " << getSkillName(skill) << "\n";
        }
    }

private:
    std::string name;
    std::vector<Skill> skills;
};

int main()
{
    std::string playerName;

    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    Character player(playerName);

    // This selection loop can later be reused when the player unlocks skills.
    bool choosingSkills = true;

    while (choosingSkills)
    {
        std::cout << "\n=== Available skills ===\n";
        std::cout << "1. Flying\n";
        std::cout << "2. Swimming\n";
        std::cout << "3. Melee\n";
        std::cout << "4. Ranged\n";
        std::cout << "0. Finish choosing skills\n";
        std::cout << "Enter a number to learn a skill: ";

        int choice;

        if (!(std::cin >> choice))
        {
            std::cout << "Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            player.learnSkill(Skill::Flying);
            break;
        case 2:
            player.learnSkill(Skill::Swimming);
            break;
        case 3:
            player.learnSkill(Skill::Melee);
            break;
        case 4:
            player.learnSkill(Skill::Ranged);
            break;
        case 0:
            choosingSkills = false;
            break;
        default:
            std::cout << "That is not a valid skill number. Try again.\n";
            break;
        }
    }

    player.displayInfo();
    player.displaySkills();

    std::cout << "\nThanks for playing!\n";
    return 0;
}
