#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

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
			case 1:
                try {
					id = stoi(value);
				}
				catch (const invalid_argument& ia) {
					id = 00000000;
				}
				break;
			case 2:
				name = value;
				break;
			case 3:
				developers.push_back(value);
				break;
			case 4:
				genres.push_back(value);
                break;
			case 5:
				releaseDate = value;
                break;
			case 6:
				try{
                    playtime = stoi(value);
                }
                catch (const invalid_argument& ia){
                    id = 00000000;
                }
                break;
			case 7:
                try {
					achievementCount = stoi(value);
				}
				catch (const invalid_argument& ia) {
					achievementCount = 00000000;
				}
				break;
            case 8:
                platform = value;
                break;
            }
			count++;
		}
		
	}

}