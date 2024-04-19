//
// Created by user on 4/19/24.
//

#include "random_value.h"
#include <cstdlib>
#include <ctime>

int get_random(int max_value) {

    std::srand(std::time(nullptr)); // use current time as seed for random generator

    return std::rand() % max_value;

}
