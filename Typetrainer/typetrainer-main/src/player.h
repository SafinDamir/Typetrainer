#ifndef __PLAYER_H_
#define __PLAYER_H_
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <chrono>
#include <tuple>

#include <ncurses.h>
#include <string>

enum class Difficulty{
	Beginner,
	Intermediate,
	Advanced
};

class Player{
private:
	const std::string _name;
	Difficulty _level;
	float _speed;
	float _performance;
	int _total_games;
	
public:
	
	Player(std::string name);
	Player(std::string name, Difficulty level);
	Player(std::string name, Difficulty level, float speed, float perf, float total_games);
	
	std::string get_name();
	
	Difficulty get_level();
	void set_level(Difficulty level);
	
	std::tuple<float, float, int> get_stats();
	void post_game_update(float speed, float performance);
};
#endif
