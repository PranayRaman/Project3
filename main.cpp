#include "FileRead.h"
#include "UnorderedMap.h"
#include "AVLTree.h"
#include "Timer.h"

int main() {
    Timer t;
    // Load data into all 3 data structures (Vector, UnorderedMap, AVLTree)
    t.start();
    vector<Game> games;
    Load("game_info.csv", games);
    t.stop();
    cout << "Loading Vector took " << t.time() << " sec." << endl;

    t.start();
    UnorderedMap map;
    for (auto g : games)
        map.insert(g);
    t.stop();
    cout << "Loading Map took " << t.time() << " sec." << endl;

    AVLTree tree;
    for (auto g : games)
        tree.insert(g, g.id);

    
    // Do Parsing

    return 0;
}