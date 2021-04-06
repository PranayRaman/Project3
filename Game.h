#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

// Basic data container for games
// Main identifier for trees/maps will be id
struct Game {
    int id = 0;
    string name = "";
    vector<string> developers;
    vector<string> genres;
    vector<string> platforms;
    string releaseDate = "";
    double rating = 0.0;
    int playtime = 0;
    int achievementCount = 0;
};

/*
Game class stored as:
	id (tree/map are constructed with this as node/index)
	name
	developer(s)
	genre (replace blank with ?)
	date released
	metacritic rating (repl. 0 with N/A when displaying)
	playtime (repl. 0 with ? when displaying)
	achievements (repl. 0 with ? when displaying)
*/