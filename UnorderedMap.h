#pragma once
#include "Game.h"

// Unordered Map storing Game objects using linked list separate chaining
// Specialized functionality due to the purpose of this project
// Source: John Gionti - Stepik 10.2.1
class UnorderedMap {
    struct MapNode;
private:
    MapNode** arr;
    int _size, capacity;
    const double MAX_LOAD_FACTOR = 1.0;
    int hash(int id) const;

    void checkResize();
    void resize(int newCapacity);
    void insertNode(MapNode** arr, Game& game);

public:
    UnorderedMap();
    UnorderedMap(int capacity);
    ~UnorderedMap();

    bool empty();
    int size();
    int max_size();
    void reserve(int capacity);

    void insert(Game& game);
    void erase(int id);
    bool find(int id);

    Game searchId(int id);
    Game searchName(string name);
    vector<Game> searchDeveloper(string dev);

    Game& operator[](int id);
    Game& at(int id);
};