#pragma once
#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//columns of game_info:
//id	slug	name	metacritic	released	tba	updated	website	rating	rating_top	playtime	achievements_count	ratings_count	suggestions_count	game_series_count	reviews_count	platforms	developers	genres	publishers	esrb_rating	added_status_yet	added_status_owned	added_status_beaten	added_status_toplay	added_status_dropped	added_status_playing
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
vector<string> getVector(string s){
	string value = "";
	vector<string> v;
	int delimCount = 0;
	stringstream linestream(s);
	while (getline(linestream, value, '|')) {
		delimCount++;
		if(delimCount == 2){
			delimCount = 0;
			v.push_back(value);
		}
	}
	return v;
}

void Load(string filename, vector<Game>& gameVector) {

	int id = 0;
    string name = "";
    vector<string> developers;
	string stringDevelopers = "";
    vector<string> genres;
	string stringGenres = "";
	vector<string> platforms;
	string stringPlatforms = "";
    string releaseDate = "";
    double rating = 0.0;
    int playtime = 0;
    int achievementCount = 0;

	string value;
	int count = 1;

	ifstream file(filename);
	string fileline;

	while (getline(file, fileline)) {
		stringstream linestream(fileline);
		while (getline(linestream, value, ',')) {
			switch (count) {
			case 1: //id
                try {
					id = stoi(value);
				}
				catch (const invalid_argument& ia) {
					id = 00000000;
				}
				break;
			case 2: //slug
				break;
			case 3: //name
				name = value;
				break;
			case 4: //metacritic
				rating = stod(value);
                break;
			case 5: //released
				releaseDate = value;
                break;
            case 6: //-tba
                break;
			case 7: //-updated
                break;
			case 8: //-website
				break;
            case 9: //-rating
                break;
			case 10: //-rating top
				break;
			case 11: //playtime
				try{
                    playtime = stoi(value);
                }
                catch (const invalid_argument& ia){
                    playtime = 00000000;
                }
				break;
			case 12: //achievment count
				try {
					achievementCount = stoi(value);
				}
				catch (const invalid_argument& ia) {
					achievementCount = 00000000;
				}
				break;
			case 13: //-rating count
				break;
			case 14: //-suggestions count
				break;
			case 15: //-game series count
				break;
			case 16: //-reviews count
				break;
			case 17: //platforms
				stringPlatforms = value;
				break;
			case 18: //developers
				stringDevelopers = value;
				break;
			case 19: //genres
				stringGenres = value;
				break;
			case 20: //-publishers
				break;
			case 21: //-esrb rating
				break;
			case 22: //-added status yet
				break;
			case 23: //-added status owned
				break;
			case 24: //-added status beaten
				break;
			case 25: //-added status toplay
				break;
			case 26: //-added status dropped
				break;
			case 27: //-added status playing
				break;
			}
			count++;
		}
        count = 1;
		developers = getVector(stringDevelopers);
		genres = getVector(stringGenres);
		platforms = getVector(stringPlatforms);
		Game g = Game(id,name,developers,genres,platforms,releaseDate,rating,playtime,achievementCount);
        gameVector.push_back(g);
	}
}

