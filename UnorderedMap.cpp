#include "UnorderedMap.h"
#include <stdexcept>

// Node object for separate chaining
struct UnorderedMap::MapNode {
    Game game;
    MapNode* next;
    MapNode(Game g) {game = g; next = nullptr;}
};

class UnorderedMap::iterator {
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

// Find first available element
// If empty, return first index (which is nullptr)
UnorderedMap::iterator UnorderedMap::begin() {
    MapNode* node = arr[0];
    int i = 1;
    while (node == nullptr && i < capacity)
        node = arr[i++];
    if (node == nullptr)
        return iterator(this, arr[0]);
    return iterator(this, node);
}

// Find spot with last available element (work backwards)
// If empty, return last index (which is nullptr)
UnorderedMap::iterator UnorderedMap::end() {
    MapNode* node = arr[capacity-1];
    int i = capacity-2;
    while (node == nullptr && i > 0)
        node = arr[i--];
    if (node == nullptr)
        return iterator(this, arr[capacity-1]);

    while (node != nullptr)
        node = node->next;
    return iterator(this, node);
}


// Hash function: uses x % capacity
int UnorderedMap::hash(int id) const {return id % capacity;}

// Helper function for inserting/updating Nodes
void UnorderedMap::insertNode(MapNode** arr, Game game) {
    MapNode* newNode = new MapNode(game);
    MapNode* iter = arr[hash(game.id)];

    if (iter == nullptr) {
        arr[hash(game.id)] = newNode;
        ++_size;
        checkResize();
        return;
    }
    while (iter->next != nullptr) {
        if (iter->game.id == game.id)
            return;
        iter = iter->next;
    }
    if (iter->game.id == game.id)
        return;
    iter->next = newNode;
    ++_size;
    checkResize();
}

// Helper function to check for resize and, if so, execute it
void UnorderedMap::checkResize() {
    if ((double)_size/(double)capacity >= MAX_LOAD_FACTOR)
        resize();
}

// Create a new arr with double the size and insert all old elements
void UnorderedMap::resize() {
    _size = 0;
    MapNode** newArr = new MapNode*[capacity*2];
    for (int i = 0; i < capacity*2; ++i)
        newArr[i] = nullptr;
    MapNode* iter = nullptr;
    capacity *= 2;
    for (int i = 0; i < capacity/2; ++i) {
        iter = arr[i];
        while (iter != nullptr) {
            insertNode(newArr, iter->game);
            iter = iter->next;
        }
    }
    MapNode** temp = arr;
    delete[] temp;
    arr = newArr;
}



// Default constructor
UnorderedMap::UnorderedMap() {
    _size = 0;
    capacity = 10;
    arr = new MapNode*[capacity];
    for (int i = 0; i < capacity; ++i)
        arr[i] = nullptr;
}

// Destructor
UnorderedMap::~UnorderedMap() {
    delete[] arr;
}

// Return whether map is empty
bool UnorderedMap::empty() {
    return (_size == 0);
}

// Return map size
int UnorderedMap::size() {
    return _size;
}

// Return map capacity
int UnorderedMap::max_size() {
    return capacity;
}


// Insert a Game then resize if necessary
void UnorderedMap::insert(Game& game) {
    insertNode(arr, game);
}

// Remove a Game without considering resizing.
// If id is not present, do nothing.
void UnorderedMap::erase(int id) {
    // Get code from Stepik
    MapNode* iter = arr[hash(id)];
    if (iter == nullptr)
        return;
    // Beginning of list
    if (iter->game.id == id) {
        MapNode* target = iter;
        arr[hash(id)] = iter->next;
        delete target;
        --_size;
        return;
    }
    // Every value after beginning
    while (iter->next != nullptr) {
        if (iter->next->game.id == id) {
            MapNode* target = iter->next;
            iter->next = iter->next->next;
            delete target;
            --_size;
            return;
        }
        iter = iter->next;
    }
}

// Search for Game by id
bool UnorderedMap::find(int id) {
    MapNode* iter = arr[hash(id)];
    while (iter != nullptr) {
        if (iter->game.id == id)
            return true;
        iter = iter->next;
    }
    return false;
}


// Search for game. If not found, create Game object and store.
// Returns reference to target Game
Game& UnorderedMap::operator[](int id) {
    try {return at(id);}
    catch (std::out_of_range) {}

    Game newGame;
    newGame.id = id;
    insert(newGame);
    return at(id);    
}

// Search for game. If not found, throw out_of_range exception
// Returns reference to target Game
Game& UnorderedMap::at(int id) const {
    MapNode* iter = arr[hash(id)];
    while (iter != nullptr) {
        if (iter->game.id == id)
            return iter->game;
        iter = iter->next;
    }
    throw std::out_of_range("UnorderedMap: index not found");
}