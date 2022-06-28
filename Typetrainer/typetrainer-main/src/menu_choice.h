#ifndef __MENU_CHOICE_H_
#define __MENU_CHOICE_H_
#include <iostream>
#include <unistd.h>

#include <string>
#include <vector>

const std::vector<std::string> main_cycle_options {"Start training", "Switch player", "Change difficulty", "Get help :(", "Exit the game"};	
const std::vector<std::string> player_options {"Create a new player", "Load another player", "Delete this player", "Nothing, let's go back to the main menu"};

const std::vector<std::string> level_options {"Beginner", "Intermediate", "Advanced"};
const std::vector<std::string> create_or_choose_options {"Load existing player", "Create a new player"};


#endif
