//
// Created by user on 4/19/24.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "high_scores.h"
#include "check_value.h"
#include "random_value.h"

namespace high_scopes {

    int getdifferentNames(const std::string &fileName, std::vector<name_count> &differentNames) {
        std::ifstream in_file{fileName};
        if (!in_file.is_open()) {
            std::cout << "Failed to open file for read: " << fileName << "!" << std::endl;
            return -1;
        }

        std::string username;
        int high_score = 0;
        while (true) {
            // Read the username first
            in_file >> username;
            // Read the high score next
            in_file >> high_score;
            // Ignore the end of line symbol
            in_file.ignore();

            if (in_file.fail()) {
                break;
            }

            bool find = false;
            for (name_count &tmp: differentNames) {
                if (tmp.username == username) {
                    if (tmp.high_score > high_score)
                        tmp.high_score = high_score;
                    find = true;
                    break;
                }
            }
            if (!find)
                differentNames.push_back({username, high_score});
            // Print the information to the screen
        }

        for (name_count &tmp: differentNames)
            std::cout << tmp.username << '\t' << tmp.high_score << std::endl;

        return 0;

    }

    int print(const std::string &fileName) {
        std::vector<name_count> differentNames;
        if (getdifferentNames(fileName, differentNames) < 0)
            return -1;

        std::cout << "High scores table:" << std::endl;
        for (name_count &tmp: differentNames)
            std::cout << tmp.username << '\t' << tmp.high_score << std::endl;

        return 0;

    }

    int game(int max_value, const std::string &fileName) {
        std::string user_name;
        int attempts_count = 0;
        int target_value = get_random(max_value);
        std::vector<name_count> differentNames;
        if (getdifferentNames(fileName, differentNames) < 0)
            return -1;

        // We should open the output file in the append mode - we don't want
        // to erase previous results.
        std::ofstream file{fileName};
        if (!file.is_open()) {
            std::cout << "Failed to open file for write: " << fileName << "!" << std::endl;
            return -1;
        }

        // Ask about name
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::cin >> user_name;

        attempts_count = get_check(target_value);

        bool find = false;
        for (name_count &tmp: differentNames) {
            if (tmp.username == user_name) {
                if (tmp.high_score > attempts_count)
                    tmp.high_score = attempts_count;
                find = true;
                break;
            }
        }
        if (!find)
            differentNames.push_back({user_name, attempts_count});

        for (name_count &tmp: differentNames) {
            file << tmp.username << ' ';
            file << tmp.high_score;
            file << std::endl;
        }

        return 0;
    }
}
