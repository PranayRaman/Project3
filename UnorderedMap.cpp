#include "UnorderedMap.h"
#include <stdexcept>

// Node object for separate chaining
// first = Game ID
// second = Game object
struct UnorderedMap::MapNode {
    int first;
    Game second;
    MapNode* next;
    MapNode(Game g) {first = g.id; second = g; next = nullptr;}
};


// Helper function for inserting/updating Nodes
void UnorderedMap::insertNode(MapNode** arr, Game& game) {
    MapNode* newNode = new MapNode(game);
    MapNode* iter = arr[hash(game.id)];

    if (iter == nullptr) {
        arr[hash(game.id)] = newNode;
        ++_size;
        checkResize();
        return;
    }
    while (iter->next != nullptr) {
        if (iter->first == game.id)
            return;
        iter = iter->next;
    }
    if (iter->first == game.id)
        return;
    iter->next = newNode;
    ++_size;
    checkResize();
}

// Hash function: uses x % capacity
int UnorderedMap::hash(int id) const {return id % capacity;}

// Helper function to check for resize and, if so, execute it
void UnorderedMap::checkResize() {
    if ((double)_size/(double)capacity >= MAX_LOAD_FACTOR)
        resize(capacity*2);
}

// Create a new arr to reflect size change and insert all old values into it
void UnorderedMap::resize(int newCapacity) {
    _size = 0;
    int oldCapacity = capacity;
    MapNode** newArr = new MapNode*[newCapacity];
    for (int i = 0; i < newCapacity; ++i)
        newArr[i] = nullptr;

    capacity = newCapacity;
    MapNode* iter = nullptr;
    for (int i = 0; i < oldCapacity; ++i) {
        iter = arr[i];
        while (iter != nullptr) {
            insertNode(newArr, iter->second);
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
// Argument constructor: capacity
UnorderedMap::UnorderedMap(int capacity) {
    _size = 0;
    this->capacity = capacity;
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

// Request a change in capacity and force a resize
void UnorderedMap::reserve(int capacity) {
    resize(capacity);
}


// Insert a Game then resize if necessary
// If trying to insert a key that already exists, do nothing
void UnorderedMap::insert(Game& game) {
    insertNode(arr, game);
}

// Remove a Game without considering resizing.
// If id is not present, do nothing.
void UnorderedMap::erase(int id) {
    MapNode* iter = arr[hash(id)];
    if (iter == nullptr)
        return;
    // Beginning of list
    if (iter->first == id) {
        MapNode* target = iter;
        arr[hash(id)] = iter->next;
        delete target;
        --_size;
        return;
    }
    // Every value after beginning
    while (iter->next != nullptr) {
        if (iter->next->first == id) {
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
// Returns whether Game was found
bool UnorderedMap::find(int id) {
    MapNode* iter = arr[hash(id)];
    while (iter != nullptr) {
        if (iter->first == id)
            return true;
        iter = iter->next;
    }
    return false;
}

// Search for Game by id
// Returns an empty Game struct if not found
Game UnorderedMap::searchId(int id) {
    MapNode* iter = arr[hash(id)];
    while (iter != nullptr) {
        if (iter->first == id)
            return iter->second;
        iter = iter->next;
    }
    return Game();
}

// Search for Game by name
// Returns an empty Game struct if not found
Game UnorderedMap::searchName(string name) {
    MapNode* iter = nullptr;
    for (int i = 0; i < capacity; ++i) {
        iter = arr[i];
        while (iter != nullptr) {
            if (iter->second.name == name)
                return iter->second;
            iter = iter->next;
        }
    } 
    return Game();
}

// Search for Games by developer
// Returns vector of all games by a particular developer (may be empty)
vector<Game> UnorderedMap::searchDeveloper(string dev) {
    vector<Game> games;
    MapNode* iter = nullptr;
    for (int i = 0; i < capacity; ++i) {
        iter = arr[i];
        while (iter != nullptr) {
            for (auto& developer : iter->second.developers)
                if (developer == dev)
                    games.push_back(iter->second);
            iter = iter->next;
        }
    }
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
    MapNode* iter = arr[hash(id)];
    while (iter != nullptr) {
        if (iter->first == id)
            return iter->second;
        iter = iter->next;
    }
    throw std::out_of_range("UnorderedMap: index not found");
}