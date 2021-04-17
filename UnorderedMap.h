#pragma once
#include <vector>
#include "Game.h"
using std::pair;

// Unordered Map storing Game objects using linked list separate chaining
// Backed by vector implementation
// Specialized functionality due to the purpose of this project
// Source: John Gionti - Stepik 10.2.1
class UnorderedMap {
private:
    vector<vector<pair<int,Game>>> arr;
    int _size, capacity;
    const double MAX_LOAD_FACTOR = 0.8;
    int hash(int id) const;

    void insertPair(vector<vector<pair<int,Game>>>& arr, Game& game);
    void checkResize();
    void resize(bool isSizeUp);

public:
    UnorderedMap();

    bool empty();
    int size();
    int max_size();

    void insert(Game& game);
    void erase(int id);
    bool find(int id);

    Game searchId(int id);
    Game searchName(string name);
    vector<Game> searchDeveloper(string dev);
    vector<Game> getLongestPlayed();
    vector<Game> getMostPopular(string genre);

    Game& operator[](int id);
    Game& at(int id);


};