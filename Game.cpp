#include "Game.h"
#include "Parsing.h"
Game::Game(int id_, string name_, vector<string> developers_, vector<string> genres_, vector<string> platforms_, string releaseDate_, double rating_, int playtime_, int achievementCount){
    id =  id_;
    name =  name_;
    developers = developers_;
    genres = genres_;
    platforms = platforms_;
    releaseDate = releaseDate_;
    rating = rating_;
    playtime = playtime_;
    achievementCount = achievementCount;
}

void Game::printInfo(){
    Parsing p;
    //id string
    string idstring = std::to_string(id);
    //developers string
    string developersstring = "";
    if(developers.empty())
        developersstring = "N/A";
    for(int i = 0; i < developers.size(); i++){
        if(i != developers.size() - 1)
            developersstring += developers[i] + ", ";
        else
            developersstring += developers[i];
    }
    //genres string
    string genresstring = "";
    if(genres.empty())
        genresstring = "N/A";
    for (int i = 0; i < genres.size(); i++){
        if(i != genres.size() -1)
            genresstring += genres[i] + ", ";
        else
            genresstring += genres[i];
    }
    //platforms string
    string platformsstring = "";
    if(platforms.empty())
        platformsstring = "?";
    for (int i = 0; i < platforms.size(); i++){
        if(i != platforms.size() -1)
            platformsstring += platforms[i] + ", ";
        else
            platformsstring += platforms[i];
    }
    //rating string
    string ratingstring = "";
    if(rating == 0)
        ratingstring = "N/A";
    else {
        ratingstring = std::to_string(rating);
        ratingstring = ratingstring.substr(0,4) + " / 5.00";
    }
    //playtime string
    string playtimestring = "";
    if(playtime == 0)
        playtimestring = "We're not sure!";
    else
        playtimestring = std::to_string(playtime) + " hours to complete";
    //achievementcount string
    string achievementcountstring = "";
    if(achievementCount == 0)
        achievementcountstring = "None";
    else
        achievementcountstring = std::to_string(achievementCount) + "achievements to get!";
    cout << "|-----------------------------------------------------------------------------|\n";
    cout << "|              Here's the game you are looking for!                           |\n";
    cout << "|                                                                             |\n";
    cout << "|              Get to \"Know Your Game\"!!!                                     |\n";
    cout << "|              ID: " << idstring;
    p.printSpaces(78-(19+idstring.length())); cout << "|\n";
    cout << "|              Name: " << name;
    p.printSpaces(78-(21+name.length())); cout << "|\n";
    cout << "|              Developers: " << developersstring;
    p.printSpaces(78-(27+developersstring.length())); cout << "|\n";
    cout << "|              Genres: " << genresstring;
    p.printSpaces(78-(23+genresstring.length())); cout << "|\n";
    cout << "|              Platforms: "<< platformsstring;
    p.printSpaces(78-(26+platformsstring.length())); cout << "|\n";
    cout << "|              Release Date: " << releaseDate;
    p.printSpaces(78-(29+releaseDate.length())); cout << "|\n";
    cout << "|              Rating: " << ratingstring;
    p.printSpaces(78-(23+ratingstring.length())); cout << "|\n";
    cout << "|              Playtime: " << playtimestring;
    p.printSpaces(78-(25+playtimestring.length())); cout << "|\n";
    cout << "|              Achievement Count: " << achievementcountstring;
    p.printSpaces(78-(34+achievementcountstring.length())); cout << "|\n";
    cout << "|-----------------------------------------------------------------------------|\n";
}