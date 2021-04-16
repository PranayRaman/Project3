#pragma once
#include "Game.h"

// Unordered Map storing Game objects using LinkedList separate chaining
// Limited functionality due to the purpose of this project
// Only supports: insertion, access by id
// Source: John Gionti - Stepik 10.2.1
class UnorderedMap {
    // Node object for separate chaining
    struct MapNode{
        Game game;
        MapNode* next;
        MapNode(Game g) {game = g; next = nullptr;}
    };
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

    class iterator {
        UnorderedMap* map;
        MapNode* it;
        int index;
    public:
        iterator(UnorderedMap* map) {this->map = map; it = nullptr; index = 0;}
        iterator(UnorderedMap* map, MapNode* node) {this->map = map; it = node; index = 0;}
        int first() {return it->game.id;}
        Game& second() {return it->game;}
        void operator=(iterator rhs) {it = rhs.it;}
        bool operator==(iterator rhs) {return it == rhs.it;}
        bool operator!=(iterator rhs) {return it != rhs.it;}
        iterator& operator++() {
            if (it == nullptr || it->next == nullptr)
                it = map->arr[++index];
            else it = it->next;
            return *this;
        }
    };
    iterator begin();
    iterator end();

    void insert(Game& game);
    void erase(int id);
    bool find(int id);
    Game& operator[](int id);
    Game& at(int id) const;
};