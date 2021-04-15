#include "FileRead.cpp"
#include "UnorderedMap.h"
#include "AVLTree.h"
#include "Timer.h"

int main() {
<<<<<<< HEAD
   
    return -0;
=======
    vector<Game> g;
    Load("game_info.csv", g);
    for(int i = 0; i < g.size(); i++){
        g[i].printInfo();
    }
    return 0;
>>>>>>> af42a834e843f02c7d500c786f1c376f44762f97
}