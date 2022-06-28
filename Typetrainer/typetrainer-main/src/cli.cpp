#include <iostream>
#include <unistd.h>

#include <string>
#include <vector>

#include <ncurses.h>

#include "player.h"
#include "database.h"
#include "menu_choice.h"

void hide_cursor(){
	curs_set(0);
}

void change_attr(WINDOW* win, int y, int x, int n, attr_t attr, short color, const void* opts){
	mvwchgat(win, y, x, n, attr, color, opts);
}

int getch_window(WINDOW* win){
	return wgetch(win);
}

void delete_window(WINDOW* win){
	delwin(win);
}

void move_window(WINDOW* win, int y, int x){
	wmove(win, y, x);
}

void clear_window(WINDOW* win){
	wclear(win); 
}

void refresh_window(WINDOW* win){
	wrefresh(win);
}

void print_window(WINDOW* win, int y, int x, std::string& text){
	mvwprintw(win, y, x, text.c_str());
}

void get_win_dim(WINDOW* win, int& y, int& x){
	getmaxyx(win, y, x);
}

void display(WINDOW* win, std::string& box_name) {
	wclear(win);
	
	box(win, 0, 0);
	mvwprintw(win, 0, 2, box_name.c_str());
	
	wrefresh(win);
	return;
}

void visible_cursor(WINDOW* win){
	keypad(win, TRUE);
	curs_set(1); // making the cursor visible for the game period
}

WINDOW* new_window(int y, int x, int y_init, int x_init){
	return newwin(y, x, y_init, x_init);
}

WINDOW* init_UI() {
	
	initscr();  //begin ncurses mode
	start_color();
	curs_set(0);  //hide the cursor
	if (has_colors()) { init_pair(1, COLOR_WHITE, COLOR_RED); } //mistake style
	
	return stdscr;
}

void welcome_message(WINDOW* win) {
	
	wclear(win);

	int ymax{0}, xmax{0};
	getmaxyx(win, ymax, xmax);
	auto xc = (int)xmax/2, yc = (int)ymax/2;
	
	mvwprintw(win, yc-1, xc-13, "Welcome to typing trainer!");
	mvwprintw(win, yc, xc-9, "- Version 1.3.0 -");
	
	wrefresh(win);
	sleep(2);
	wclear(win);
	
	return;
}

void help_message(WINDOW* win) {
	wclear(win);
	
	int ymax{0}, xmax{0};
	getmaxyx(win, ymax, xmax);
	auto xc = (int)xmax/2, yc = (int)ymax/2;
	
	mvwprintw(win, yc-3, xc-18, "You are playing command line typing");
	mvwprintw(win, yc-2, xc-16, "trainer, which measures your");
	mvwprintw(win, yc-1, xc-16, "speed and quality of typing");
	mvwprintw(win, yc+1, xc-16, "you can navigate through text:");
	mvwprintw(win, yc+2, xc-16, "- to restart a sentence press UP");
	mvwprintw(win, yc+3, xc-16, "- to skip a sentence press DOWN");
	mvwprintw(win, yc+5, xc-18, "Press any key to exit help message");
	wrefresh(win);
	
	wgetch(win);
	wclear(win);
	return;
}

void goodbye_message(WINDOW* win) {
	wclear(win);

	int ymax{0}, xmax{0};
	getmaxyx(win, ymax, xmax);
	auto xc = (int)xmax/2, yc = (int)ymax/2;
	
	mvwprintw(win, yc-1, xc-15, "Looking forward to see you again!");
	mvwprintw(win, yc, xc-3, "- Bye -");
	
	wrefresh(win);
	sleep(2);
	wclear(win);
	
	return;
}

void close_UI() {

	curs_set(1); // bringing the cursor back just in case
	endwin(); // end ncurses mode
	
	return;
}

void post_game_message(WINDOW* win, std::string player_name, long elapsed_time, double speed, int performance) {
	
	int ymax{0}, xmax{0};
	getmaxyx(win, ymax, xmax);
	auto xc = (int)xmax/2, yc = (int)ymax/2;
	
	mvwprintw(win, 2, 5, "You did it, %s!", player_name.c_str());
	mvwprintw(win, 4, 5, "Elapsed time: %ld seconds", elapsed_time);
	mvwprintw(win, 5, 5, "Average speed %.2f keys per second", speed);
	mvwprintw(win, 6, 5, "With %d% rate of right characters", performance);
	wrefresh(win);
	sleep(3);
	return;
}

int get_menu_choice(WINDOW* win, std::string menu_name, const std::vector<std::string> options, int y, int x) {
	keypad(win, true);
	mvwprintw(win, y, x, menu_name.c_str());
	
	int choice{0};
	int highlight{0};
	
	while(1) {
		for (int i = 0; i < options.size(); i++) {
			if (i == highlight) { wattron(win, A_REVERSE); }
			mvwprintw(win, y+2+i, x+1, options[i].c_str());
			wattroff(win, A_REVERSE);
		}
		choice = wgetch(win);
		switch(choice) {
			case KEY_UP:
				highlight--;
				if (highlight == -1) { highlight = options.size() - 1; }
				break;
			case KEY_DOWN:
				highlight++;
				if (highlight == options.size()) { highlight = 0; }
				break;
			default:
				break;
		}
		if (choice == 10) { //KEY_ENTER
			wclear(win);
			return highlight;
		}
	}
}

std::string get_player_name(WINDOW* win) {
	wclear(win);
	mvwprintw(win, 2, 2, "Enter new player's name:");
	wrefresh(win);

	WINDOW * subwin = newwin(3, 36, 4, 2);
	
	std::string text;
	display(subwin, text = "New username");
	
	keypad(subwin, true);
	wmove(subwin, 1, 2);
	int c{0};
	
	std::string playername = "";
	while((c = wgetch(subwin)) != 10){ //KEY_ENTER
		if ( isalpha(c) && playername.length() < 20 ) { playername += (char)c; }
		if ( c == KEY_BACKSPACE ) {
			if ( playername.length() != 0 ) {
				playername.pop_back();
			}
		}
		display(subwin, text = "New username");
		mvwprintw(subwin, 1, 2, playername.c_str());
		wrefresh(subwin);
	}
	
	delwin(subwin);
	wclear(win);
	
	return playername;
}

void display_player(WINDOW* win, int y, int x, Player* player) {
	std::vector<std::string> levels = {"Beginner", "Intermediate", "Advanced"};

	wclear(win);
	mvwprintw(win, y+2, x+2, "Current player is: %s", player->get_name().c_str());
	mvwprintw(win, y+3, x+2, "Level: %s", levels[static_cast<int>(player->get_level())].c_str());
	
	return;
}
