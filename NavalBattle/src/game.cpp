#include <gamestate/gamestate.h>
#include <serialize/serialize.h>
#include <visualize/visualize.h>

#include <menu/menu.h>

#include <iostream>

#include <cassert>

bool do_load_game() {
    std::string folder_path = menu::folder_path();

    // load player1 field
    int size = 0;

    const std::string player1_field_path = folder_path + "/player1_field.dat";
    if (!serialize::load(player1_field_path.c_str(), gamestate::get_player1_field(), size)) {
        std::cerr << "Failed to load player1 field! File: " << player1_field_path << std::endl;
        return false;
    }

    const std::string player1_intel_path = folder_path + "/player1_intel.dat";
    if (!serialize::load(player1_intel_path.c_str(), gamestate::get_player1_intel(), size)) {
        std::cerr << "Failed to load player1 field! File: " << player1_intel_path << std::endl;
        return false;
    }

    const std::string player2_field_path = folder_path + "/player2_field.dat";
    if (!serialize::load(player2_field_path.c_str(), gamestate::get_player2_field(), size)) {
        std::cerr << "Failed to load player2 field! File: " << player2_field_path << std::endl;
        return false;
    }

    const std::string player2_intel_path = folder_path + "/player2_intel.dat";
    if (!serialize::load(player2_intel_path.c_str(), gamestate::get_player2_intel(), size)) {
        std::cerr << "Failed to load player2 field! File: " << player2_intel_path << std::endl;
        return false;
    }

    gamestate::set_field_size(size);

    return true;
}

bool do_save_game() {
    const std::string folder_path = menu::folder_path();
    const int size = gamestate::get_field_size();

    const std::string player1_field_path = folder_path + "/player1_field.dat";
    if (!serialize::save(player1_field_path.c_str(), gamestate::get_player1_field(), size)) {
        std::cerr << "Failed to save player1 field! File: " << player1_field_path << std::endl;
        return false;
    }

    const std::string player1_intel_path = folder_path + "/player1_intel.dat";
    if (!serialize::save(player1_intel_path.c_str(), gamestate::get_player1_intel(), size)) {
        std::cerr << "Failed to save player1 field! File: " << player1_intel_path << std::endl;
        return false;
    }

    const std::string player2_field_path = folder_path + "/player2_field.dat";
    if (!serialize::save(player2_field_path.c_str(), gamestate::get_player2_field(), size)) {
        std::cerr << "Failed to save player2 field! File: " << player2_field_path << std::endl;
        return false;
    }

    const std::string player2_intel_path = folder_path + "/player2_intel.dat";
    if (!serialize::save(player2_intel_path.c_str(), gamestate::get_player2_intel(), size)) {
        std::cerr << "Failed to save player2 field! File: " << player2_intel_path << std::endl;
        return false;
    }

    return true;
}

bool do_manual_deploy() {
    return true;
}

menu::CoordinatesSection step_player(gamestate::State *field, gamestate::State *intel, int
number) {

    menu::CoordinatesSection ret;
    using namespace gamestate;

    int row, col;
    ret = menu::coordinates(size, row, col);
    if (ret == menu::CoordinatesSection::Back)
        return ret;

    State state;
    bool isOk = get_state(field, row, col, state);
    if (!isOk) {
        std::cerr << "Erorr due to set state for row = " << row << " col = " << col << "!" << std::endl;
        return menu::CoordinatesSection::Back;
    }

    switch (state) {
        case State::Empty:
            std::cout << "Empty!" << std::endl;
            set_state(field, row, col, State::Fail);
            set_state(intel, row, col, State::Fail);
            break;
        case State::Ship:
            std::cout << "Ship was hit!" << std::endl;
            set_state(field, row, col, State::Hit);
            set_state(intel, row, col, State::Hit);
            break;
        case State::Hit:
            std::cout << "Already hit this coordinates!" << std::endl;
            break;
        case State::Fail:
            std::cout << "Already fail this coordinates!" << std::endl;
            break;
        default:
            assert(false);
    }

    bool all_hit = true;
    for (int i = 0; i < size && all_hit; ++i) {
        for (int j = 0; j < size; ++j) {
            get_state(field, i, j, state);
            if (state == State::Ship) {
                all_hit = false;
                break;
            }
        }
    }
    if (all_hit) {
        std::cout << "All player" << number << "'s ship were hit! You win!" << std::endl;
        return menu::CoordinatesSection::Back;
    }

    return ret;

}

void do_game() {
    using namespace gamestate;

    State *player1_intel_ptr = get_player1_intel();
    State *player2_intel_ptr = get_player2_intel();
    State *player1_field_ptr = get_player1_field();
    State *player2_field_ptr = get_player2_field();

    while (step_player(player2_field_ptr, player1_intel_ptr, 2) == menu::CoordinatesSection::Next &&
           step_player(player1_field_ptr, player2_intel_ptr, 1) == menu::CoordinatesSection::Next);
}

int main(int, char **) {

    // Do initialization
    const int field_size = 3;
    gamestate::set_field_size(field_size);

    bool game_started = false;
    using menu::MainSection;
    MainSection main_section;
    do {
        main_section = menu::main();
        switch (main_section) {
            case MainSection::Quit:
                std::cout << "Thank you! See you later!" << std::endl;
                break;
            case MainSection::NewGame: {
                std::cout << "New game creation" << std::endl;

                menu::NewGameSection section = menu::new_game();
                switch (section) {
                    case menu::NewGameSection::Back:
                        continue;
                        break;
                    case menu::NewGameSection::AutoDeploy:
                        std::cerr << "Auto deploy was not implemented yet! Manual deploy will be used." << std::endl;
                        [[fallthrough]];
                    case menu::NewGameSection::ManualDeploy:
                        do_manual_deploy();
                        break;
                }
                game_started = true;
                break;
            }
            case MainSection::LoadGame: {
                std::cout << "Loading the previous game" << std::endl;
                if (!do_load_game()) {
                    std::cerr << "Failed to load the game! Data are corrupted! Exit!" << std::endl;
                    return -1;
                }
                std::cout << "The previous game was loaded successfully!" << std::endl;

                game_started = true;
                break;
            }
            case MainSection::SaveGame: {
                std::cout << "Saving the current game" << std::endl;
                if (!do_save_game()) {
                    std::cerr << "Failed to save the current game!" << std::endl;
                }
                std::cout << "The game was saved successfully!" << std::endl;
                break;
            }
            default:
                std::cerr << "Unknown menu section! Exit!" << std::endl;
                return -1;
        };

        if (game_started) {
            do_game();
        }
        game_started = false;
    } while (main_section != MainSection::Quit);

    return 0;
}