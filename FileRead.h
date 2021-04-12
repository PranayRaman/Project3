#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

//columns of game_info:
//id	slug	name	metacritic	released	tba	updated	website	rating	rating_top	playtime	achievements_count	ratings_count	suggestions_count	game_series_count	reviews_count	platforms	developers	genres	publishers	esrb_rating	added_status_yet	added_status_owned	added_status_beaten	added_status_toplay	added_status_dropped	added_status_playing

void Load(string filename, vector<Game>& gameVector) {

	int id = 0;
    string name = "";
    vector<string> developers;
    vector<string> genres;
    string releaseDate = "";
    double rating = 0.0;
    int playtime = 0;
    int achievementCount = 0;
    string platform = "";

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
				name = value;
				break;
			case 3: //name
				developers.push_back(value);
				break;
			case 4: //-metacritic
				genres.push_back(value);
                break;
			case 5: //released
				releaseDate = value;
                break;
            case 6: //-tba
                rating = stod(value);
                break;
			case 7: //-updated
				try{
                    playtime = stoi(value);
                }
                catch (const invalid_argument& ia){
                    playtime = 00000000;
                }
                break;
			case 8: //-website
                try {
					achievementCount = stoi(value);
				}
				catch (const invalid_argument& ia) {
					achievementCount = 00000000;
				}
				break;
            case 9: //rating
                platform = value;
                break;
			case 10: //-rating top
				break;
			case 11: //playtime
				break;
			case 12: //achievment count
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
				break;
			case 18:
				break;
			case 19:
				break;
			case 20:
				break;
			case 21:
				break;
			case 22:
				break;
			case 23:
				break;
			case 24:
				break;
			case 25:
				break;
			case 26:
				break;

			count++;
			}
		}
        count = 1;
		Game g = Game(id,name,developers,genres,releaseDate,rating,playtime,achievementCount,platform);
        gameVector.push_back(g);
	}

}