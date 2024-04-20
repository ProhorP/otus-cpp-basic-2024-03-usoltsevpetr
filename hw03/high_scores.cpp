//
// Created by user on 4/19/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include "high_scores.h"
#include "check_value.h"
#include "random_value.h"

int work(int max_value, bool only_print) {

    const std::string high_scores_filename = "high_scores.txt";
    const std::string temp_filename = "temp.txt";
    std::string user_name;
    int attempts_count = 0;

    if (!only_print) {
        int target_value = get_random(max_value);

        // Ask about name
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::cin >> user_name;

        attempts_count = get_check(target_value);

        //Доп.задание №3 - не сообразил как сделать без хэш-таблицы, т.к. мы их не проходили

        //Доп.задание №4 Начало

        // Read the high score file and print all results
        std::ofstream out_file{temp_filename};
        if (!out_file.is_open()) {
            std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
            return -1;
        }

        bool find = false;
        std::ifstream in_file{high_scores_filename};
        if (in_file.is_open()) {
            while (true) {
                std::string tmp_username;
                int tmp_high_score = 0;
                // Read the username first
                in_file >> tmp_username;
                // Read the high score next
                in_file >> tmp_high_score;
                // Ignore the end of line symbol
                in_file.ignore();

                if (in_file.fail()) {
                    break;
                }

                if (tmp_username == user_name) {
                    find = true;
                    if (tmp_high_score > attempts_count) {
                        tmp_high_score = attempts_count;
                    }
                }

                // Print the information to the screen
                out_file << tmp_username << '\t' << tmp_high_score << std::endl;
            }
        }

        if (!find)
            out_file << user_name << '\t' << attempts_count << std::endl;

        out_file.close();
        if (in_file.is_open()) {
            in_file.close();
            remove(high_scores_filename.c_str());
        }
        rename(temp_filename.c_str(), high_scores_filename.c_str());
        //Доп.задание №4 Конец

    }

    {
        std::ifstream in_file{high_scores_filename};
        if (!in_file.is_open()) {
            std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
            return -1;
        }

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

            // Print the information to the screen
            std::cout << username << '\t' << high_score << std::endl;
        }

    }

    return 0;
}