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
    bool loopMenu = true;
    Parsing p;
    Timer t;
    vector<Game> games;
    UnorderedMap map;
    
    // Parsing
    bool answered = true;
    string q1;
    bool q1c1 = false;  //q1 choice 1
    bool q1c2 = false;  //q1 choice 2
    bool q1c3 = false;  //q1 choice 3
    string userInput;   //input for search
    string time = "";   //for printing search time
    Game temp1;          //for finding in vector
    Game temp2;
    Game temp3;

    //text output begins
    cout << "|-----------------------------------------------------------------------------|\n"
            "|                               Know Your Game                                |\n"
            "|-----------------------------------------------------------------------------|\n"
            "|                                                                             |\n"
            "|         How do others rate it? How long does it take to complete?           |\n"
            "|     What other games did this developer make? Find out these and more!      |\n"
            "|                                                                             |\n"
            "|                                                                             |\n"
            "|                    To exit the program at any time type:                    |\n"
            "|                            exit     or     Exit                             |\n"
            "|-----------------------------------------------------------------------------|\n"
            "|                          Currently loading Games...                         |\n"
            "|-----------------------------------------------------------------------------|\n";

    // Load data into all 3 data structures (Vector, UnorderedMap, AVLTree)
    
    // Vector
    t.start();
    Load("game_info.csv", games);
    t.stop();
    time = to_string(t.time()) + " s";
    cout << "|              Loading Vector from .csv took " << time;
    p.printSpaces(78-(45+time.length())); cout << "|\n";

    // Unordered Map
    t.start();
    for (auto g : games)
        map.insert(g);
    t.stop();
    time = to_string(t.time()) + " s";
    cout << "|              Loading Map from vector took " << time;
    p.printSpaces(78-(44+time.length())); cout << "|\n";

    // AVL Tree
    t.start();
    AVLTree tree;
    for (auto g : games)
        tree.insert(g, g.id);
    t.stop();
    time = to_string(t.time()) + " s";
    cout << "|              Loading Tree from vector took " << time;
    p.printSpaces(78-(45+time.length())); cout << "|\n";

    cout << "|-----------------------------------------------------------------------------|\n";

    while(loopMenu){
        cout << "|                                                                             |\n"
                "|              How would you like to get to \"Know Your Game\"?                 |\n"
                "|                                                                             |\n"
                "|              1. Search by ID                                                |\n"
                "|              2. Search by Name                                              |\n"
                "|              3. Search by Developer                                         |\n"
                "|              4. Exit Program                                                |\n"
                "|                                                                             |\n";
        do{
            cout << "|              Enter your choice: ";
            cin >> q1;
            if(q1 == "1"){
                q1c1 = true;
                answered = true;
            }
            else if(q1 == "2"){
               q1c2 = true;
               answered = true;
            }
            else if(q1 == "3"){
                q1c3 = true;
                answered = true;
            }
            else if(q1 == "4"){
                loopMenu = false;
                answered = true;
            }
            else if (q1 == "exit" || q1 == "Exit"){
                loopMenu = false;
                answered = true;
            }
            else
                answered = false;
        }
        while(!answered);
        answered = true;

        if(q1c1){   //if search by ID
//FIXME compare search results, print out if they match. Results should be found by looping in vector, returned from AVL, returned from MAP
            cout << "|              Enter an ID number: ";
            cin >> userInput;
            if(userInput == "exit" || userInput == "Exit"){
                loopMenu = false;
                break;
            }
            cout << "|              Searching by ID ...                                            |\n";
            
            // searching vector
            t.start();
            for(int i = 0; i < games.size(); i++){
                if (games[i].id == stoi(userInput)) {
                    temp1 = games[i];
                    break;
                }
            }
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for Vector Search is: " << time;
            p.printSpaces(78-(42+time.length()));
            cout << "|\n";

            //searching tree
            t.start();
            temp2= tree.search(stoi(userInput));
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for AVL Tree Search is: " << time;
            p.printSpaces(78-(44+time.length()));
            cout << "|\n";

            //searching map
            t.start();
            temp3 = map.searchId(stoi(userInput));
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for Unordered Map Search is: " << time;
            p.printSpaces(78-(49+time.length()));
            cout << "|\n";

            //print the Game information
            temp1.printInfo();
            q1c1 = false;


            //results
            if(temp1.id!=temp2.id || temp2.id!=temp3.id)
                cout<< "Results do not match! (This is bad)";

        }

        if(q1c2){   //if q1 choice 2, search by name
//FIXME compare search results, print out if they match. Results should be found by looping in vector, returned from AVL, returned from MAP
            cout << "|              Enter a Name: ";
            cin.ignore();
            getline(cin, userInput);
            if(userInput == "exit" || userInput == "Exit"){
                loopMenu = false;
                break;
            }
            cout << "|              Searching by Name ...                                          |\n";
            
            // Results

            // searching vector
            t.start();
            for(int i = 0; i < games.size(); i++){
                if (games[i].name == userInput) {
                    temp1 = games[i];
                    break;
                }
            }
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for Vector Search is: " << time;
            p.printSpaces(78-(42+time.length()));
            cout << "|\n";

            //searching tree
            t.start();
            temp2=tree.search(userInput);
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for AVL Tree Search is: " << time;
            p.printSpaces(78-(44+time.length()));
            cout << "|\n";

            //searching map
            t.start();
            temp3 = map.searchName(userInput);
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for Unordered Map Search is: " << time;
            p.printSpaces(78-(49+time.length()));
            cout << "|\n";

            //print the Game information
            temp1.printInfo();
            q1c2 = false;

            //results
            if(temp1.id!=temp2.id || temp2.id!=temp3.id)
                cout<< "Results do not match! (This is bad)";
        }

        if(q1c3) { //Search by developer
//FIXME compare search results, print out if they match. Results should be found by looping in vector, returned from AVL, returned from MAP
            cout << "|              Enter a Developer: ";
            cin.ignore();
            getline(cin, userInput);
            if(userInput == "exit" || userInput == "Exit"){
                loopMenu = false;
                break;
            }
            cout << "|              Searching by Developer ...                                     |\n";
            vector<Game> gamesDev1;
            vector<Game> gamesDev2;
            vector<Game> gamesDev3;

            // searching vector
            t.start();
            for(int i = 0; i < games.size(); i++){
                for(int j = 0; j < games[i].developers.size(); j++){
                    if(games[i].developers[j] == userInput)
                        gamesDev1.push_back(games[i]);
                }
            }
            t.stop();
            time = to_string(t.time()) + " s";
            
            cout << "|              Time for Vector Search is: " << time;
            p.printSpaces(78-(42+time.length()));
            cout << "|\n";

            //searching tree
            t.start();
            gamesDev2 = tree.searchDev(userInput);
            t.stop();
            time = to_string(t.time()) + " s";

            cout << "|              Time for AVL Tree Search is: " << time;
            p.printSpaces(78-(44+time.length()));
            cout << "|\n";

            //searching map
            t.start();
            gamesDev3 = map.searchDeveloper(userInput);
            t.stop();
            time = to_string(t.time()) + " s";

            cout << "|              Time for Unordered Map Search is: " << time;
            p.printSpaces(78-(49+time.length()));
            cout << "|\n";

            //print the Game information
            if(gamesDev1.size()==gamesDev2.size() && gamesDev2.size()==gamesDev3.size())
                for(int i = 0; i < gamesDev2.size(); i++){
                    // TODO: return list of names of games instead
                }
            else {
                // TODO: print vectors don't match! sus!
            }

            q1c3 = false;
        }

        answered = true;
    }

    return 0;
}

