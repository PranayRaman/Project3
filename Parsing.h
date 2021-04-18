#include <string>
#include "Game.h"
using namespace std;
class Parsing{ //john do you want to search by all of these?
//or only some. They each would need their own AVL tree to build
public:
    string line = "|-----------------------------------------------------------------------------|\n";
    string blankline = "|                                                                             |\n";
    
    void printSpaces(int n){
        for(int i = 0; i < n; i++){
            cout << " ";
        }
    }

};
