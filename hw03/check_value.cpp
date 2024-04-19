//
// Created by user on 4/19/24.
//

#include "check_value.h"
#include <iostream>

int get_check(const int target_value) {

    int count = 0;

    std::cout << "Enter your guess:" << std::endl;

    do {
        int current_value = 0;
        std::cin >> current_value;

        if (current_value < target_value) {
            std::cout << "less than " << current_value << std::endl;
            count++;
        }
        else if (current_value > target_value) {
            std::cout << "greater than " << current_value << std::endl;
            count++;
        }
        else {
            std::cout << "you win!" << std::endl;
            break;
        }

    } while(true);

    return count;
}