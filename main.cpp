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
    Game temp;          //for finding in vector

    //text output begins
    cout << "|-----------------------------------------------------------------------------|\n"
            "|                               Know Your Game                                |\n"
            "|-----------------------------------------------------------------------------|\n"
            "|                                                                             |\n"
            "|    Get to know about the game ID, Name, Developers, Genres, Platforms,      |\n"
            "|    Release Date, Rating, Playtime and Achievement Count!                    |\n"
            "|                                                                             |\n"
            "|-----------------------------------------------------------------------------|\n"
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
            cout << "|              Enter your choice:                                             |\n";
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
            cout << "|              Enter an ID number:                                            |\n";
            cin >> userInput;
            if(userInput == "exit" || userInput == "Exit"){
                loopMenu = false;
                break;
            }
            cout << "|              Searching by ID ...                                            |\n";
            
            // searching vector
            t.start();
            for(int i = 0; i < games.size(); i++){
                if (games[i].id == stoi(userInput))
                    temp = games[i];
                    break;
            }
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for Vector ID Search is: "<< time;
            p.printSpaces(78-(45+time.length()));
            cout << "|\n";

            //searching tree
            t.start();
            tree.search(stoi(userInput));
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for AVL Tree ID Search is: " << time;
            p.printSpaces(78-(47+time.length()));
            cout << "|\n";

            //searching map
            t.start();
            temp = map.searchId(stoi(userInput));
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for Unordered Map ID Search is: " << time;
            p.printSpaces(78-(52+time.length()));
            cout << "|\n";

            //print the Game information
            temp.printInfo();
            q1c1 = false;
        }

        if(q1c2){   //if q1 choice 2, search by name
//FIXME compare search results, print out if they match. Results should be found by looping in vector, returned from AVL, returned from MAP
            cout << "|              Enter a Name:                                                  |\n";
            cin >> userInput;
            if(userInput == "exit" || userInput == "Exit"){
                loopMenu = false;
                break;
            }
            cout << "|              Searching by Name ...                                          |\n";
            
            // searching vector
            t.start();
            for(int i = 0; i < games.size(); i++){
                if (games[i].name == userInput)
                    temp = games[i];
                    break;
            }
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for Vector Name Search is: " << time;
            p.printSpaces(78-(47+time.length()));
            cout << "|\n";

            //searching tree
            t.start();
            tree.search(userInput);
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for AVL Tree Name Search is: " << time;
            p.printSpaces(78-(49+time.length()));
            cout << "|\n";

            //searching map
            t.start();
            temp = map.searchName(userInput);
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for Unordered Map Name Search is: " << time;
            p.printSpaces(78-(54+time.length()));
            cout << "|\n";

            //print the Game information
            temp.printInfo();
            q1c2 = false;
        }

        if(q1c3) { //Search by developer
//FIXME compare search results, print out if they match. Results should be found by looping in vector, returned from AVL, returned from MAP
            cout << "|              Enter a Developer:                                             |\n";
            cin >> userInput;
            if(userInput == "exit" || userInput == "Exit"){
                loopMenu = false;
                break;
            }
            cout << "|              Searching by Developer ...                                     |\n";
            vector<Game> gamesDev;
            vector<Game> gamesDev2;

            // searching vector
            t.start();
            for(int i = 0; i < games.size(); i++){
                for(int j = 0; j < games[i].developers.size(); j++){
                    if(games[i].developers[j] == userInput)
                        gamesDev.push_back(games[i]);
                }
            }
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for Vector ID Search is: " << time;
            p.printSpaces(78-(45+time.length()));
            cout << "|\n";

            //searching tree
            t.start();
            tree.searchDev(userInput);
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for AVL Tree ID Search is: " << time;
            p.printSpaces(78-(47+time.length()));
            cout << "|\n";

            //searching map
            t.start();
            gamesDev2 = map.searchDeveloper(userInput);
            t.stop();
            if(t.time() == 0)
                time = "< 0.001 s";
            else
                time = to_string(t.time()) + " s";
            cout << "|              Time for Unordered Map ID Search is: " << time;
            p.printSpaces(78-(52+time.length()));
            cout << "|\n";

//FIXME printing all the games from a Developer is not working
//use <Game>.printInfo() to print the games
            //print the Game information
            for(int i = 0; i < gamesDev.size(); i++){
                gamesDev2[i].printInfo();
            }
            q1c3 = false;
        }

        answered = true;
    }

    return 0;
}