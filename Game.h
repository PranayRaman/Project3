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
    Game(){}
    Game(int id_, string name_, vector<string> developers_, vector<string> genres_, vector<string> platforms_, string releaseDate_, double rating_, int playtime_, int achievementCount);
// ==== Functions ====
    void printInfo();
};

