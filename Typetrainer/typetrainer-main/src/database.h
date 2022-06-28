#ifndef __DATABASE_H_
#define __DATABASE_H_
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <chrono>

#include <string>
#include <vector>

#include "player.h"

std::fstream open_database(const std::string path_to_database);
Player* load(std::fstream& db, const std::string player_name);
void store(std::fstream& db, Player* player);

std::vector<std::string> get_all_players(std::fstream& db);
#endif
