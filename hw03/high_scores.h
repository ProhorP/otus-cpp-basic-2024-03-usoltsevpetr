//
// Created by user on 4/19/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_HIGH_SCORES_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_HIGH_SCORES_H

namespace high_scopes {
    struct name_count{
        std::string username;
        int high_score = 0;
    };
    int print(const std::string &fileName);
    int game(int max_value, const std::string &fileName);
}

#endif //OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_HIGH_SCORES_H
