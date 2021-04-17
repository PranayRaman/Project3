#include "FileRead.h"
#include "UnorderedMap.h"
#include "AVLTree.h"
#include "Timer.h"
#include "Parsing.h"
#include <windows.h>
#include <iostream>
#include <string>
using std::cout;

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

    //Terminal Size Info


    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int windowCols = csbi.dwSize.X;
    int windowRows = csbi.dwSize.Y;
    //learned how to get console window size
    //https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

    // Do Parsing
    

    return 0;
}