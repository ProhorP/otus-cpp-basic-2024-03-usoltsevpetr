//
// Created by user on 4/19/24.
//

#include <iostream>
#include <string>
#include "high_scores.h"

int main(int argc, char **argv) {

    int max_value = 100;
    bool only_print = false;
    // argc - it is a count of arguments
    // But there is some detail - OS always pass one system argument - the name of the executable
    // So, is the application was executed without arguments at all, argc will be still == 1

    // Let's print this argument
    if (argc > 0) {
        std::cout << "We have at least one argument!" << std::endl;
        std::cout << "argv[0] = " << argv[0] << std::endl;
    }

    // To check - does use print some other argument we should check if the argc >= 2
    if (argc >= 2) {
        std::cout << "We have one more argument!" << std::endl;
        std::cout << "argv[1] = " << argv[1] << std::endl;

        std::string arg1_value{argv[1]};
        if (arg1_value == "–max") {
            std::cout << "-parameter argument was detected!" << std::endl;

            // We've detected the '-parameter' argument. And we extect that after this argument there is a value:
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;
                return -1;
            }
            // We need to parse the string to the int value
            max_value = std::stoi(argv[2]);
            std::cout << "The '-parameter' value = " << max_value << std::endl;
        } else if (arg1_value == "-table") {
            only_print = true;
        } else if (arg1_value == "–level") {
            std::cout << "-parameter argument was detected!" << std::endl;

            // We've detected the '-parameter' argument. And we extect that after this argument there is a value:
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;
                return -1;
            }
            // We need to parse the string to the int value
            int level = std::stoi(argv[2]);
            switch (level) {
                case 1:
                    max_value = 10;
                    break;
                case 2:
                    max_value = 50;
                    break;
                case 3:
                    max_value = 100;
                    break;
                default:
                    std::cout << "invalid level" << std::endl;
                    return -1;
            }
            std::cout << "The '-parameter' value = " << level << std::endl;
        }
    }

    const std::string high_scores_filename = "high_scores.txt";

    if (!only_print)
        if (high_scopes::game(max_value, high_scores_filename) < 0)
            return -1;

    return high_scopes::print(high_scores_filename);

}