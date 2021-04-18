#include <string>
using namespace std;
class Parsing{ //john do you want to search by all of these?
//or only some. They each would need their own AVL tree to build
    string KnowYourGame = 
    "#################\n"
    "# Know Your Game #\n"
    "##################";
    string question1 = "How would you like to get to Know Your Game?";
    string q1options = 
    "1. Search by ID\n"
    "2. Search by name\n";
public:
    void printSpaces(int n){
        for(int i = 0; i < n; i++){
            cout << " ";
        }
    }
};
