#pragma once
#include "Game.h"

// Unordered Map storing Game objects using LinkedList separate chaining
// Limited functionality due to the purpose of this project
// Only supports: insertion, access by id
// Source: John Gionti - Stepik 10.2.1
class UnorderedMap {
    struct MapNode;
private:
    MapNode** arr;
    int _size, capacity;
    const double MAX_LOAD_FACTOR = 0.8;
    int hash(int id) const;

    void insertNode(MapNode** arr, Game game);
    void checkResize();
    void resize();

public:
    UnorderedMap();
    ~UnorderedMap();

    bool empty();
    int size();
    int max_size();

    class iterator;
    iterator begin();
    iterator end();

    void insert(Game& game);
    void erase(int id);
    bool find(int id);
    Game& operator[](int id);
    Game& at(int id) const;
};