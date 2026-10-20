#include "input.h"
#include <iostream>
#include <limits>

int getNumber(const std::string& prompt)
{
    int choice;

    while (true)
    {
        std::cout << prompt;

        if (std::cin >> choice)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        std::cout << "Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}