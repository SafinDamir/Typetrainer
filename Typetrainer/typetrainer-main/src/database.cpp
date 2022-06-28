#include <iostream>
#include <fstream>
#include <filesystem>

#include <unistd.h>
#include <stdlib.h>
#include <chrono>

#include <string>
#include <vector>

#include "player.h"

std::fstream open_database(const std::string path_to_database){
	
	std::fstream db;
	db.open( "../src/statistics.csv", std::ios::in | std::ios::out | std::ios::ate );
	
	if (!db.is_open()){
		std::cerr << "Could not access statistics\n";
		exit(1);
	}
	
	db << std::fixed;
	
	return db;
}

Player* load(std::fstream& db, const std::string player_name){
	db.clear();
	db.seekp(0);
	std::string player_line = "";
	
	std::getline(db,player_line); //skipping header
	
	while(std::getline(db, player_line)) {
		if (player_line.find(player_name) == 0) {
			int level = static_cast<int>(player_line.at(player_name.length()+1)) - static_cast<int>('0');
			return new Player(player_name, Difficulty(level));
		}
	}
	std::cerr << "Loading function broke\n";
	return nullptr; //couldn't find a player, something must be broken
}
void store(std::fstream& db, Player* player) {
	db.clear();
	db.seekp(0);

	std::string player_line = "";
	auto line_pos{0};
	
	std::getline(db,player_line); //skipping header
	line_pos = db.tellp();
	
	auto [speed, perf, total_games] = player->get_stats();
	
	while(std::getline(db, player_line)) {
		if (player_line.find(player->get_name()) != std::string::npos) {
			//player already existed in the db
			db.seekp(line_pos + player->get_name().length()+1);
			
			db << static_cast<int>(player->get_level()) << "," << std::setw(10) << speed << "," << std::setw(10) << perf << "," << std::setw(10) << total_games << std::endl;
			
			db.clear();
			db.seekp(0); //for changes to show immediately
			return;
		}
		line_pos = db.tellp();
	}
	//player is new and is just appended to the file
	db.clear();
	db.seekp(0, std::ios::end);
	
	db << player->get_name() << "," << static_cast<int>(player->get_level()) << "," << std::setw(10) << speed << "," << std::setw(10) << perf << "," << std::setw(10) << total_games << std::endl;
	db.clear();
	return;
}

//void del(std::fstream& db, Player* player){}

std::vector<std::string> get_all_players(std::fstream& db) {
	db.clear();
	db.seekp(0);

	std::string player_line = "";
	std::vector<std::string> players{};
	
	std::getline(db,player_line); //skipping header
	
	while(std::getline(db, player_line)) {
		players.push_back(player_line.substr(0, player_line.find(',')));
	}
	return players;
}

//void clear_all_data(std::fstream db) {
//}
