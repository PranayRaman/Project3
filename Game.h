#pragma once
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
using std::cout;
using std::endl;

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
// ==== Constructors ====
    Game(int id_, string name_, vector<string> developers_, vector<string> genres_, vector<string> platforms_, string releaseDate_, double rating_, int playtime_, int achievementCount);
// ==== Functions ====
    void printInfo();
};

Game::Game(int id_, string name_, vector<string> developers_, vector<string> genres_, vector<string> platforms_, string releaseDate_, double rating_, int playtime_, int achievementCount){
    id =  id_;
    name =  name_;
    developers = developers_;
    genres = genres_;
    platforms = platforms_;
    releaseDate = releaseDate_;
    rating = rating_;
    playtime = playtime_;
    achievementCount = achievementCount;
}

void Game::printInfo(){
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Developers: ";
    for (int i = 0; i < developers.size(); i++){
        if(i != developers.size() -1)
            cout << developers[i] << ", ";
        else
            cout << developers[i] << endl;
    }
    cout << "Genres: ";
    if(genres.empty())
        cout << "?" << endl;
    for (int i = 0; i < genres.size(); i++){
        if(i != genres.size() -1)
            cout << genres[i] << ", ";
        else
            cout << genres[i] << endl;;
    }
    cout << "Platforms: ";
    for (int i = 0; i < platforms.size(); i++){
        if(i != platforms.size() -1)
            cout << platforms[i] << ", ";
        else
            cout << platforms[i] << endl;;
    }
    cout << "Release Date: " << releaseDate << endl;
    cout << "Rating: ";
    if(rating == 0)
        cout << "N/A" << endl;
    else
        cout << rating << endl;
    cout << "Playtime: ";
    if(playtime == 0)
        cout << "?" << endl;
    else
        cout << playtime << endl;
    cout << "Achievement Count: ";
    if(achievementCount == 0)
        cout << "N/A" << endl;
    else
        cout << achievementCount << endl;
    cout << "-----------------------------------" << endl;
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