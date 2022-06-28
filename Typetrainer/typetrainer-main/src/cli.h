#ifndef __CLI_H_
#define __CLI_H_
#include <iostream>
#include <unistd.h>

#include <string>
#include <vector>

#include <ncurses.h>

#include "player.h"
#include "menu_choice.h"

void hide_cursor();

void change_attr(WINDOW* win, int y, int x, int n, attr_t attr, short color, const void* opts);

int getch_window(WINDOW* win);

void delete_window(WINDOW* win);

void move_window(WINDOW* win, int y, int x);

void clear_window(WINDOW* win);

void refresh_window(WINDOW* win);

void print_window(WINDOW* win, int y, int x, std::string& text);

void get_win_dim(WINDOW* win, int& y, int& x);

void display(WINDOW* win, std::string& box_name);

void visible_cursor(WINDOW* win);

WINDOW* new_window(int y, int x, int y_init, int x_init);

void welcome_message(WINDOW* win);
void help_message(WINDOW* win);
void goodbye_message(WINDOW* win);
void post_game_message(WINDOW* win, std::string player_name, long elapsed_time, double speed, int performance);

int get_menu_choice(WINDOW* win, std::string menu_name, const std::vector<std::string> options, int x, int y);

std::string get_player_name(WINDOW* win);
void display_player(WINDOW* win, int y, int x, Player* player);

WINDOW* init_UI();
void close_UI();
#endif
