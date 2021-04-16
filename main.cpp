#include "FileRead.h"
#include "UnorderedMap.h"
#include "AVLTree.h"
#include "Timer.h"

int main() {
    // Load data into all 3 data structures (Vector, UnorderedMap, AVLTree)
    vector<Game> games;
    Load("game_info.csv", games);
    for (auto g : games)
        g.printInfo();

    UnorderedMap map;
    for (auto g : games)
        map.insert(g);
    for (auto iter = map.begin(); iter != map.end(); ++iter)    // currently doesn't work :(
        iter.second().printInfo();
    AVLTree tree;
    for (auto g : games)
        tree.insert(g, g.id);

    
    // Do Parsing

    return 0;
}