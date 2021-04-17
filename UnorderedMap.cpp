#include "UnorderedMap.h"
#include <stdexcept>
#include <utility>
using std::make_pair;


// Hash function: uses x % capacity
int UnorderedMap::hash(int id) const {return id % capacity;}

// Helper function to check for resize and, if so, execute it
void UnorderedMap::checkResize() {
    if ((double)_size/(double)capacity >= MAX_LOAD_FACTOR)
        resize(capacity*2);
    else if ((double)_size/(double)capacity*2 < MAX_LOAD_FACTOR && capacity > 10)
        resize(capacity/2);
}

// Create a new arr to reflect size change and insert all old values into it
void UnorderedMap::resize(int newCapacity) {
    vector<vector<pair<int,Game>>> newArr;
    newArr.resize(newCapacity);
    for (auto& bucket : arr)
        for (auto& pair : bucket)
            newArr[hash(pair.first)].push_back(pair);
    capacity = newCapacity;
    arr = newArr;
}



// Default constructor
UnorderedMap::UnorderedMap() {
    _size = 0;
    capacity = 10;
    arr.resize(capacity);
}
// Argument constructor: capacity
UnorderedMap::UnorderedMap(int capacity) {
    _size = 0;
    this->capacity = capacity;
    arr.resize(capacity);
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

// Request a change in capacity and force a resize
void UnorderedMap::reserve(int capacity) {
    resize(capacity);
}


// Insert a Game then resize if necessary
// If trying to insert a key that already exists, do nothing
void UnorderedMap::insert(Game& game) {
    auto newPair = make_pair(game.id, game);
    for (auto& pair : arr[hash(game.id)])
        if (pair.first == newPair.first)
            return;
    arr[hash(game.id)].push_back(newPair);
    ++_size;
    checkResize();
}

// Remove a Game without considering resizing.
// If id is not present, do nothing.
void UnorderedMap::erase(int id) {
    for (auto iter = arr[hash(id)].begin(); iter != arr[hash(id)].end(); ++iter)
        if (iter->first == id)
            arr[hash(id)].erase(iter, iter+1);
}

// Search for Game by id
// Returns whether Game was found
bool UnorderedMap::find(int id) {
    for (auto& pair : arr[hash(id)])
        if (pair.first == id)
            return true;
    return false;
}

// Search for Game by id
// Returns an empty Game struct if not found
Game UnorderedMap::searchId(int id) {
    for (auto& pair : arr[hash(id)])
        if (pair.first == id)
            return pair.second;
    return Game();
}

// Search for Game by name
// Returns an empty Game struct if not found
Game UnorderedMap::searchName(string name) {
    for (auto& bucket : arr)
        for (auto& pair : bucket)
            if (pair.second.name == name)
                return pair.second;
    return Game();
}

// Search for Games by developer
// Returns vector of all games by a particular developer
vector<Game> UnorderedMap::searchDeveloper(string dev) {
    vector<Game> games;
    for (auto& bucket : arr)
        for (auto& pair : bucket)
            for (auto developer : pair.second.developers)
                if (developer == dev)
                    games.push_back(pair.second);
    return games;
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
Game& UnorderedMap::at(int id) {
    for (auto& pair : arr[hash(id)])
        if (pair.first == id)
            return pair.second;
    throw std::out_of_range("UnorderedMap: index not found");
}