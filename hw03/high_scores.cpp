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

    int print(const std::string &fileName) {
        std::ifstream in_file{fileName};
        if (!in_file.is_open()) {
            std::cout << "Failed to open file for read: " << fileName << "!" << std::endl;
            return -1;
        }

        std::vector<name_count> differentNames;
        std::cout << "High scores table:" << std::endl;
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

    int game(int max_value, const std::string &fileName) {
        std::string user_name;
        int attempts_count = 0;
        int target_value = get_random(max_value);

        // Ask about name
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::cin >> user_name;

        attempts_count = get_check(target_value);

        // Write new high score to the records table
        {
            // We should open the output file in the append mode - we don't want
            // to erase previous results.
            std::ofstream out_file{fileName, std::ios_base::app};
            if (!out_file.is_open()) {
                std::cout << "Failed to open file for write: " << fileName << "!" << std::endl;
                return -1;
            }

            // Append new results to the table:
            out_file << user_name << ' ';
            out_file << attempts_count;
            out_file << std::endl;
        } // end of score here just to mark end of the logic block of code

        return 0;
    }
}
