#include <iostream>
#include <fstream>

#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

#include <ncurses.h>
#include <string>
#include <vector>

#include <stdlib.h>

#include "player.h"
#include "cli.h"
#include "database.h"
#include "engine.h"
#include "menu_choice.h"


int main(){
	
//	Create progress file or open for adding
	std::fstream log = open_database("statistics.csv");

	
	auto choice{0}, subchoice{0}, level{0}, pid{0};
	std::string welcoming{""};
	bool exit = false;
	
//---------INTRO PART------------------------------------------------------------------------
	WINDOW* source_window;
	source_window = init_UI();  // later here would be CLUI\WebUI switch 
				// with ofc some return handles like stdscr window* obj etc

	welcome_message(source_window);
	Player* main_player = choose_or_create_player(source_window, log);
	
//---------MAIN PART-------------------------------------------------------------------------
	int ymax{0}, xmax{0};
	get_win_dim(source_window, ymax, xmax);

	while(not exit) {
		welcoming = "What do you want to do next, " + main_player->get_name() + "?";
		choice = get_menu_choice(source_window, welcoming, main_cycle_options, 2, 2);
		switch(choice) {
			case 0: //play
				pid = fork(); //quick fix of process termination
				if (pid == 0) {			
					execl("gen", "gen", "10", std::to_string(static_cast<int>(main_player->get_level())+1).c_str(), "../texts/generated_text", NULL);
					
					perror("Text generation:");
					 
					return 0;
				}
								
				pid = fork(); 
				if (pid == 0) {				
					execl("spl", "spl", (std::to_string(static_cast<int>(xmax))).c_str(), "../texts/generated_text", "../texts/splitted_text", NULL);

					perror("Text splitting:");
					 
					return 0;
				}

				wait(NULL);
				play(source_window, main_player);
				store(log, main_player);
				break;
			case 1: //change player
				display_player(source_window, 0, 0, main_player);
				subchoice = get_menu_choice(source_window, "What do you want to change?", player_options, 5, 2);
				
				switch(subchoice) {
					case 0: { //create
						delete main_player;
						main_player = create(source_window);
						break;
					}
					case 1: { //chose from database
						delete main_player;
						main_player = choose(source_window, log);
						break;
					}
					case 2: { //delete
						//del(main_player); TODO update functionality
						delete main_player;
						main_player = choose_or_create_player(source_window, log);
						break;
					}
					case 3: //return
						break;
				}
				break;
			case 2: //change difficulty
				update_level(source_window, main_player);
				break;
			case 3: //get help
				help_message(source_window);
				break;
			case 4: //exit
				exit = true;
				break;
		}
	}
	
	goodbye_message(source_window);
	log.close();
	
	close_UI();

	return 0;
}
