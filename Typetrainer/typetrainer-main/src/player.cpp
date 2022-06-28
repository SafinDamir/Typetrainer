#include <iostream>
#include <fstream>

#include <unistd.h>
#include <chrono>
#include <tuple>

#include <ncurses.h>
#include <string>

#include "player.h"
	
Player::Player(std::string name) : _name(name), _level(Difficulty::Beginner), _speed(0), _performance(0), _total_games(0) {};
Player::Player(std::string name, Difficulty level) : _name(name), _level(level), _speed(0), _performance(0), _total_games(0) {};
Player::Player(std::string name, Difficulty level, float speed, float perf, float total_games) : _name(name), _level(level), _speed(speed), _performance(perf), _total_games(total_games) {};

std::string Player::get_name() { return _name; }
Difficulty Player::get_level() { return _level; }
std::tuple<float, float, int> Player::get_stats() { return {_speed, _performance, _total_games}; }

void Player::set_level(Difficulty level) {
	_level = level;
	return;
}

void Player::post_game_update(float speed, float performance) {
	if (speed > 0 && performance > 0 && performance <= 100) {
		_speed = std::max(speed, _speed);
		_performance = std::max(performance, _performance);
	}
	_total_games++;
	return;
}
