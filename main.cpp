#include "FileRead.cpp"
#include "UnorderedMap.h"
#include "AVLTree.h"
#include "Timer.h"

int main() {
    vector<Game> g;
    Load("game_info.csv", g);
    for(int i = 0; i < g.size(); i++){
        g[i].printInfo();
    }
    return 0;
}