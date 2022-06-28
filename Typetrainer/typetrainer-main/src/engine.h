#ifndef __ENGINE_H_
#define __ENGINE_H_
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <chrono>

#include <ncurses.h>
#include <string>

#include "player.h"
#include "menu_choice.h"

template<typename T>
void change_attr(T win, int y, int x, int n, attr_t attr, short color, const void* opts){
    change_attr(win, y, x, n, attr, color, opts);
}

template <typename T>
int getch_window(T win){
	return getch_window(win); 
}

template <typename T>
void delete_window(T win, int y, int x){
	delete_window(win); 
}

template <typename T>
void move_window(T win, int y, int x){
	move_window(win, y, x); 
}

template <typename T>
void clear_window(T win){
	clear_window(win); 
}

template <typename T>
void refresh_window(T win){
	refresh_windowh(win);
}

template <typename T>
void print_window(T win, int y, int x, std::string& text){
	print_window(win, y, x, text);
}

template <typename T>
void get_win_dim(T win, int& y, int& x){
    get_win_dim(win, y, x);
}

template <typename T>
Player* create(T win){
	std::string player_name = get_player_name(win);
	auto level = get_menu_choice(win, "Choose difficulty level:", level_options, 2, 2);
	clear_window(win);
	return new Player(player_name, Difficulty(level));
}

template <typename T>
Player* choose(T win, std::fstream& db){
    std::string text;
	std::vector<std::string> avaliable_players = get_all_players(db);
	if (avaliable_players.size() == 0) {
		clear_window(win);
        text = "No players in the database yet, please choose a player"; //to be able to pass by reference
        print_window(win, 2, 2, text);
        refresh_window(win);
		sleep(1);
		clear_window(win);
		return create(win);
	}
	int choice = get_menu_choice(win, "Choose your player:", avaliable_players, 2, 2);
	wclear(win);
	return load(db, avaliable_players[choice]);
}

template <typename T>
Player* choose_or_create_player(T win, std::fstream& db) {
	auto choice = get_menu_choice(win, "Create a player or choose an existing one:", create_or_choose_options, 2, 2);
	switch (choice) {
		case 0: // load
			return choose(win, db);
		case 1: // create
			return create(win);
	}
	std::cerr << "Choose or create menu broke\n";
	return nullptr;
}

template <typename T>
void update_level(T win, Player* player){
	auto level = get_menu_choice(win, "Choose new difficulty level:", level_options, 2, 2);
	player->set_level(Difficulty(level));
	return;
}

template <typename T>
void display(T win, std::string& box_name) {
    display(win, box_name);
}

template <typename T>
void visible_cursor(T win) {
    visible_cursor(win);
}

template <typename T>
void play(T win, Player* player){
	int pos{0}, c{0}, cur_mistakes{0};
	long total_mistakes{0}, total_keys{0};

	std::ifstream ifs;
	ifs.open( "../texts/splitted_text.txt", std::ios::in );
	
	if (!ifs.is_open()){
		std::cerr << "Could not access generated text\n";
		exit(1);
	}
	
//	Create game windows, display lables and mistakes counter
	int ymax{0}, xmax{0};
	get_win_dim(win, ymax, xmax);

	WINDOW * win_text = new_window(10, xmax, 0, 0);
	WINDOW * win_input = new_window(10, xmax-40, 10, 0);
	WINDOW * win_stats = new_window(10, 40, 10, xmax-40);
	
    std::string text;
	display(win_text, text = "Sample text");
	display(win_input,  text = "User input");
	display(win_stats, text = "Mistakes counter");

	text = std::to_string(total_mistakes + cur_mistakes);
    print_window(win_stats, 2, 5, text);
	refresh_window(win_stats);
	
	std::string line;

    visible_cursor(win_input);
	

	
//	Start of timer
	auto start = std::chrono::steady_clock::now();
	
	while (getline(ifs, line)){
		if (line.length() < 1) { continue; } //skip empty strings
		
        print_window(win_text, 2, 5, line);
		move_window(win_input, 2, 5);
		move_window(win_text, 2, 5);
		
		refresh_window(win_input);
		refresh_window(win_text);
		
		pos = 5, cur_mistakes = 0;
		
		while(c = getch_window(win_input)){
			switch (c) {
				case KEY_UP:
					//restart the sentence
					change_attr(win_text, 2, 5, line.length(), A_NORMAL, 0, NULL);
					refresh_window(win_text);
					
                    text = std::to_string(total_mistakes);
					print_window(win_stats, 2, 5, text);
					refresh_window(win_stats);
					
					display(win_input,  text = "User input");
					move_window(win_input, 2, 5);
					
					pos = 5, cur_mistakes = 0;
					break;
				case KEY_DOWN:
					//skip the sentence
					pos = line.length()+5;
					break;
				default:
					//check the character
					if (c == (int)line.at(pos-5)){
						change_attr(win_text, 2, pos, 1, A_REVERSE, 0, NULL);
						move_window(win_text, 2, pos+1);
						refresh_window(win_text);
						
						total_keys++;
						pos++;
						break;
					}
					else{				
                        move_window(win_input, 2, pos);
						refresh_window(win_input);
						
						change_attr(win_text, 2, pos, 1, A_REVERSE, 1, NULL);
						refresh_window(win_text);
						
						cur_mistakes++;
                        text = std::to_string(total_mistakes + cur_mistakes);
                        print_window(win_stats, 2, 5, text);
						refresh_window(win_stats);
						break;
					}
			}
			
		if (pos == line.length()+5) break;
		}
		total_mistakes += cur_mistakes;
		
		display(win_text, text = "Sample text");
		display(win_input, text = "User input");
	}
	
//	Finish timer
	auto finish = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(finish - start);
	
    hide_cursor();
	
//	Compute statistics of current round
	auto total_seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count();
	auto speed = (float)total_keys/(float)total_seconds;
	
	auto performance{0};
	if ((int)total_keys != 0) {
		performance = (1 - (float)total_mistakes/(float)total_keys)*100;
	}
	
	post_game_message(win_text, player->get_name(), total_seconds, speed, performance);
	
//	Update player statistics:
	player->post_game_update(speed, performance);

//	Remove all windows
	clear_window(win_text);
	clear_window(win_input);
	clear_window(win_stats);
	
	delete_window(win_text);
	delete_window(win_input);
	delete_window(win_stats);
	
	ifs.close();
	
	return;
}

#endif
