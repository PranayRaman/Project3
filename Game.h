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
    vector<string> platform;

    Game(int id_, string name_, vector<string> developers_, vector<string> genres_, string releaseDate_, double rating_, int playtime_, int achievementCount, vector<string> platform_);
};

Game::Game(int id_, string name_, vector<string> developers_, vector<string> genres_, string releaseDate_, double rating_, int playtime_, int achievementCount, vector<string> platform_){
    id =  id_;
    name =  name_;
    developers = developers_;
    genres = genres_;
    releaseDate = releaseDate_;
    rating = rating_;
    playtime = playtime_;
    achievementCount = achievementCount;
    platform = platform_;
}


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