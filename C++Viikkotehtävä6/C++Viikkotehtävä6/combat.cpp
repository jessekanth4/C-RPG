#include "combat.h"
#include "input.h"

#include <iostream>
#include <random>

// Generate an attack roll from 3 to 9.
int rollAttack()
{
    static std::random_device seed;
    static std::mt19937 generator(seed());
    static std::uniform_int_distribution<int> attackRoll(3, 9);

    return attackRoll(generator);
}

CombatResult fightEnemy(Character& player, Enemy& enemy, int& playerHealth)
{
    std::cout << "\nA " << enemy.name << " blocks the way!\n";

    while (true)
    {
        std::cout << "\nYour health: " << playerHealth << "/" << playerMaxHealth
                  << "\n" << enemy.name << " health: " << enemy.health
                  << "/" << enemy.maxHealth << "\n"
                  << "1. Fight\n"
                  << "2. Run\n";

        const int choice = getNumber("Choice: ");

        if (choice == 2)
        {
            // Running restores both sides and leaves the player where they came from.
            playerHealth = playerMaxHealth;
            enemy.health = enemy.maxHealth;
            std::cout << "You escaped. Both you and the " << enemy.name << " recovered.\n";
            return CombatResult::Escaped;
        }

        if (choice != 1)
        {
            std::cout << "Choose 1 to fight or 2 to run.\n";
            continue;
        }

        // The strongest weapon determines damage. Without a weapon, the player deals 1x the roll.
        const int playerRoll = rollAttack();
        const int playerDamage = playerRoll * player.getStrongestWeaponDamage();
        enemy.health -= playerDamage;

        std::cout << "You rolled " << playerRoll << " and dealt "
                  << playerDamage << " damage.\n";

        if (enemy.health <= 0)
        {
            enemy.health = 0;
            enemy.defeated = true;
            std::cout << "You defeated the " << enemy.name << "!\n";
            return CombatResult::Victory;
        }

        // If the enemy survives, it immediately makes its own attack.
        const int enemyRoll = rollAttack();
        const int enemyDamage = enemyRoll * enemy.damage;
        playerHealth -= enemyDamage;

        std::cout << "The " << enemy.name << " rolled " << enemyRoll
                  << " and dealt " << enemyDamage << " damage.\n";

        if (playerHealth <= 0)
        {
            // Death sends the player Home and restores both combatants.
            playerHealth = playerMaxHealth;
            enemy.health = enemy.maxHealth;
            std::cout << "You were defeated! You return Home, and both of you recover.\n";
            return CombatResult::PlayerDied;
        }
    }
}
